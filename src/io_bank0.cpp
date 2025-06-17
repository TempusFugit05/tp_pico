#include "io_bank0.h"

#include "pico_system.h"
#include "pico_types.h"

void tp::io_bank0::reset()
{
    tp::system::reset_peripheral(tp::PERIPHERAL::IO_BANK0);
}

uint32_t tp::io_bank0::gpio_control_offset(int pin)
{
    return (pin * 8) + 4;
}

uint32_t tp::io_bank0::gpio_status_offset(int pin)
{
    return pin * 8;
}

void tp::io_bank0::set_gpio_function(int pin, tp::GPIO_FUNCTION function)
{
    *(uint32_t*)((uint32_t)tp::register_offsets::BANK0 + gpio_control_offset(pin)) = (uint32_t)function;
}

void tp::io_bank0::set_sio_register(int pin, tp::GPIO_ACTION sio_register, uint32_t value)
{
    *(uint32_t*)((uint32_t)tp::register_offsets::SIO + (uint32_t)sio_register) |= value << pin;
}

uint32_t tp::io_bank0::get_sio_register(int pin, tp::GPIO_ACTION sio_register)
{
    return *(uint32_t*)((uint32_t)tp::register_offsets::SIO + (uint32_t)sio_register);
}