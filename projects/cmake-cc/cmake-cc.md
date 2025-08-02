# cmake-cc

```
.cmake/
	config.cmake
bin/
	_.cc
inc/
	_.h
lib/
	_.cc
mod/
	_.cc
CMakeLists.txt
cmake.sh
rebuild.sh
```

- `.cmake/config.cmake`

```cmake
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
```

- `bin/_.cc`

```cpp
#include "_.h"

int main() {
    run();
    return 0;
}
```

- `inc/_.h`

```cpp
#pragma once

#define println(...) printf(__VA_ARGS__), printf("\n")

void run();
```

- `lib/_.cc`

```cpp
#include "_.h"

import _;

void run() {
    hello();    
}
```

- `mod/_.cc`

```cpp
module;

#include <cstdio>

#include "_.h"

export module _;

export void hello() {
    println("Hello, world!");
}
```

- `CMakeLists.txt`

```cmake
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
```

- `cmake.sh`

```sh
cmake -S . -B .cmake/target &&
cmake --build .cmake/target &&
if [ $# -eq 0 ]; then
    .cmake/output/_
else
    .cmake/output/$1
fi
```

- `rebuild.sh`

```sh
rm -rf .cmake/target

cmake -S . -B .cmake/target &&
cmake --build .cmake/target &&
if [ $# -eq 0 ]; then
    .cmake/output/_
else
    .cmake/output/$1
fi
```
