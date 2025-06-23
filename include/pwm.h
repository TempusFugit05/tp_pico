#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include "pico_types.h"
#include "gpio.h"

namespace tp
{
    constexpr uint8_t PWM_DIV_MAX_FRACTION = 16;

    enum class pwm_register
    {
        CSR = 0x00, // Control and status register.
        DIV = 0x04, // Clock divider.
        CTR = 0x08, // PWM counter.
        CC = 0x0c, 
        TOP = 0x10, // Counter wrap.
    };

    enum class pwm_div_bits
    {
        FRAC = 0, // A 4 bit fraction part of the divider (Value is FRAC / 16) (bits 0 - 3).
        INT = 4, // The integer part of the divider (bits 4 - 11).
    };

    enum class pwm_common_register
    {
        EN = 0xa0, // Allows to enable/disable multiple pwm channels at once
        INTR = 0xa4,
        INTE = 0xa8,
        INTF = 0xac,
        INTS = 0xb0,
    };

    enum class pwm_csr_control
    {
        EN = 0, // Enable m_channel
        PH_CORRECT = 1, // Enable/Disable phase-correct
        A_INV = 2, // Invert output A
        B_INV = 3, // Invert output B
        DIVMODE = 5,
        PH_RET = 6,
        PH_ADV = 7,
    };

    enum class pwm_divmode
    {
        DIV = 0x0,
        LEVEL = 0x1,
        RISE = 0x2,
        FALL = 0x3,
    };

    enum class pwm_channel
    {
        CHANNEL_A,
        CHANNEL_B,
    };

    class pwm : tp::gpio
    {    
        private:
            uint8_t m_slice;
            tp::pwm_channel m_channel;
            float m_duty_cycle;

            uint32_t* register_to_address(const tp::pwm_register pwm_register) const;
        public:
            pwm(const tp::gpio_number pin, const uint16_t resolution = uint16_t(-1), const float duty_cycle = 0);

            /**
             * @brief Get the slice of the pwm pin.
             * 
             * @return The slice associated with this pin. 
             *
             * @details A slice is one of the 8 (each 4 pins share the same slice) independent pwm outputs of the pi pico. 
             *          Each pin has a slice and channel associated to it. 
             */
            uint32_t get_slice() const;
            
            /**
             * @brief Get the channel of the pwm pin.
             * 
             * @return The channel associated with this pin.
             * 
             * @details A channel is one of two (each 2 pins share the same channel) signal outputs of a pwm slice.
             *          Each channel has its own counter compare value but both share the same top and div values (see Table 516 in datasheet).
             */
            tp::pwm_channel get_channel() const;

            /**
             * @brief Set the resolution of the pwm channel, higher values result in more precise control. (TOP register)
             * 
             * @param resolution The desired resolution.
             */
            void set_resolution(const uint16_t resolution) const;

            /**
             * @brief Get the resolution of the pwm channel.
             * 
             * @return The resolution of the pwm channel.
             */
            uint16_t get_resolution() const;
            
            /**
             * @brief Set the number of ticks the cycle should be held in the high level. (CC register)
             * 
             * @param level The number of ticks to hold signal high in one pwm cycle.
             *  
             * @example set_level(25); // Equivalent to 25% duty cycle when the resolution is 100 or 12.5% when resolution is 200.
             */
            void set_level(uint16_t level) const;
            
            /**
             * @brief Get the level value of the pwm channel.
             * 
             * @return The level of the pwm channel.
             */
            uint32_t get_level() const;
            
            /**
             * @brief Set the clock divider for the pwm slice associated with this pin. (DIV register) 
             * 
             * @param integer The integer part of the divide.
             * @param fraction The fraction part of the divider (up to 15/16).
             * 
             * @todo Figure out a better interface for this.
             */
            void set_divider(uint8_t integer, uint8_t fraction) const;

            /**
             * @brief Set the frequency of the pwm slice associated with this pin.
             * @warning This affects both clock divider and level of the pwm channel (DIV and CC registers).
             * 
             * @param frequency The desired frequency of the slice.
             * 
             * @details This function attempts to find the best combination of
             *          level and divider values to achieve the desired frequency.
             *          The frequency can be any number between the clock frequency (125,000,000 by default) and 0.
             *          frequency = clock_speed / (divider * resolution).
             *          This function will attempt to maximize the divider for the given frequency to allow the highest resolution.
             * 
             * @todo Find an algorithm to accurately follow the explanation in the details section.
             */
            void set_frequency(const float frequency);

            /**
             * @brief Enable or disable the pwm slice associated with this pin.
             * 
             * @param enable true to enable slice; false to disable.
             */
            void enable(const bool enable) const;

            /**
             * @brief Apply the duty cycle for the slice associated with this pin.
             * 
             * @note There is no need to call this function after setting the duty cycle. This is only needed after changing the channel resolution.
             */
            void apply_duty_cycle() const;

            /**
             * @brief Set the duty cycle of the slice associated with this pin.
             * 
             * @param duty_cycle The desired duty cycle (0% - 100%).
             *
             * @details duty_cycle = (level / resolution) * 100.
             */
            void set_duty_cycle(const float duty_cycle);

            /**
             * @brief Get the duty cycle.
             * 
             * @return The duty cycle.
             */
            float get_duty_cycle() const;
    };
} // namespace tp_pico

#endif // PWM_H