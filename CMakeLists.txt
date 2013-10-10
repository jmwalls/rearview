# base CMakeLists.txt for rearview
cmake_minimum_required (VERSION 2.8)
project (rearview)

# include local modules
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# get local dir paths for generated code
get_filename_component (SRC_DIR src ABSOLUTE)

# set paths
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
if (NOT IS_DIRECTORY ${LIBRARY_OUTPUT_PATH})
  file (MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})
endif ()

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
if (NOT IS_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
  file (MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
endif ()

set (INCLUDE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/include)
if (NOT IS_DIRECTORY ${INCLUDE_OUTPUT_PATH})
  file (MAKE_DIRECTORY ${INCLUDE_OUTPUT_PATH})
endif ()

include_directories (${INCLUDE_OUTPUT_PATH})

set (LIBRARY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/lib)
set (EXECUTABLE_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set (INCLUDE_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/include)
set (CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

file(GLOB_RECURSE INCLUDE_FILES RELATIVE ${SRC_DIR} src/*.h*)
foreach(I ${INCLUDE_FILES})
  configure_file(${SRC_DIR}/${I} ${INCLUDE_OUTPUT_PATH}/rearview/${I} @ONLY)
endforeach()

# search through subdirs
add_subdirectory (src)
