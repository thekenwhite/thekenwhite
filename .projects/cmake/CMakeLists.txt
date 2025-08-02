
cmake_minimum_required(VERSION 4.0)

project(cmake)

include(.cmake/config.cmake)

file(GLOB c_bin_files bin/c/*)
file(GLOB cc_bin_files bin/cc/*)

# INCLUDE

include_directories(inc)

# C LIBRARY

file(GLOB_RECURSE c_lib_files lib/c/*)

add_library(c_lib ${c_lib_files})
target_include_directories(c_lib PRIVATE inc/c)

# C++ LIBRARY

file(GLOB_RECURSE cc_lib_files lib/cc/*)
add_library(cc_lib ${cc_lib_files})
target_include_directories(cc_lib PRIVATE inc/cc)

# C++ MODULE

file(GLOB_RECURSE cc_mod_files mod/*)
add_library(cc_mod)
target_sources(cc_mod   
    PUBLIC FILE_SET CXX_MODULES
    FILES ${cc_mod_files}
)
target_include_directories(cc_mod PRIVATE inc/cc)

target_link_libraries(cc_lib cc_mod)

# C BINARY

foreach(bin_file ${c_bin_files})
    get_filename_component(bin_name ${bin_file} NAME_WLE)
    add_executable(${bin_name} ${bin_file})
    target_include_directories(${bin_name} PRIVATE inc/c)
    target_link_libraries(${bin_name} c_lib)
    target_link_libraries(${bin_name} cc_lib)
endforeach()

# C++ BINARY

foreach(bin_file ${cc_bin_files})
    get_filename_component(bin_name ${bin_file} NAME_WLE)
    add_executable(${bin_name} ${bin_file})
    target_include_directories(${bin_name} PRIVATE inc/cc)
    target_link_libraries(${bin_name} c_lib)
    target_link_libraries(${bin_name} cc_lib)
endforeach()
