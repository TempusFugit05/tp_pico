#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "gpio.h"

namespace tp
{

    void set_gpio_isr(const uint32_t intr_mask, const tp::isr isr, const uint32_t pin_number);
    void remove_gpio_isr(const uint32_t intr_mask, const uint32_t pin_number);
    void clear_irq(const uint32_t interrupt_mask, const uint32_t gpio_number);

    void init_gpio_isr();
    void gpio_isr();

} // namespace tp


#endif // INTERRUPT_H