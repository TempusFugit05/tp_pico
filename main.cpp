#include <stdio.h>
#include <inttypes.h>

#include "tp_pico.h"
#include "pico_system.h"
#include "clock.h"
#include "digital_pin.h"
#include "interrupt.h"

void test_irq()
{
    printf("PRESSED\n");
}

void test_irq2()
{
    printf("DEPRESSED :(\n");
}

int main()
{
    tp::d_pin intest = tp::d_pin(tp::gpio::pin_number::GPIO_14);
    intest.set_isr(tp::gpio::irq_mask::EDGE_HIGH, test_irq);
    intest.set_isr(tp::gpio::irq_mask::EDGE_LOW, test_irq2);

    while (true)
    {
        printf("I AM ALIVE\n");
    }
}