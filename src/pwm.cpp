#include <math.h>

#include "pwm.h"
#include "pico_types.h"
#include "gpio.h"

tp::pwm::pwm(const int gpio_number, const uint16_t resolution, const float duty_cycle)
    :   m_duty_cycle(duty_cycle)
    ,    m_pin(gpio_number, tp::GPIO_FUNCTION::PWM)
{
    m_channel = get_channel();
    m_slice = get_slice();
    set_resolution(resolution);
}

uint32_t* tp::pwm::register_to_address(const tp::PWM_REGISTER pwm_register) const
{
    return (uint32_t*)((uint32_t)pwm_register + (uint32_t)tp::register_offsets::PWM + (m_slice * sizeof(uint32_t) * 5));
}

uint8_t tp::pwm::get_slice() const
{
    const uint32_t pin_number = m_pin.get_gpio_number();
    return ((pin_number >= 16) ? pin_number - 16 : pin_number) / 2;
}

tp::PWM_CHANNEL tp::pwm::get_channel() const
{
    return m_pin.get_gpio_number() % 2 == 0 ? tp::PWM_CHANNEL::CHANNEL_A : tp::PWM_CHANNEL::CHANNEL_B;
}

void tp::pwm::set_resolution(const uint16_t wrap_value) const
{
    *register_to_address(tp::PWM_REGISTER::TOP) = wrap_value;
}

uint16_t tp::pwm::set_resolution() const
{
    return *register_to_address(tp::PWM_REGISTER::TOP);
}

void tp::pwm::set_level(uint16_t level) const
{
    uint32_t* const reg = register_to_address(tp::PWM_REGISTER::CC);
    const uint32_t channel_level = m_channel == tp::PWM_CHANNEL::CHANNEL_B ? (uint32_t)level << (sizeof(uint32_t) * 4) : (uint32_t)level;
    *reg = (m_channel == tp::PWM_CHANNEL::CHANNEL_B ? (*reg << 16) >> 16 : (*reg >> 16) << 16) | channel_level;
}

uint16_t tp::pwm::get_level() const
{
    uint32_t* const reg = register_to_address(tp::PWM_REGISTER::CC);
    return (m_channel == tp::PWM_CHANNEL::CHANNEL_B ? (*reg << 16) >> 16 : (*reg >> 16) << 16);
}

void tp::pwm::set_divider(uint8_t integer, uint8_t fraction) const
{
    uint32_t* const reg = register_to_address(tp::PWM_REGISTER::DIV);
    *reg = ((*reg >> 11) << 11) | (integer << (uint32_t)tp::PWM_DIV_BITS::INT) | std::min(fraction, tp::PWM_DIV_MAX_FRACTION);
}

void tp::pwm::enable(const bool enable) const
{
    uint32_t* const reg = register_to_address(tp::PWM_REGISTER::CSR);
    *reg = ~((~*reg) | (uint32_t)1) | enable;    
}

void tp::pwm::set_frequency(const float frequency)
{
    set_divider(255, 0);
    set_resolution((125000000 / (255 * frequency)));
    apply_duty_cycle();
}

void tp::pwm::apply_duty_cycle() const
{
    const uint16_t wrap = set_resolution();
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