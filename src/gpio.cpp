#include <stdint.h>

#include "gpio.h"
#include "io_bank0.h"

tp::gpio::gpio(tp::gpio_number pin) : pin((uint32_t)pin){}

tp::gpio::gpio(tp::gpio_number pin, tp::gpio::function function) : gpio(pin)
{
    set_function(function);
}

void tp::gpio::set_function(tp::gpio::function function) const
{
    const uint32_t gpio_control_offset = (pin * 8) + 4;
    *(uint32_t*)(tp::register_offsets::bank0 + gpio_control_offset) = (uint32_t)function;
}

tp::gpio_number tp::gpio::get_gpio_number() const
{
    return (tp::gpio_number)pin;
}