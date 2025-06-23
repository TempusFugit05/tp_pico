#ifndef CLOCK_H
#define CLOCK_H

#include "pico_types.h"
#include "pico_system.h"

namespace tp
{
    // Clock sources for the frequency counter (bits 0 - 7)
    enum class fc_clock_sources
    {
        NO_SOURCE = 0x00,
        PLL_SYS_PRIMARY = 0x01,
        PLL_USB_PRIMARY = 0x02,
        ROSC = 0x03,
        ROSC_PH = 0x04,
        XOSC = 0x05,
        GPIN0 = 0x06,
        GPIN1 = 0x07,
        REF = 0x08,
        SYS = 0x09,
        PERI = 0x0a,
        USB = 0x0b,
        ADC = 0x0c,
        RTC = 0x0d,
    };

    enum class  fc0_status_bits
    {
        PASS = 0,
        DONE = 4,
        RUNNING = 8,
        WAITING = 12,
        FAIL = 16,
        SLOW = 20,
        FAST = 24,
        DIED = 28,
    };

    // clock frequency counter
    struct fc
    {
        public:
            static uint32_t* const ref;
            static uint32_t* const min_hrz;
            static uint32_t* const max_hrz;
            static uint32_t* const delay;
            static uint32_t* const interval;
            static uint32_t* const src; // See fc_clock_sources for available clock sources.
            static uint32_t* const status;
            static uint32_t* const result;
    };

    class tp::system::clock
    {
        public:
            static uint32_t get_ref_clock_freq();
            static void set_accuracy(const uint32_t accuracy);
            static void set_ref_frequency(const uint32_t frequency);
            static void start_measurement(fc_clock_sources source);
            static bool frequency_measure_done();
            static float get_frequency(fc_clock_sources source);
    };

} // namespace tp


#endif // CLOCK_H