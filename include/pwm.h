#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include "pico_types.h"
#include "gpio.h"

namespace tp
{
    constexpr uint8_t PWM_DIV_MAX_FRACTION = 16;

    enum class PWM_REGISTER
    {
        CSR = 0x00, // Control and status register.
        DIV = 0x04, // Clock divider.
        CTR = 0x08, // PWM counter.
        CC = 0x0c, 
        TOP = 0x10, // Counter wrap.
    };

    enum class PWM_DIV_BITS
    {
        FRAC = 0, // A 4 bit fraction part of the divider (Value is FRAC / 16) (bits 0 - 3).
        INT = 4, // The integer part of the divider (bits 4 - 11).
    };

    enum class PWM_COMMON_REGISTER
    {
        EN = 0xa0, // Allows to enable/disable multiple pwm channels at once
        INTR = 0xa4,
        INTE = 0xa8,
        INTF = 0xac,
        INTS = 0xb0,
    };

    enum class PWM_CSR_CONTROL
    {
        EN = 0, // Enable m_channel
        PH_CORRECT = 1, // Enable/Disable phase-correct
        A_INV = 2, // Invert output A
        B_INV = 3, // Invert output B
        DIVMODE = 5,
        PH_RET = 6,
        PH_ADV = 7,
    };

    enum class PWM_DIVMODE
    {
        DIV = 0x0,
        LEVEL = 0x1,
        RISE = 0x2,
        FALL = 0x3,
    };

    enum class PWM_CHANNEL
    {
        CHANNEL_A,
        CHANNEL_B,
    };

    class pwm
    {    
        private:
            gpio m_pin;
            uint8_t m_slice;
            tp::PWM_CHANNEL m_channel;
            float m_duty_cycle;

            uint32_t* register_to_address(const tp::PWM_REGISTER pwm_register) const;
        public:
            pwm(const int gpio_number, const uint16_t resolution = uint16_t(-1), const float duty_cycle = 0);
            uint8_t get_slice() const;
            tp::PWM_CHANNEL get_channel() const;

            void set_resolution(const uint16_t wrap_value) const;
            uint16_t set_resolution() const;
            
            void set_level(uint16_t level) const;
            uint16_t get_level() const;
            
            void set_divider(uint8_t integer, uint8_t fraction) const;
            void set_frequency(const float frequency);

            void enable(const bool enable) const;
            void apply_duty_cycle() const;
            void set_duty_cycle(const float duty_cycle);
            float get_duty_cycle() const;
    };
} // namespace tp_pico

#endif // PWM_H