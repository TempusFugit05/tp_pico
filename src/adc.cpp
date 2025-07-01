#include <stdio.h>

#include "adc.h"
#include "pico_types.h"
#include "binary_helpers.h"

uint32_t* const tp::adc::registers::cs = (uint32_t*)(tp::register_offsets::adc + 0x00);
uint32_t* const tp::adc::registers::result = (uint32_t*)(tp::register_offsets::adc + 0x04);
uint32_t* const tp::adc::registers::fcs = (uint32_t*)(tp::register_offsets::adc + 0x08);
uint32_t* const tp::adc::registers::fifo = (uint32_t*)(tp::register_offsets::adc + 0x0c);
uint32_t* const tp::adc::registers::div = (uint32_t*)(tp::register_offsets::adc + 0x10);
uint32_t* const tp::adc::registers::intr = (uint32_t*)(tp::register_offsets::adc + 0x14);
uint32_t* const tp::adc::registers::inte = (uint32_t*)(tp::register_offsets::adc + 0x18);
uint32_t* const tp::adc::registers::intf = (uint32_t*)(tp::register_offsets::adc + 0x1c);
uint32_t* const tp::adc::registers::ints = (uint32_t*)(tp::register_offsets::adc + 0x20);


tp::adc::adc(const tp::adc::adc_pin gpio_number) : gpio((tp::gpio::pin_number)gpio_number){}

bool tp::adc::is_ready() const
{
    return EXTRACT_BIT(*tp::adc::registers::cs, (uint32_t)tp::adc::cs_bits::READY);
}

void tp::adc::enable(bool start)
{
    *tp::adc::registers::cs = OVERRIDE_BIT(*tp::adc::registers::cs, (uint32_t)tp::adc::cs_bits::EN, (uint32_t)start);
}

void tp::adc::start_measurement() const
{
    *tp::adc::registers::cs = OVERRIDE_BIT(*tp::adc::registers::cs, (uint32_t)tp::adc::cs_bits::START_ONCE, 1);
}

uint32_t tp::adc::read_raw() const
{
    enable(true);
    *tp::adc::registers::cs = OVERRIDE_BIT(*tp::adc::registers::cs, (uint32_t)tp::adc::cs_bits::AINSEL, (pin));
    start_measurement();
    while (!is_ready()){}
    constexpr const uint32_t offset = (sizeof(uint32_t) * 8 - ADC_RESOLUTION_BITS); // Shifting needed to clear the reserved bits of the result register. 
    return (*tp::adc::registers::result << offset) >> offset;
}

float tp::adc::read() const
{
    return (float)read_raw() / ~((~(uint32_t)0) << ADC_RESOLUTION_BITS); // Clamp reading between 0 and 1.
}