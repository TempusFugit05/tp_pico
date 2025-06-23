#include <stdio.h>

#include "adc.h"
#include "pico_types.h"
#include "binary_helpers.h"

uint32_t* const tp::adc_registers::cs = (uint32_t*)(tp::register_offsets::adc + 0x00);
uint32_t* const tp::adc_registers::result = (uint32_t*)(tp::register_offsets::adc + 0x04);
uint32_t* const tp::adc_registers::fcs = (uint32_t*)(tp::register_offsets::adc + 0x08);
uint32_t* const tp::adc_registers::fifo = (uint32_t*)(tp::register_offsets::adc + 0x0c);
uint32_t* const tp::adc_registers::div = (uint32_t*)(tp::register_offsets::adc + 0x10);
uint32_t* const tp::adc_registers::intr = (uint32_t*)(tp::register_offsets::adc + 0x14);// See fc_clock_sources for available clock sources.
uint32_t* const tp::adc_registers::inte = (uint32_t*)(tp::register_offsets::adc + 0x18);
uint32_t* const tp::adc_registers::intf = (uint32_t*)(tp::register_offsets::adc + 0x1c);
uint32_t* const tp::adc_registers::ints = (uint32_t*)(tp::register_offsets::adc + 0x20);


tp::adc::adc(const tp::adc_pin gpio_number) : gpio_number((uint32_t)gpio_number){}

bool tp::adc::is_ready() const
{
    return EXTRACT_BIT(*tp::adc_registers::cs, (uint32_t)tp::cs_bits::READY);
}

void tp::adc::enable(bool start) const
{
    *tp::adc_registers::cs = SET_BIT(*tp::adc_registers::cs, (uint32_t)tp::cs_bits::EN, (uint32_t)start);
}

void tp::adc::start_conversion() const
{
    *tp::adc_registers::cs = SET_BIT(*tp::adc_registers::cs, (uint32_t)tp::cs_bits::START_ONCE, 1);
}

uint32_t tp::adc::read_raw() const
{
    enable(true);
    *tp::adc_registers::cs = SET_BIT(*tp::adc_registers::cs, (uint32_t)tp::cs_bits::AINSEL, (uint32_t)gpio_number - 26);
    start_conversion();
    while (!is_ready()){}
    const uint32_t offset = (sizeof(uint32_t) * 8 - ADC_RESOLUTION_BITS); // Shifting needed to clear the reserved bits of the result register. 
    return (*tp::adc_registers::result << offset) >> offset;
}

float tp::adc::read() const
{
    return (float)read_raw() / ~((~(uint32_t)0) << ADC_RESOLUTION_BITS); // Clamp reading between 0 and 1.
}