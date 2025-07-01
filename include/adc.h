#ifndef ADC_H
#define ADC_H

#include "gpio.h"

namespace tp
{
    #define ADC_RESOLUTION_BITS (12)
 
    class adc : gpio
    {
        public:
            struct registers
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
                GPIO_26 = (uint32_t)gpio::pin_number::GPIO_26 - 26,
                GPIO_27 = (uint32_t)gpio::pin_number::GPIO_27 - 26,
                GPIO_28 = (uint32_t)gpio::pin_number::GPIO_28 - 26,
                GPIO_29 = (uint32_t)gpio::pin_number::GPIO_29 - 26,
                TEMP_SENSOR = 30 - 26,
            };

            adc(const adc_pin gpio_number);
            
            /**
             * @brief Enable the adc peripheral.
             * 
             * @param enable true to enable adc, false to disable.
             * 
             * @warning Disabling the adc will disable measuring from all pins.
             */
            static void enable(bool enable);

            /**
             * @brief Start an adc measurement.
             */
            void start_measurement() const;

            /**
             * @brief Check if the measurement is done.
             * 
             * @return true if measurement is done.
             * @return false if measurement is still ongoing.
             */
            bool is_ready() const;

            /**
             * @brief Read the adc measurement in raw form (0 - 4095).
             * 
             * @return The value measurement.
             */
            uint32_t read_raw() const;

            /**
             * @brief Read the adc measurement as a float between 0 - 1.
             * 
             * @return The measurement as a float between 0 (0 volt) - 1 (3.3 volt).
             */
            float read() const;
    };

} // namespace tp

#endif // ADC_H