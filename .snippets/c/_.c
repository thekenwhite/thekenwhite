
#include <stdio.h>

#define println(...) printf(__VA_ARGS__), printf("\n")

int main() {
    println("Hello C");
    return 0;
}
