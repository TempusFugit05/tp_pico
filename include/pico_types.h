#ifndef PICO_TYPES_H
#define PICO_TYPES_H

#include <stdint.h>
namespace tp
{
    typedef void (**vtable)(void);
    typedef void (*isr)(void);

    struct register_offsets
    {
        public:
            constexpr static uint32_t const clock =    0x40008000;
            constexpr static uint32_t const reset =    0x4000c000;
            constexpr static uint32_t const bank0 =    0x40014000;
            constexpr static uint32_t const adc =      0x4004c000;
            constexpr static uint32_t const pwm =      0x40050000;
            constexpr static uint32_t const rosc =     0x40060000;
            constexpr static uint32_t const sio =      0xd0000000; // See fc_clock_sources for available clock sources.
            constexpr static uint32_t const cortex =   0xe0000000;
            constexpr static uint32_t const nvic =     0xe1000000;
    };

    struct memory_offsets
    {
        public:
            constexpr static uint32_t const rom =        0x00000000;
            constexpr static uint32_t const xip =        0x10000000;
            constexpr static uint32_t const sram =       0x20000000;
            constexpr static uint32_t const apb =        0x40000000;
            constexpr static uint32_t const ahb =        0x50000000;
            constexpr static uint32_t const io_port =    0xd0000000;
            constexpr static uint32_t const cortex =     0xe0000000;    
    };

    enum class core_id
    {
        CORE_0 = 0,
        CORE_1 = 1,
    };

} // namespace pico

#endif // PICO_TYPES_H