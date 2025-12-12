#include <cstdio>
#include <pico_system.h>

#include "pico/stdlib.h"
#include "tp_pico.h"

[[noreturn]] int main() {
    stdio_init_all();

    while (true) {
        printf("Hello World\n");
        tp::system::wait_ms(1000);
    }
}