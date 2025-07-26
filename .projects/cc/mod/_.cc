
module;

#include <iostream>

export module _;

import type;

export {
    void run();
    void hello();
}

void run() {
    hello();
}

void hello() {
    strv hello = "Hello, World!";
    std::cout << hello << std::endl;
}
