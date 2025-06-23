#ifndef DIGITAL_PIN_H
#define IGITAL_PIN_H

#include "gpio.h"

namespace tp
{

    enum class gpio_action // SIO REGISTERS
    {
        CPUID = 0x000, // Core identifier, 0 when read from the first core, 1 when read from the second.
        GPIO_IN = 0x004, // Input value for gpio.
        GPIO_OUT = 0x010, // The output value of the gpio pin.
        GPIO_OUT_SET = 0x014, // Set gpio high.
        GPIO_OUT_CLEAR = 0x018, // Set gpio low.
        GPIO_OUTPUT_ENABLE_SET = 0x024, // Set gpio to output.
        GPIO_OUTPUT_ENABLE_CLEAR = 0x028, // Set gpio to input.
        GPIO_OUTPUT_ENABLE_XOR = 0x02, // Flip gpio set_direction (input -> output) || (output -> input).
        GPIO_OUT_XOR = 0x1c, // Flip gpio state (high -> low) || (low -> high).
    };

    class d_pin : tp::gpio
    {
        public:
        enum class direction
        {
            INPUT = (uint32_t)gpio_action::GPIO_OUTPUT_ENABLE_CLEAR,
            OUTPUT = (uint32_t)gpio_action::GPIO_OUTPUT_ENABLE_SET,
            FLIP = (uint32_t)gpio_action::GPIO_OUT_XOR,
        };

            d_pin(tp::gpio_number pin);

            void set_direction(tp::d_pin::direction set_direction) const;
            void set_output(bool value) const;
            void set_action(tp::gpio_action action, uint32_t value=1) const;
            void flip_output() const;

            bool input_read() const;
            uint32_t get_action(tp::gpio_action action) const;
    };

} // namespace tp


#endif // IGITAL_PIN_H