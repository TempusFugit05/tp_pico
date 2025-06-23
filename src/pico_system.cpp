#include "pico_system.h"
#include "pico_types.h"

tp::core_id tp::system::get_core_id()
{
    return (tp::core_id)*(uint32_t*)tp::register_offsets::sio;
}

void tp::system::interrupt_enable(tp::interrupt_register interrupt_register)
{
    *(uint32_t*)(tp::register_offsets::cortex + (uint32_t)tp::register_offsets::nvic_iser) = 1 << (uint32_t)interrupt_register;
}

void tp::system::reset_peripheral(tp::peripheral peripheral, uint32_t value)
{
    *(uint32_t*)(tp::register_offsets::reset) &= ~(value << (uint32_t)peripheral); // Reset the peripheral.
    while(!(tp::register_offsets::reset + (uint32_t)tp::reset_register::DONE & (value << (uint32_t)peripheral))); // Wait for reset to finish.
}