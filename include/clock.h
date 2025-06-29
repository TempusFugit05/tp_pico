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

    class tp::system::clock
    {
        public:

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

            /**
             * @brief Get the frequency of the reference clock (ref_clk).
             * 
             * @return uint32_t The frequency of the reference clock in hrz.
             * 
             * @todo Find a way to get the actual reference clock frequency instead of a hardcoded value.
             */
            static uint32_t get_ref_clock_freq();

            /**
             * @brief Set the accuracy of the frequency counter.
             * 
             * @param accuracy The accuracy of the measurement (valid values range from 0 - 15).
             * 
             * @details This sets the measurement interval of the measurement. 
             *          Longer intervals give better accuracy.
             *          The default interval is 250us.
             *          The interval is given by 0,96us * 2 ** accuracy.
             */
            static void set_accuracy(const uint32_t accuracy);

            /**
             * @brief Set the reference frequency (the frequency of ref_clk in khz).
             * 
             * @param frequency The frequency of ref_clk. 
             */
            static void set_ref_frequency(const uint32_t frequency);
            
            /**
             * @brief Start the frequency measurement.
             * 
             * @param source The clock to measure.
             */
            static void start_measurement(fc_clock_sources source);

            /**
             * @brief Check if the frequency measurement is done.
             * 
             * @return true if measurement is done.
             * @return false if measurement is still ongoing.
             */
            static bool frequency_measure_done();

            /**
             * @brief Get the frequency of a clock.
             * 
             * @param source The clock to measure.
             * @return The measured frequency in hz.
             */
            static uint32_t get_frequency(fc_clock_sources source);
    };

} // namespace tp


#endif // CLOCK_H