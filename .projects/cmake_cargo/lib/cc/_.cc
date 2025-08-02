
#include <cstdio>

#include "_.h"

#include "c/_.h"

#include "rs/_.h"

import _;

void cc_run() {
    cc_hello();
    mod_hello();
    c_from_cc();
    rs_from_cc();
}

void cc_hello() {
    println("Hello C++");
}

void cc_from_c() {
    println("Hello C++ from C");
}

extern "C" void cc_from_rs() {
    println("Hello C++ from Rust");
}
