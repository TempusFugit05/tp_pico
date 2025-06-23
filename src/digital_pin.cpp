#include "gpio.h"

#include "digital_pin.h"

tp::d_pin::d_pin(tp::gpio_number pin) : tp::gpio(pin, tp::gpio::function::SIO){}

void tp::d_pin::set_direction(tp::d_pin::direction set_direction) const
{
    set_action((tp::gpio_action)set_direction);
}

void tp::d_pin::flip_output() const
{
    set_action(tp::gpio_action::GPIO_OUT_XOR);
}

void tp::d_pin::set_output(bool value) const
{
    set_action(value ? tp::gpio_action::GPIO_OUT_SET : tp::gpio_action::GPIO_OUT_CLEAR);
}

bool tp::d_pin::input_read() const
{
    return get_action(tp::gpio_action::GPIO_IN);
}

void tp::d_pin::set_action(tp::gpio_action sio_register, uint32_t value) const
{
    *(uint32_t*)(tp::register_offsets::sio + (uint32_t)sio_register) |= value << pin;
}

uint32_t tp::d_pin::get_action(tp::gpio_action sio_register) const
{
    return (*(uint32_t*)(tp::register_offsets::sio + (uint32_t)sio_register) & (1 << pin)) >> pin;
}