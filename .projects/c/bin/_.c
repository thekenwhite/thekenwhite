
#include "_.h"

int main() {
    int alive = startup();

    while (alive > 0) {
        alive = running();
    }
    
    return shutdown();
}
