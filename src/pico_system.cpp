#include "pico_system.h"
#include "pico_types.h"

void tp::system::interrupt_enable(tp::INTERRUPT_REGISTER interrupt_register)
{
    *(uint32_t*)((uint32_t)tp::register_offsets::CORTEX + (uint32_t)tp::register_offsets::NVIC_ISER) = 1 << (uint32_t)interrupt_register;
}

void tp::system::reset_peripheral(tp::PERIPHERAL peripheral, uint32_t value)
{
    *(uint32_t*)((uint32_t)tp::register_offsets::RESET) &= ~(value << (uint32_t)peripheral); // Reset the peripheral.
    while(!((uint32_t)tp::register_offsets::RESET + (uint32_t)tp::RESET_REGISTER::DONE & (value << (uint32_t)peripheral))); // Wait for reset to finish.
}

// tp::system system = tp::system();