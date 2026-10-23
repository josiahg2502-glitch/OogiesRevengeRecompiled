# CMakeList.txt : generate all projects
#
cmake_minimum_required(VERSION 3.10.2)

add_subdirectory("libXbSymbolDatabase")

if(XBSDB_BUILD_CLI)
 add_subdirectory("cli")
endif()

if(XBSDB_BUILD_UNITTEST)
 add_subdirectory("UnitTest")
endif()
