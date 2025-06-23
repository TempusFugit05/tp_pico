#ifndef ADC_H
#define ADC_H

#include "gpio.h"

namespace tp
{
    #define ADC_RESOLUTION_BITS (12)

    struct adc_registers
    {
        public:
            static uint32_t* const cs;
            static uint32_t* const result;
            static uint32_t* const fcs;
            static uint32_t* const fifo;
            static uint32_t* const div;
            static uint32_t* const intr; // See fc_clock_sources for available clock sources.
            static uint32_t* const inte;
            static uint32_t* const intf;
            static uint32_t* const ints;
    };

    enum class cs_bits
    {
        EN = 0, // Start adc peripheral
        TS_EN = 1, // Start temperature sensor.
        START_ONCE = 2, // Start single conversion.
        START_MANY = 3, // Start continueous conversions.
        READY = 8, // 1 if a conversion was completed.
        ERR = 9, // 1 if there was an error when making adc conversion.
        ERR_STICKY = 10,
        AINSEL = 12, // Select input for sampling (bits 12 - 14).
        ROBIN = 16, // Allows to sample multiple inputs in a round-robin fasion. 1 bit per channel (bits 16 - 20).
    };

    enum class adc_pin
    {
        GPIO_26 = (uint32_t)gpio_number::GPIO_26,
        GPIO_27 = (uint32_t)gpio_number::GPIO_27,
        GPIO_28 = (uint32_t)gpio_number::GPIO_28,
        GPIO_29 = (uint32_t)gpio_number::GPIO_29,
    };
 
    class adc
    {
        private:
            uint32_t gpio_number;

        public:
            adc(const adc_pin gpio_number);
            void enable(bool start) const;
            void start_conversion() const;
            bool is_ready() const;
            uint32_t read_raw() const;
            float read() const;
    };

} // namespace tp

#endif // ADC_H