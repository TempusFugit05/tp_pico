#include <math.h>

#include "pwm.h"
#include "pico_types.h"
#include "gpio.h"
#include "clock.h"
#include "pico_system.h"

tp::pwm::pwm(const gpio_number pin, const uint16_t resolution, const float duty_cycle)
    :   m_duty_cycle(duty_cycle)
    ,   tp::gpio(pin, tp::gpio::function::PWM)
{
    m_channel = get_channel();
    m_slice = get_slice();
    set_resolution(resolution);
}

uint32_t* tp::pwm::register_to_address(const tp::pwm_register pwm_register) const
{
    return (uint32_t*)((uint32_t)pwm_register + tp::register_offsets::pwm + (m_slice * sizeof(uint32_t) * 5));
}

uint32_t tp::pwm::get_slice() const
{
    const uint32_t pin_number = pin;
    return ((pin_number >= 16) ? pin_number - 16 : pin_number) / 2;
}

tp::pwm_channel tp::pwm::get_channel() const
{
    return pin % 2 == 0 ? tp::pwm_channel::CHANNEL_A : tp::pwm_channel::CHANNEL_B;
}

void tp::pwm::set_resolution(const uint16_t resolution) const
{
    *register_to_address(tp::pwm_register::TOP) = resolution;
}

uint16_t tp::pwm::get_resolution() const
{
    return *register_to_address(tp::pwm_register::TOP);
}

void tp::pwm::set_level(uint16_t level) const
{
    uint32_t* const reg = register_to_address(tp::pwm_register::CC);
    const uint32_t channel_level = m_channel == tp::pwm_channel::CHANNEL_B ? (uint32_t)level << (sizeof(uint32_t) * 4) : (uint32_t)level;
    *reg = (m_channel == tp::pwm_channel::CHANNEL_B ? (*reg << 16) >> 16 : (*reg >> 16) << 16) | channel_level;
}

uint32_t tp::pwm::get_level() const
{
    uint32_t* const reg = register_to_address(tp::pwm_register::CC);
    return (m_channel == tp::pwm_channel::CHANNEL_B ? (*reg << 16) >> 16 : (*reg >> 16) << 16);
}

void tp::pwm::set_divider(uint8_t integer, uint8_t fraction) const
{
    uint32_t* const reg = register_to_address(tp::pwm_register::DIV);
    *reg = ((*reg >> 11) << 11) | (integer << (uint32_t)tp::pwm_div_bits::INT) | std::min(fraction, tp::PWM_DIV_MAX_FRACTION);
}

void tp::pwm::enable(const bool enable) const
{
    uint32_t* const reg = register_to_address(tp::pwm_register::CSR);
    *reg = ~((~*reg) | (uint32_t)1) | enable;    
}

void tp::pwm::set_frequency(const float frequency)
{
    set_divider(255, 0);
    set_resolution((tp::system::clock::get_frequency(tp::fc_clock_sources::SYS) / (255 * frequency)));
    apply_duty_cycle();
}

void tp::pwm::apply_duty_cycle() const
{
    const uint16_t wrap = get_resolution();
    set_level((m_duty_cycle * wrap) / 100);
}

void tp::pwm::set_duty_cycle(const float duty_cycle)
{
    m_duty_cycle = duty_cycle;
    apply_duty_cycle();
}

float tp::pwm::get_duty_cycle() const
{
    return m_duty_cycle;
}