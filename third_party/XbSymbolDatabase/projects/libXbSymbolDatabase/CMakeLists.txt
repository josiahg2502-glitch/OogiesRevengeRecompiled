# CMakeList.txt : CMake project for libXbSymbolDatabase.
#
cmake_minimum_required(VERSION 3.10.2)

project(libXbSymbolDatabase LANGUAGES C)

find_package(Threads)

file(GLOB INCLUDES
 "${XBSDB_ROOT_DIR}/include/Xbe.h"
 "${XBSDB_ROOT_DIR}/include/libCallTypes.h"
 "${XBSDB_ROOT_DIR}/include/libParamTypes.h"
 "${XBSDB_ROOT_DIR}/include/libXbSymbolDatabase.h"

# Include xrefs for ABI feature support.
 "${XBSDB_ROOT_DIR}/include/xref/list_xref.h"
 "${XBSDB_ROOT_DIR}/include/xref/d3d8.def"
 "${XBSDB_ROOT_DIR}/include/xref/d3d8ltcg.def"
# "${XBSDB_ROOT_DIR}/include/xref/d3dx8.def" # do we need this?
 "${XBSDB_ROOT_DIR}/include/xref/dsound.def"
 "${XBSDB_ROOT_DIR}/include/xref/jvs.def"
 "${XBSDB_ROOT_DIR}/include/xref/xacteng.def"
 "${XBSDB_ROOT_DIR}/include/xref/xapilib.def"
 "${XBSDB_ROOT_DIR}/include/xref/xgraphic.def"
 "${XBSDB_ROOT_DIR}/include/xref/xnet.def"
# "${XBSDB_ROOT_DIR}/include/xref/xnetn.def" # do we need this?
# "${XBSDB_ROOT_DIR}/include/xref/xnets.def" # do we need this?
 "${XBSDB_ROOT_DIR}/include/xref/xonline.def"
# "${XBSDB_ROOT_DIR}/include/xref/xonlines.def" # do we need this?
)
source_group(TREE ${XBSDB_ROOT_DIR} FILES ${INCLUDES})

file(GLOB HEADERS

 "${XBSDB_ROOT_DIR}/src/lib/internal_db_version.h"
 "${XBSDB_ROOT_DIR}/src/lib/internal_functions.h"
 "${XBSDB_ROOT_DIR}/src/lib/internal_tests.h"
 "${XBSDB_ROOT_DIR}/src/lib/manual_custom.h"
 "${XBSDB_ROOT_DIR}/src/lib/manual_d3d8__ltcg.h"
 "${XBSDB_ROOT_DIR}/src/lib/manual_dsound.h"
 "${XBSDB_ROOT_DIR}/src/lib/manual_jvs.h"
 "${XBSDB_ROOT_DIR}/src/lib/manual_xapilib.h"
 "${XBSDB_ROOT_DIR}/src/OOVPADatabase/OOVPA.h"
 "${XBSDB_ROOT_DIR}/src/OOVPADatabase/OOVPA_databases.h"
)
source_group(TREE ${XBSDB_ROOT_DIR}/src PREFIX header FILES ${HEADERS})

file(GLOB_RECURSE SOURCES
 "${XBSDB_ROOT_DIR}/src/libXbSymbolDatabase.c"
 "${XBSDB_ROOT_DIR}/src/OOVPADatabase/*/*.inl"
 "${XBSDB_ROOT_DIR}/src/OOVPADatabase/*.c"
)
source_group(TREE ${XBSDB_ROOT_DIR} FILES ${SOURCES})

add_library(${PROJECT_NAME} STATIC ${INCLUDES} ${HEADERS} ${SOURCES})

# NOTES:
# Using INTERFACE keyword will not work within the project. Only PUBLIC/PRIVATE keywords does.
target_include_directories(${PROJECT_NAME}
 PUBLIC "$<BUILD_INTERFACE:${XBSDB_ROOT_DIR}/include>"
 PUBLIC "$<INSTALL_INTERFACE:include>"
 PRIVATE "${XBSDB_ROOT_DIR}/src/OOVPADatabase"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)

if(Threads_FOUND)
 target_link_libraries(${PROJECT_NAME} Threads::Threads)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
 C_STANDARD 11
 C_STANDARD_REQUIRED ON
 FOLDER XbSymbolDatabase
)

if(XBSDB_INSTALL_LIB)
 install(DIRECTORY ${XBSDB_ROOT_DIR}/include/
  TYPE INCLUDE
 )
 install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib_shared
  ARCHIVE DESTINATION lib_static
 )
endif()
