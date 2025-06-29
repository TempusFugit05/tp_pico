#include <stdint.h>

#include "gpio.h"
#include "io_bank0.h"
#include "interrupt.h"

tp::gpio::gpio(tp::gpio::pin_number gpio_number) : pin(gpio_number){}

tp::gpio::gpio(tp::gpio::pin_number gpio_number, tp::gpio::function gpio_function) : gpio(gpio_number)
{
    set_function(gpio_function);
}

void tp::gpio::set_function(tp::gpio::function gpio_function) const
{
    const uint32_t gpio_control_offset = (pin * 8) + 4;
    *(uint32_t*)(tp::register_offsets::bank0 + gpio_control_offset) = (uint32_t)gpio_function;
}

tp::gpio::pin_number tp::gpio::get_gpio_number() const
{
    return (tp::gpio::pin_number)pin;
}

void tp::gpio::set_isr(const uint32_t interrupt_mask, const tp::isr isr)
{
    tp::set_gpio_isr(interrupt_mask, isr, pin);
}

void tp::gpio::remove_isr(const uint32_t interrupt_mask)
{
    tp::remove_gpio_isr(interrupt_mask, pin);
}