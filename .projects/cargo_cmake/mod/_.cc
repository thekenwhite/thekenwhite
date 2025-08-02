
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

export extern "C" void mod_from_rs() {
    println("Hello C++ Module from Rust");
}
