// #include <cstring>
// #include <stdio.h>

#include "gpio.h"
#include "pico_system.h"

#include "interrupt.h"

void default_isr(){}

struct isr_callbacks
{
    private:
        void init_gpio_isr(tp::isr* const isr_table)
        {
            for (uint32_t i = 0; i < tp::GPIO_NUM_PINS; i++)
            {
                isr_table[i] = default_isr;
            }
            
        }
    
    public:

        tp::isr edge_high[tp::GPIO_NUM_PINS];
        tp::isr edge_low[tp::GPIO_NUM_PINS];
        tp::isr level_high[tp::GPIO_NUM_PINS];
        tp::isr level_low[tp::GPIO_NUM_PINS];

        isr_callbacks()
        {
            init_gpio_isr(edge_high);
            init_gpio_isr(edge_low);
            init_gpio_isr(level_high);
            init_gpio_isr(level_low);
        }
};

isr_callbacks callbacks = isr_callbacks();

constexpr const uint32_t pins_per_reg = 8;
constexpr const uint32_t bits_per_pin = 4;

inline void tp::clear_irq(const uint32_t interrupt_mask, const uint32_t gpio_number)
{
    tp::io_bank0::registers::intr[gpio_number / 8] &= interrupt_mask << ((gpio_number % 8) * 4);
}

inline void call_gpio_isr(uint32_t pin_number, tp::gpio::irq_mask irq, const uint32_t intr_mask, const tp::isr* const callback_arr)
{
    if(intr_mask & irq)
    {
        callback_arr[pin_number]();
        clear_irq(irq, pin_number);
    }
}
/**
 * @brief This is the default isr for the IO_IRQ_BANK0 interrupt type.
 *
 * @details For every gpio, this function will check which
 *          interrupt bits are set and call the configured
 *          callback for this interrupt.
 */
void tp::gpio_isr()
{
    uint32_t* const status_base = (tp::system::get_core_id() == tp::core_id::CORE_0) ? tp::io_bank0::registers::proc0_ints : tp::io_bank0::registers::proc1_ints;
    
    for (uint32_t i = 0; i < tp::GPIO_NUM_PINS; i++)
    {
        const uint32_t status = status_base[i / pins_per_reg];
        const uint32_t intr_mask = (status >> ((i % pins_per_reg) * bits_per_pin)) & 0b1111; // Extracting the interrupt mask for the current pin.
        call_gpio_isr(i, tp::gpio::irq_mask::EDGE_HIGH, intr_mask, callbacks.edge_high);
        call_gpio_isr(i, tp::gpio::irq_mask::EDGE_LOW, intr_mask, callbacks.edge_low);
        call_gpio_isr(i, tp::gpio::irq_mask::LEVEL_HIGH, intr_mask, callbacks.level_high);
        call_gpio_isr(i, tp::gpio::irq_mask::LEVEL_LOW, intr_mask, callbacks.level_low);
    }
}

inline void set_gpio_isr_helper(uint32_t pin_number, tp::gpio::irq_mask irq, const uint32_t intr_mask, tp::isr* const callback_arr, const tp::isr isr)
{
    if(intr_mask & irq)
    {
        callback_arr[pin_number] = isr;
    }
}
void tp::set_gpio_isr(const uint32_t intr_mask, const tp::isr isr, const uint32_t pin_number)
{
    uint32_t* const config_base = (tp::system::get_core_id() == tp::core_id::CORE_0) ? tp::io_bank0::registers::proc0_inte : tp::io_bank0::registers::proc1_inte;
    config_base[pin_number / pins_per_reg] |= intr_mask << (pin_number % pins_per_reg) * bits_per_pin;
    set_gpio_isr_helper(pin_number, tp::gpio::irq_mask::EDGE_HIGH, intr_mask, callbacks.edge_high, isr);
    set_gpio_isr_helper(pin_number, tp::gpio::irq_mask::EDGE_LOW, intr_mask, callbacks.edge_low, isr);
    set_gpio_isr_helper(pin_number, tp::gpio::irq_mask::LEVEL_HIGH, intr_mask, callbacks.level_high, isr);
    set_gpio_isr_helper(pin_number, tp::gpio::irq_mask::LEVEL_LOW, intr_mask, callbacks.level_low, isr);
}

void remove_gpio_isr_helper(uint32_t pin_number, tp::gpio::irq_mask irq, const uint32_t intr_mask, tp::isr* const callback_arr)
{
    if(intr_mask & irq)
    {
        callback_arr[pin_number] = default_isr;
    }
}

void tp::remove_gpio_isr(const uint32_t intr_mask, const uint32_t pin_number)
{
    uint32_t* const config_base = (tp::system::get_core_id() == tp::core_id::CORE_0) ? tp::io_bank0::registers::proc0_inte : tp::io_bank0::registers::proc1_inte;
    config_base[pin_number / pins_per_reg] &= ~(intr_mask << (pin_number % pins_per_reg) * bits_per_pin);
    remove_gpio_isr_helper(pin_number, tp::gpio::irq_mask::EDGE_HIGH, intr_mask, callbacks.edge_high);
    remove_gpio_isr_helper(pin_number, tp::gpio::irq_mask::EDGE_LOW, intr_mask, callbacks.edge_low);
    remove_gpio_isr_helper(pin_number, tp::gpio::irq_mask::LEVEL_HIGH, intr_mask, callbacks.level_high);
    remove_gpio_isr_helper(pin_number, tp::gpio::irq_mask::LEVEL_LOW, intr_mask, callbacks.level_low);
}