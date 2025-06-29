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
            static uint32_t const reset;
            static uint32_t const bank0;
            static uint32_t const adc;
            static uint32_t const pwm;
            static uint32_t const clock;
            static uint32_t const sio; // See fc_clock_sources for available clock sources.
            static uint32_t const cortex;
            static uint32_t const nvic;
    };

    struct memory_offsets
    {
        public:
            static uint32_t const rom;
            static uint32_t const xip;
            static uint32_t const sram;
            static uint32_t const apb;
            static uint32_t const ahb;
            static uint32_t const io_port;
            static uint32_t const cortex;
    };

    enum class core_id
    {
        CORE_0 = 0,
        CORE_1 = 1,
    };

} // namespace pico

#endif // PICO_TYPES_H