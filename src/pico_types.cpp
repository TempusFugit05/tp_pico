#include "pico_types.h"

namespace tp
{
    uint32_t const tp::register_offsets::reset = 0x4000c000;
    uint32_t const tp::register_offsets::bank0 = 0x40014000;
    uint32_t const tp::register_offsets::adc = 0x4004c000;
    uint32_t const tp::register_offsets::pwm = 0x40050000;
    uint32_t const tp::register_offsets::clock = 0x40008000;
    uint32_t const tp::register_offsets::sio = 0xd0000000; // See fc_clock_sources for available clock sources.
    uint32_t const tp::register_offsets::cortex = 0xe0000000;
    uint32_t const tp::register_offsets::nvic_iser = 0xe1000000;

} // namespace tp
