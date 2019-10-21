#include <iostream>
#include <stdint.h>

extern "C" uint32_t add(uint32_t, uint32_t);

int main() {

    std::cout << "Hello World!\n";

    std::cout << add(15, 20);

    return 0;
}
