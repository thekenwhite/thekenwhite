
cmake_minimum_required(VERSION 4.0)

project(cmake)

include(.cmake/config.cmake)

file(GLOB c_bin_files bin/c/*)
file(GLOB cc_bin_files bin/cc/*)

include_directories(inc)

file(GLOB_RECURSE c_lib_files lib/c/*)
file(GLOB_RECURSE cc_lib_files lib/cc/*)
