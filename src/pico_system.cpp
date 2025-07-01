#include "pico/stdlib.h"

#include "nvic.h"
#include "pico_types.h"
#include "interrupt.h"
#include "binary_helpers.h"
#include "adc.h"

#include "pico_system.h"

uint32_t* const tp::system::reset_registers::reset = (uint32_t*)(tp::register_offsets::reset + 0x0);
uint32_t* const tp::system::reset_registers::wdsel = (uint32_t*)(tp::register_offsets::reset + 0x4);
uint32_t* const tp::system::reset_registers::done =  (uint32_t*)(tp::register_offsets::reset + 0x8);


tp::system::system()
{
    stdio_init_all();
    tp::nvic::assign_isr(tp::nvic::interrupt::IO_IRQ_BANK0, tp::gpio_isr);
    tp::nvic::enable_interrupt(tp::nvic::interrupt::IO_IRQ_BANK0);
}

tp::system tp::system::_instance = tp::system();

tp::core_id tp::system::get_core_id()
{
    return (tp::core_id) *(uint32_t*)tp::register_offsets::sio;
}

void tp::system::reset_peripheral(tp::system::peripheral peripheral)
{
    *(uint32_t*)(tp::register_offsets::reset) |= (uint32_t)1 << (uint32_t)peripheral; // Reset the peripheral.
    while(!(GET_BIT(*tp::system::reset_registers::done, (uint32_t)peripheral))); // Wait for reset to finish.
}

float tp::system::cpu_temp()
{
    *tp::adc::registers::cs |= 0b10;
    tp::adc sensor = tp::adc(tp::adc::adc_pin::TEMP_SENSOR);
    sensor.enable(true);
    return 27 - (((sensor.read() * (float)3.3) - (float)0.706) / (float)0.001721); // Convert raw reading to temperature given by the formula in section 4.9.5.
}