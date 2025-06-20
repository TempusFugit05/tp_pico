#ifndef ADC_H
#define ADC_H

#include "gpio.h"

namespace tp
{
    #define ADC_RESOLUTION_BITS (12)

    enum class adc_register
    {
        CS = (uint32_t)tp::register_offsets::ADC + 0x00, // adc control and status.
        RESULT = (uint32_t)tp::register_offsets::ADC + 0x04, // Result of the last conversion (bits 0 - 11).
        FCS = (uint32_t)tp::register_offsets::ADC + 0x08,
        FIFO = (uint32_t)tp::register_offsets::ADC + 0x0c,
        DIV = (uint32_t)tp::register_offsets::ADC + 0x10,
        INTR = (uint32_t)tp::register_offsets::ADC + 0x14,
        INTE = (uint32_t)tp::register_offsets::ADC + 0x18,
        INTF = (uint32_t)tp::register_offsets::ADC + 0x1c,
        INTS = (uint32_t)tp::register_offsets::ADC + 0x20,
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