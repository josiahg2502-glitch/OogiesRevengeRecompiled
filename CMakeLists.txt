cmake_minimum_required(VERSION 3.20)
# llvm-mingw's resource compiler sits next to its C++ compiler (it is not on PATH)
if(CMAKE_CXX_COMPILER AND NOT EXISTS "${CMAKE_RC_COMPILER}")
    get_filename_component(_bin "${CMAKE_CXX_COMPILER}" DIRECTORY)
    set(CMAKE_RC_COMPILER "${_bin}/windres.exe" CACHE FILEPATH "" FORCE)
endif()
project(OogiesRevenge CXX RC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/generated/funcs.h")
    message(FATAL_ERROR "Run xboxrecomp/codegen.py first (see README.md)")
endif()

file(GLOB GENERATED_SOURCES CONFIGURE_DEPENDS generated/*.cpp)
file(GLOB_RECURSE RUNTIME_SOURCES CONFIGURE_DEPENDS xboxrecomp/runtime/*.cpp)

add_executable(OogiesRevenge ${GENERATED_SOURCES} ${RUNTIME_SOURCES} OogiesRevenge.rc)
# Each generated shard takes gigabytes to compile: at most 4 at once, so a full rebuild cannot run a 16 GB PC out of
# memory (ninja's default of one job per CPU did).
set_property(GLOBAL PROPERTY JOB_POOLS heavy_compile=4)
set_property(TARGET OogiesRevenge PROPERTY JOB_POOL_COMPILE heavy_compile)
target_include_directories(OogiesRevenge PRIVATE xboxrecomp/runtime generated)
set(CMAKE_RC_FLAGS "${CMAKE_RC_FLAGS} -I ${CMAKE_CURRENT_SOURCE_DIR}")
# The generated code is huge; -O1 keeps build times sane until profiling says otherwise.
set_source_files_properties(${GENERATED_SOURCES} PROPERTIES COMPILE_OPTIONS "-O1")
target_link_options(OogiesRevenge PRIVATE -static -mwindows)  # no console window; stderr goes to UserData/log.txt
target_link_libraries(OogiesRevenge PRIVATE d3d11 dxgi dwmapi user32 gdi32 ole32 winmm shell32 bcrypt comdlg32)

add_executable(flags_test xboxrecomp/tests/flags_test.cpp)
target_include_directories(flags_test PRIVATE xboxrecomp/runtime)
target_link_options(flags_test PRIVATE -static)
add_executable(adpcm_test xboxrecomp/tests/adpcm_test.cpp)
target_include_directories(adpcm_test PRIVATE xboxrecomp/runtime)
target_link_options(adpcm_test PRIVATE -static)
