
#include <iostream>

#include "_.h"

bool alive;

int countdown;

int exit_code;

bool startup() {
    std::cout << "Starting up..." << std::endl;
    alive = true;
    countdown = 3;
    return true;
}

bool running() {
    std::cout << "Countdown: " << countdown << "..." << std::endl;
    
    countdown -= 1;
    
    if (countdown > 0) {
        alive = true;
    } else {
        alive = false;
    }

    return alive;
}

int shutdown() {
    exit_code = 0;
    std::cout << "Shutting down with: " << exit_code << std::endl;
    return exit_code;
}
