#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#include "hardware/irq.h"
#include "pico/stdlib.h"
#include "tp_pico.h"
#include "pico_system.h"

tp::gpio test_output = tp::gpio(25);
uint32_t counter = 0;

void test_irq()
{
    test_output.output_flip();
    printf("TRIGGERED %u\n", counter);
    counter ++;
    printf("1: %d | %d\n", *(uint32_t*)((uint32_t)tp::register_offsets::BANK0 + 0x0f4), 1 << 27);
    printf("2: %d | %d\n\n", *(uint32_t*)((uint32_t)tp::register_offsets::BANK0 + 0x104), 1 << 27);
    *(uint32_t*)((uint32_t)tp::register_offsets::BANK0 + 0x0f4) = *(uint32_t*)((uint32_t)tp::register_offsets::BANK0 + 0x104); // Enable interrupt for pin 14 when HIGH (INTR1 Register)
}

int main()
{
    test_output.set_function(tp::GPIO_FUNCTION::SIO);
    test_output.direction(tp::GPIO_INPUT_DIRECTION::OUTPUT);

    stdio_init_all();
    irq_set_enabled(IO_IRQ_BANK0, true);
    irq_set_exclusive_handler(13, test_irq);
    // *(uint32_t*)((uint32_t)tp::register_offsets::BANK0 + 0x0f4) = 1 << 27; // Enable interrupt for pin 14 when HIGH (INTR1 Register)
    printf("REBOOT");
    *(uint32_t*)((uint32_t)tp::register_offsets::BANK0 + 0x104) = 1 << 27; // Enable interrupt for pin 14 when HIGH (PROC0_INTE1 Register)

    while (true)
    {
    }
}