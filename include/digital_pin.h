#ifndef DIGITAL_PIN_H
#define IGITAL_PIN_H

#include "gpio.h"

namespace tp
{

    class d_pin : public tp::gpio
    {
        public:
            enum class action // SIO REGISTERS
            {
                GPIO_IN = 0x004, // Input value for gpio.
                GPIO_OUT = 0x010, // The output value of the gpio pin.
                GPIO_OUT_SET = 0x014, // Set gpio high.
                GPIO_OUT_CLEAR = 0x018, // Set gpio low.
                GPIO_OUTPUT_ENABLE_SET = 0x024, // Set gpio to output.
                GPIO_OUTPUT_ENABLE_CLEAR = 0x028, // Set gpio to input.
                GPIO_OUTPUT_ENABLE_XOR = 0x02, // Flip gpio set_direction (input -> output) || (output -> input).
                GPIO_OUT_XOR = 0x1c, // Flip gpio state (high -> low) || (low -> high).
            };

            enum class direction
            {
                INPUT = (uint32_t)action::GPIO_OUTPUT_ENABLE_CLEAR,
                OUTPUT = (uint32_t)action::GPIO_OUTPUT_ENABLE_SET,
                FLIP = (uint32_t)action::GPIO_OUT_XOR,
            };

            d_pin(tp::gpio::pin_number pin);

            /**
             * @brief Set the input direction of the gpio.
             * 
             * @param set_direction The input direction.
             */
            void set_direction(tp::d_pin::direction set_direction) const;

            /**
             * @brief Enable or disable the output of the gpio. 
             * 
             * @param enable true to enable, false to disable.
             * 
             * @note Only valid when input direction is output.
             */
            void set_output(bool enable) const;

            /**
             * @brief Perform a raw action on the gpio pin.
             * 
             * @param action The action to be performed.
             */
            void set_action(tp::d_pin::action action) const;

            /**
             * @brief Flip the input / output direction of the gpio.
             */
            void flip_output() const;

            /**
             * @brief Read the input value of the gpio.
             * 
             * @return true level is high
             * @return false level is low
             */
            bool input_read() const;

            /**
             * @brief Get the value of a gpio action register.
             * 
             * @param action The action register to read.
             * @return The value of the gpio in the target register.
             */
            bool get_action(tp::d_pin::action action) const;
    };

} // namespace tp


#endif // IGITAL_PIN_H