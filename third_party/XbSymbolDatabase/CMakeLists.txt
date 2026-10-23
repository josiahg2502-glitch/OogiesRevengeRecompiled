# CMakeList.txt : CMake solution for XbSymbolDatabase.
#
cmake_minimum_required(VERSION 3.10.2)

project(XbSymbolDatabase)

# Enforce warnings as errors to verify projects are in sync and doesn't have hidden warnings.
if(${CMAKE_VERSION} VERSION_LESS "3.24.0")
 if(MSVC)
  set(COMPILE_WARNING_AS_ERROR "/WX")
 else()
  include(CheckCCompilerFlag)
  check_c_compiler_flag("-Werror-all" WERRALL)
  check_c_compiler_flag("-Werror" WERR)
  if(WERRALL)
   set(COMPILE_WARNING_AS_ERROR "-Werror-all")
  elseif(WERR)
   set(COMPILE_WARNING_AS_ERROR "-Werror")
  else()
   message(WARNING "Unable enforce compile warnings as errors.")
  endif()
 endif()
 add_compile_options(${COMPILE_WARNING_AS_ERROR})
else()
 set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
endif()

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
 set(XBSDB_DEFAULT_CONFIGS ON)
 enable_testing()
 # force disable unit test for XCode due to missing cuchar header file.
 # TODO: Test XCode again when Apple Clang is at least version 15.
 # NOTE: llvm Clang contain a fix in https://github.com/llvm/llvm-project/commit/311ff3917827131c20d4b8dac4ce0394a2351b94 commit.
 if(XCODE)
  cmake_policy(SET CMP0077 NEW)
  set(XBSDB_BUILD_UNITTEST OFF)
 endif()
else()
 set(XBSDB_DEFAULT_CONFIGS OFF)
endif()

option(XBSDB_INSTALL_LIB "Install libXbSymbolDatabase library" ${XBSDB_DEFAULT_CONFIGS})
option(XBSDB_BUILD_CLI "Build XbSymbolDatabase CLI tool" ${XBSDB_DEFAULT_CONFIGS})
option(XBSDB_BUILD_UNITTEST "Build XbSymbolDatabase Unit Test" ${XBSDB_DEFAULT_CONFIGS})
include(CMakeDependentOption)
cmake_dependent_option(XBSDB_INSTALL_CLI "Install XbSymbolDatabase CLI tool" ${XBSDB_DEFAULT_CONFIGS}
                       "XBSDB_BUILD_CLI" OFF)
cmake_dependent_option(XBSDB_INSTALL_UNITTEST "Install XbSymbolDatabase Unit Test" ${XBSDB_DEFAULT_CONFIGS}
                       "XBSDB_BUILD_UNITTEST" OFF)

# For any optional tools, use list(APPEND XBSDB_INSTALL_TOOLS "tool_name")

if(XBSDB_INSTALL_LIB)
 list(APPEND XBSDB_INSTALL_TOOLS "libXbSymbolDatabase")
endif()

if(XBSDB_INSTALL_CLI)
 list(APPEND XBSDB_INSTALL_TOOLS "XbSymbolDatabaseCLI")
endif()

if(XBSDB_INSTALL_UNITTEST)
 list(APPEND XBSDB_INSTALL_TOOLS "XbSymbolDatabaseUnitTest")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(XBSDB_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory("${PROJECT_SOURCE_DIR}/projects")

if(XBSDB_INSTALL_TOOLS)

 if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  install(FILES "LICENSE" "README.md" DESTINATION .)
 else()
  install(FILES "LICENSE" "README.md" DESTINATION "XbSymbolDatabase")
 endif()
endif()
