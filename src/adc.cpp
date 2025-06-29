#include <stdio.h>

#include "adc.h"
#include "pico_types.h"
#include "binary_helpers.h"

tp::adc::adc(const tp::adc_pin gpio_number) : gpio((tp::gpio::pin_number)gpio_number){}

bool tp::adc::is_ready() const
{
    return EXTRACT_BIT(*tp::adc_registers::cs, (uint32_t)tp::cs_bits::READY);
}

void tp::adc::enable(bool start)
{
    *tp::adc_registers::cs = OVERRIDE_BIT(*tp::adc_registers::cs, (uint32_t)tp::cs_bits::EN, (uint32_t)start);
}

void tp::adc::start_measurement() const
{
    *tp::adc_registers::cs = OVERRIDE_BIT(*tp::adc_registers::cs, (uint32_t)tp::cs_bits::START_ONCE, 1);
}

uint32_t tp::adc::read_raw() const
{
    enable(true);
    *tp::adc_registers::cs = OVERRIDE_BIT(*tp::adc_registers::cs, (uint32_t)tp::cs_bits::AINSEL, (pin - 26));
    start_measurement();
    while (!is_ready()){}
    constexpr const uint32_t offset = (sizeof(uint32_t) * 8 - ADC_RESOLUTION_BITS); // Shifting needed to clear the reserved bits of the result register. 
    return (*tp::adc_registers::result << offset) >> offset;
}

float tp::adc::read() const
{
    return (float)read_raw() / ~((~(uint32_t)0) << ADC_RESOLUTION_BITS); // Clamp reading between 0 and 1.
}