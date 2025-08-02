
cmake_minimum_required(VERSION 4.0)

project(cmake)

include(.cmake/config.cmake)

file(GLOB bin_files bin/*)

include_directories(inc)

file(GLOB_RECURSE lib_files lib/*)

add_library(lib ${lib_files})

file(GLOB_RECURSE mod_files mod/*)

add_library(mod)

target_sources(mod   
    PUBLIC FILE_SET CXX_MODULES
    FILES ${mod_files}
)

target_link_libraries(lib mod)

foreach(bin_file ${bin_files})
    get_filename_component(bin_name ${bin_file} NAME_WLE)
    add_executable(${bin_name} ${bin_file})
    target_link_libraries(${bin_name} lib)
endforeach()
