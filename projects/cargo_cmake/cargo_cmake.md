# cargo_cmake

```
.cmake/
	config.cmake
bin/
	c/
		_.c
	cc/
		_.cc
inc/
	_/
		_.h
	c/
		_.h
	cc/
		_.h
lib/
	c/
		_.c
	cc/
		_.cc
mod/
	_.cc
src/
	bin/
		_.rs
	lib/
		_.rs
CMakeLists.txt
Cargo.toml
build.rs
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

- `bin/c/c.c`

```c
#include "_.h"

int main() {
    c_run();
    return 0;
}
```

- `bin/cc/cc.cc`

```cpp
#include "_.h"

int main() {
    cc_run();
    return 0;
}
```

- `inc/_/_.h`

```c
#pragma once

#define println(...) printf(__VA_ARGS__), printf("\n")
```

- `inc/c/_.h`

```c
#include "_/_.h"

void c_run();

void c_hello();

#ifdef __cplusplus
extern "C" {
#endif

void c_from_cc();

#ifdef __cplusplus
}
#endif
```

- `inc/cc/_.h`

```cpp
#include "_/_.h"

void cc_run();

void cc_hello();

#ifdef __cplusplus
extern "C" {
#endif

void cc_from_c();
void mod_from_c();

#ifdef __cplusplus
}
#endif
```

- `lib/c/_.c`

```c
#include <stdio.h>

#include "_.h"

#include "cc/_.h"

void c_run() {
    c_hello();
    cc_from_c();
    mod_from_c();
}

void c_hello() {
    println("Hello C");
}

void c_from_cc() {
    println("Hello C from C++");
}
```

- `lib/cc/_.cc`

```cpp
#include <cstdio>

#include "_.h"

#include "c/_.h"

import _;

void cc_run() {
    cc_hello();
    mod_hello();
    c_from_cc();
}

void cc_hello() {
    println("Hello C++");
}

void cc_from_c() {
    println("Hello C++ from C");
}
```

- `mod/_.cc`

```cpp
module;

#include <cstdio>

#include "_.h"

export module _;

export void mod_hello() {
    println("Hello C++ Module");
}

export void mod_from_c() {
    println("Hello C++ Module from C");
}
```

- `src/bin/_.rs`

```rust
fn main() {
    lib::run();
}
```

- `src/lib/_.rs`

```rust
unsafe extern "C" {
    unsafe fn c_from_rs();
    unsafe fn cc_from_rs();
    unsafe fn mod_from_rs();
}

pub fn run() {
    println!("Hello Rust");

    unsafe {
        c_from_rs();
        cc_from_rs();
        mod_from_rs();
    }
}
```

- `CMakeLists.txt`

```cmake

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
target_sources(cc_lib
    PUBLIC FILE_SET CXX_MODULES
    FILES ${cc_mod_files}
)

# LIBRARY

add_library(lib
    $<TARGET_OBJECTS:c_lib>
    $<TARGET_OBJECTS:cc_lib>
)

# C BINARY

foreach(bin_file ${c_bin_files})
    get_filename_component(bin_name ${bin_file} NAME_WLE)
    add_executable(${bin_name} ${bin_file})
    target_include_directories(${bin_name} PRIVATE inc/c)
    target_link_libraries(${bin_name} lib)
endforeach()

# C++ BINARY

foreach(bin_file ${cc_bin_files})
    get_filename_component(bin_name ${bin_file} NAME_WLE)
    add_executable(${bin_name} ${bin_file})
    target_include_directories(${bin_name} PRIVATE inc/cc)
    target_link_libraries(${bin_name} lib)
endforeach()
  
install(TARGETS lib DESTINATION .)
```

- `Cargo.toml`

```toml
[package]
name = "cargo_cmake"
version = "0.1.0"
edition = "2024"
default-run = "_"

[[bin]]
name = "_"
path = "src/bin/_.rs"

[lib]
name = "lib"
path = "src/lib/_.rs"

[build-dependencies]
cmake = "*"
```

- `build.rs`

```rust
#![allow(unused_macros)]

use cmake::Config;

macro_rules! warning {
    ($($tokens: tt)*) => {
        println!("cargo::warning={}", format!($($tokens)*))
    }
}

fn main() {
    let dst = Config::new(".").build();

    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=static=lib");
}
```

- `cmake.sh`

```sh
cmake -S . -B .cmake/target &&
cmake --build .cmake/target &&
if [ $# -ne 0 ]; then
    .cmake/output/$1
fi
```

- `rebuild.sh`

```sh
rm -rf .cmake/target

cmake -S . -B .cmake/target &&
cmake --build .cmake/target &&
if [ $# -ne 0 ]; then
    .cmake/output/$1
fi
```
