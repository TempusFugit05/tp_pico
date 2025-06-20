#include <stdint.h>

#include "gpio.h"
#include "io_bank0.h"

tp::gpio::gpio(int gpio_number) : gpio_number(gpio_number){}

tp::gpio::gpio(int gpio_number, tp::GPIO_FUNCTION function) : gpio(gpio_number)
{
    set_function(function);
}

void tp::gpio::set_function(tp::GPIO_FUNCTION function) const
{
    const uint32_t gpio_control_offset = (gpio_number * 8) + 4;
    *(uint32_t*)((uint32_t)tp::register_offsets::BANK0 + gpio_control_offset) = (uint32_t)function;
}

void tp::gpio::direction(tp::GPIO_INPUT_DIRECTION direction) const
{
    io_bank0::set_sio_register(gpio_number, (tp::GPIO_ACTION)direction);
}

void tp::gpio::output_flip() const
{
    io_bank0::set_sio_register(gpio_number, tp::GPIO_ACTION::GPIO_OUT_XOR);
}

void tp::gpio::output_set(bool value) const
{
    io_bank0::set_sio_register(gpio_number, value ? tp::GPIO_ACTION::GPIO_OUT_SET : tp::GPIO_ACTION::GPIO_OUT_CLEAR);
}

bool tp::gpio::input_read() const
{
    return (io_bank0::get_sio_register(gpio_number, tp::GPIO_ACTION::GPIO_IN) & (1 << gpio_number)) >> gpio_number;
}

uint32_t tp::gpio::get_gpio_number() const
{
    return gpio_number;
}