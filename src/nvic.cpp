#include "pico_types.h"
#include "binary_helpers.h"

#include "nvic.h"

uint32_t* const tp::nvic::registers::iser =     (uint32_t*)(tp::register_offsets::cortex + 0xe100);
uint32_t* const tp::nvic::registers::icer =     (uint32_t*)(tp::register_offsets::cortex + 0xe180);
uint32_t* const tp::nvic::registers::ispr =     (uint32_t*)(tp::register_offsets::cortex + 0xe200);
uint32_t* const tp::nvic::registers::icpr =     (uint32_t*)(tp::register_offsets::cortex + 0xe280);
uint32_t* const tp::nvic::registers::ipr_base = (uint32_t*)(tp::register_offsets::cortex + 0xe400);
uint32_t* const tp::nvic::registers::vtor =     (uint32_t*)(tp::register_offsets::cortex + 0xed08);

void tp::nvic::enable_interrupt(const tp::nvic::interrupt interrupt)
{
    *tp::nvic::registers::iser |= (1 << (uint32_t)interrupt);
}

void tp::nvic::disable_interrupt(const tp::nvic::interrupt interrupt)
{
    *tp::nvic::registers::icer |= (1 << (uint32_t)interrupt);
}

void tp::nvic::force_interrupt(const tp::nvic::interrupt interrupt)
{
    *tp::nvic::registers::ispr |= (1 << (uint32_t)interrupt);
}

void tp::nvic::clear_pending_interrupt(const tp::nvic::interrupt interrupt)
{
    *tp::nvic::registers::icpr |= (1 << (uint32_t)interrupt);
}

tp::vtable tp::nvic::irq_vtable()
{
    return tp::nvic::interrupt_table() + tp::nvic::VTABLE_IRQ_START;
}

void tp::nvic::assign_isr(const tp::nvic::interrupt interrupt, const tp::isr handler)
{
    irq_vtable()[(uint32_t)interrupt] = handler;
}

tp::vtable tp::nvic::interrupt_table()
{
    constexpr const uint32_t vtor_reg_offset = 7;
    uint32_t offset =  CLEAR_RIGHT(*tp::nvic::registers::vtor, vtor_reg_offset);
    return (tp::vtable)(offset + tp::memory_offsets::sram);
}