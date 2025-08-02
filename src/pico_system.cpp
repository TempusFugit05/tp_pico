#include "pico/stdlib.h"

#include "nvic.h"
#include "pico_types.h"
#include "interrupt.h"
#include "binary_helpers.h"
#include "adc.h"
#include "clock.h"
#include "debug.h"
#include "digital_pin.h"

#include "pico_system.h"

uint32_t* const tp::system::reset_registers::reset = (uint32_t*)(tp::register_offsets::reset + 0x0);
uint32_t* const tp::system::reset_registers::wdsel = (uint32_t*)(tp::register_offsets::reset + 0x4);
uint32_t* const tp::system::reset_registers::done =  (uint32_t*)(tp::register_offsets::reset + 0x8);

uint32_t* const tp::system::systick_registers::csr = (uint32_t*)(tp::register_offsets::cortex + 0xe010);
uint32_t* const tp::system::systick_registers::rvr = (uint32_t*)(tp::register_offsets::cortex + 0xe014);
uint32_t* const tp::system::systick_registers::cvr = (uint32_t*)(tp::register_offsets::cortex + 0xe018);
uint32_t* const tp::system::systick_registers::calib = (uint32_t*)(tp::register_offsets::cortex + 0xe01c);

uint64_t tp::system::elapsed_time_us = 0;

constexpr const uint32_t systick_max_value = CLEAR_LEFT(~(uint32_t)0, 32 - 24);

tp::system::system()
{
    stdio_init_all();
    tp::nvic::assign_isr(tp::nvic::interrupt::IO_IRQ_BANK0, tp::gpio_isr);
    tp::nvic::enable_interrupt(tp::nvic::interrupt::IO_IRQ_BANK0);

    tp::nvic::set_exception_handler(tp::nvic::hw_exception::SYSTICK, systick_exception_handler);
    enable_systick_exception(true);
    enable_systick(true);

    tp::system::clock();
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

void tp::system::systick_exception_handler()
{
    tp::system::elapsed_time_us += get_systick_reload_value();
}

uint64_t tp::system::current_time_us()
{
    return elapsed_time_us + get_systick_reload_value() - get_systick_value();
}

void tp::system::enable_systick(const bool enable)
{
    *tp::system::systick_registers::csr = OVERRIDE_BIT(*tp::system::systick_registers::csr, 0, enable);
}

void tp::system::enable_systick_exception(const bool enable)
{
    *tp::system::systick_registers::csr = OVERRIDE_BIT(*tp::system::systick_registers::csr, 1, enable);
}

void tp::system::set_systick_reload_value(const uint32_t value)
{
    TP_ASSERT_MSG(value <= systick_max_value, "The systick reload value can't be higher than %d.", systick_max_value);
    *tp::system::systick_registers::rvr = CLEAR_RIGHT(*tp::system::systick_registers::rvr, 24) | value;
}

uint32_t tp::system::get_systick_reload_value()
{
    return CLEAR_LEFT(*tp::system::systick_registers::rvr, 32 - 24);
}

uint32_t tp::system::get_systick_value()
{
    return CLEAR_LEFT(*tp::system::systick_registers::cvr, 32 - 24);
}

void tp::system::set_systick_value(const uint32_t value)
{
    TP_ASSERT_MSG(value <= systick_max_value, "The systick value can't be higher than %d.", systick_max_value);
    *tp::system::systick_registers::cvr = CLEAR_RIGHT(*tp::system::systick_registers::cvr, 24) | value;
}

void tp::system::wait_us(uint64_t us)
{
    volatile uint64_t start_time = current_time_us();
    while (current_time_us() - start_time < us){asm volatile("" : "+g"(start_time)); /* Trick the compiler to prevent optimizing this out */ }
}

void tp::system::wait_ms(uint32_t ms)
{
    wait_us(ms * 1000);
}

