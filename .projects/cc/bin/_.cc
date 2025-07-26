
#include "_.h"

int main() {
    bool alive = startup();

    while (alive) {
        alive = running();
    }
    
    return shutdown();
}
