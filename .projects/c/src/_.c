
#include <stdio.h>

#include "_.h"

int alive;

int countdown;

int exit_code;

int startup() {
    printf("Starting up...\n");
    alive = 1;
    countdown = 3;
    return 1;
}

int running() {
    printf("Countdown: %d...\n", countdown);
    
    countdown -= 1;
    
    if (countdown > 0) {
        alive = 1;
    } else {
        alive = 0;
    }

    return alive;
}

int shutdown() {
    exit_code = 0;
    printf("Shutting down with: %d\n", exit_code);
    return exit_code;
}
