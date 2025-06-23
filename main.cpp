#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#include "hardware/irq.h"
#include "pico/stdlib.h"
#include "tp_pico.h"
#include "pico_system.h"
#include "clock.h"
#include "digital_pin.h"


void test_irq()
{
    printf("TRIGGERED\n");
    *(uint32_t*)(tp::register_offsets::bank0 + 0x0f4) &= 1 << 27; // Enable interrupt for pin 14 when HIGH (INTR1 Register)
}

int main()
{
    tp::pwm test = tp::pwm(tp::gpio_number::GPIO_25, 100);
    test.set_level(100);
    test.enable(true);

    tp::d_pin intest = tp::d_pin(tp::gpio_number::GPIO_14);
    intest.set_direction(tp::d_pin::direction::INPUT);

    stdio_init_all();
    irq_set_enabled(IO_IRQ_BANK0, true);
    irq_set_exclusive_handler(13, test_irq);
    
    *(uint32_t*)((uint32_t)tp::register_offsets::bank0 + 0x104) = 1 << 27; // Enable interrupt for pin 14 when HIGH (PROC0_INTE1 Register)
    
    while (true)
    {
        // test.enable(intest.input_read());
        // printf("%f\n\n", tp::system::clock::get_frequency(tp::fc_clock_sources::SYS));
        // sleep_ms(1000);
    }
}