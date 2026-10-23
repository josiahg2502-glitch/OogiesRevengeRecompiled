#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <libXbSymbolDatabase.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static bool bReverseMangle = true;
static bool bExtendInfo = false;

static void msg_cb(xb_output_message message_flag, const char* msg)
{
    fprintf(stderr, "XbSymbolDatabase: %s\n", msg);
}

static void reg_cb(const char* library_str,
                   uint32_t library_flag,
                   uint32_t xref_index,
                   const char* symbol_str,
                   xbaddr address,
                   uint32_t build_version,
                   uint32_t symbol_type,
                   uint32_t call_type,
                   uint32_t param_count,
                   const XbSDBSymbolParam* param_list)
{
    const char* symbol_name = bReverseMangle ? symbol_str : XbSDB_SymbolReferenceToString(xref_index);
    char buffer[64] = { 0 };
    char param_output[256] = { 0 };
    size_t param_size = 0;
    if (bExtendInfo) {
        switch (symbol_type) {
            case symbol_variable: {
                printf("%.8s__VAR__%s = 0x%08x\n", library_str, symbol_name, address);
                return;
            }
            case symbol_function: {
                for (unsigned i = 0; i < param_count; i++) {
                    if (param_list[i].type == param_void) {
                        break;
                    }
                    snprintf(buffer, ARRAY_SIZE(buffer), (i == 0 ? "%s %s" : ", %s %s"), XbSDB_ParamToString(param_list[i].type), param_list[i].name);
                    size_t buffer_count = strnlen(buffer, ARRAY_SIZE(buffer));
                    if (param_size + buffer_count >= ARRAY_SIZE(param_output)) {
                        printf("ERROR: param_size(%zu) + buffer_count(%zu) is too long to be stored in param_output(%zu)\n", param_size, buffer_count, ARRAY_SIZE(param_output));
                        break;
                    }
                    strncat(param_output, buffer, buffer_count);
                    param_size += buffer_count;
                }
                printf("%.8s__FUN__%s__%s(%s) = 0x%08x\n", library_str, XbSDB_CallingConventionToString(call_type), symbol_name, param_output, address);
                return;
            }
            default: {
                printf("%.8s__UNK__%s = 0x%08x\n", library_str, symbol_name, address);
                return;
            }
        }
    }
    printf("%.8s__%s = 0x%08x\n", library_str, symbol_name, address);
}

int main(int argc, char const* argv[])
{
    bool bVerbose = false;
    const char* xbe_path = NULL;
    char const* arg_ = NULL;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            arg_ = argv[i] + 1;
            if (strcmp(arg_, "v") == 0 || strcmp(arg_, "verbose") == 0) {
                bVerbose = true;
            }
            else if (strcmp(arg_, "d") == 0 || strcmp(arg_, "demangle") == 0) {
                bReverseMangle = false;
            }
            else if (strcmp(arg_, "e") == 0 || strcmp(arg_, "extendinfo") == 0) {
                bExtendInfo = true;
            }
        }
        else {
            if (xbe_path == NULL) {
                xbe_path = argv[i];
            }
            else {
                fprintf(stderr, "usage: %s xbefile [-v -verbose] [-d -demangle] [-e -extendinfo]\n", argv[0]);
                return 1;
            }
        }
    }

    if (xbe_path == NULL) {
        fprintf(stderr, "usage: %s xbefile [-v -verbose] [-d -demangle] [-e -extendinfo]\n", argv[0]);
        return 1;
    }

    unsigned int version = XbSDB_LibraryVersion();
    if (bVerbose) {
        fprintf(stderr, "Database Version = %x\n", version);
    }

    FILE* fd = fopen(xbe_path, "rb");
    if (fd == NULL) {
        fprintf(stderr, "failed to open %s for reading\n", xbe_path);
        return 1;
    }

    fseek(fd, 0, SEEK_END);
    size_t size = ftell(fd);
    rewind(fd);

    unsigned char* xbe_buffer = malloc(size);
    if (xbe_buffer == NULL) {
        fprintf(stderr, "unable to allocate memory for xbe buffer\n");
        return 1;
    }
    size_t xbe_size = fread(xbe_buffer, 1, size, fd);
    assert(xbe_size == size);
    if (memcmp(xbe_buffer, "XBEH", 4) != 0) {
        fprintf(stderr, "invalid xbe header\n");
        free(xbe_buffer);
        return 1;
    }

    XbSDB_SetOutputMessage(&msg_cb);

    if (bVerbose) {
        XbSDB_SetOutputVerbosity(XB_OUTPUT_MESSAGE_DEBUG);
    }

    XbSDBLibraryHeader lib_header = {
        .count = XbSDB_GenerateLibraryFilter(xbe_buffer, NULL),
        .filters = malloc(lib_header.count * sizeof(XbSDBLibrary))
    };
    if (!lib_header.filters) {
        fprintf(stderr, "unable to allocate memory for lib_header.filters \n");
        free(xbe_buffer);
        return 1;
    }
    XbSDB_GenerateLibraryFilter(xbe_buffer, &lib_header);

    if (bVerbose) {
        fprintf(stderr, "%u libraries\n", lib_header.count);
        for (unsigned int i = 0; i < lib_header.count; i++) {
            fprintf(stderr, "  %.8s\n", lib_header.filters[i].name);
        }
    }

    XbSDBSectionHeader sect_header = {
        .count = XbSDB_GenerateSectionFilter(xbe_buffer, NULL, 1),
        .filters = malloc(sect_header.count * sizeof(XbSDBSection))
    };
    if (!sect_header.filters) {
        fprintf(stderr, "unable to allocate memory for sect_header.filters \n");
        free(lib_header.filters);
        free(xbe_buffer);
        return 1;
    }
    XbSDB_GenerateSectionFilter(xbe_buffer, &sect_header, 1);

    if (bVerbose) {
        fprintf(stderr, "%u sections\n", sect_header.count);
        for (unsigned int i = 0; i < sect_header.count; i++) {
            fprintf(stderr, "  %.8s\n", sect_header.filters[i].name);
        }
    }

    XbSDBContextHandle ctx;
    bool status = XbSDB_CreateContext(&ctx,
                                      reg_cb,
                                      lib_header,
                                      sect_header,
                                      XbSDB_GetKernelThunkAddress(xbe_buffer));
    assert(status == 1);
    XbSDBContext_ScanManual(ctx);
    XbSDBContext_ScanAllLibraryFilter(ctx);
    XbSDBContext_RegisterXRefs(ctx);
    XbSDBContext_Release(ctx);

    free(lib_header.filters);
    free(sect_header.filters);
    free(xbe_buffer);
    return 0;
}
