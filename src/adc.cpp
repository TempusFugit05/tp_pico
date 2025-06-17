#include <stdio.h>

#include "adc.h"
#include "pico_types.h"
#include "binary_helpers.h"

tp::adc::adc(const tp::adc_pin gpio_number) : gpio_number((uint32_t)gpio_number){}

bool tp::adc::is_ready() const
{
    return EXTRACT_BIT(*(uint32_t*)tp::adc_register::CS, (uint32_t)tp::cs_bits::READY);
}

void tp::adc::enable(bool start) const
{
    uint32_t* const reg = (uint32_t*)tp::adc_register::CS;
    *reg = SET_BIT(*reg, (uint32_t)tp::cs_bits::EN, (uint32_t)start);
}

void tp::adc::start_conversion() const
{
    uint32_t* const reg = (uint32_t*)tp::adc_register::CS;
    *reg = SET_BIT(*reg, (uint32_t)tp::cs_bits::START_ONCE, 1);
}

uint32_t tp::adc::read_raw() const
{
    enable(true);
    uint32_t* const reg = (uint32_t*)tp::adc_register::CS;
    *reg = SET_BIT(*reg, (uint32_t)tp::cs_bits::AINSEL, (uint32_t)gpio_number - 26);
    start_conversion();
    while (!is_ready()){}
    const uint32_t offset = (sizeof(uint32_t) * 8 - ADC_RESOLUTION_BITS);
    return (*(uint32_t*)tp::adc_register::RESULT << offset) >> offset;
}

float tp::adc::read() const
{
    return (float)read_raw() / ~((~(uint32_t)0) << ADC_RESOLUTION_BITS); // Clamp reading between 0 and 1.
}