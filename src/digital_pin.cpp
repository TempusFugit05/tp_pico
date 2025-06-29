#include "gpio.h"

#include "digital_pin.h"

tp::d_pin::d_pin(tp::gpio::pin_number gpio_number) : tp::gpio(gpio_number, tp::gpio::function::SIO){}

void tp::d_pin::set_direction(tp::d_pin::direction set_direction) const
{
    set_action((tp::d_pin::action)set_direction);
}

void tp::d_pin::flip_output() const
{
    set_action(tp::d_pin::action::GPIO_OUT_XOR);
}

void tp::d_pin::set_output(bool value) const
{
    set_action(value ? tp::d_pin::action::GPIO_OUT_SET : tp::d_pin::action::GPIO_OUT_CLEAR);
}

bool tp::d_pin::input_read() const
{
    return get_action(tp::d_pin::action::GPIO_IN);
}

void tp::d_pin::set_action(tp::d_pin::action sio_register) const
{
    *(uint32_t*)(tp::register_offsets::sio + (uint32_t)sio_register) |= 1 << pin;
}

bool tp::d_pin::get_action(tp::d_pin::action sio_register) const
{
    return (*(uint32_t*)(tp::register_offsets::sio + (uint32_t)sio_register) & (1 << pin)) >> pin;
}