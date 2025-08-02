
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
