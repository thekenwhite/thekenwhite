
cmake_minimum_required(VERSION 4.0)

project(cmake)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/.cmake/output)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/.cmake/output)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/.cmake/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/.cmake/output)

include_directories(inc)

file(GLOB_RECURSE bin_files bin/*)

file(GLOB_RECURSE src_files src/*)

file(GLOB_RECURSE mod_files mod/*)

add_library(src_lib ${src_files})

add_library(mod_lib)

target_sources(mod_lib
    PUBLIC FILE_SET CXX_MODULES
    FILES ${mod_files}
)

foreach(bin_file ${bin_files})
    get_filename_component(bin_name ${bin_file} NAME_WLE)
    add_executable(${bin_name} ${bin_file})
    target_link_libraries(${bin_name} src_lib)
    target_link_libraries(${bin_name} mod_lib)
endforeach()
