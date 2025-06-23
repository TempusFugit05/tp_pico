#ifndef PICO_TYPES_H
#define PICO_TYPES_H

#include <stdint.h>
namespace tp
{
    struct register_offsets
    {
        public:
            static uint32_t const reset;
            static uint32_t const bank0;
            static uint32_t const adc;
            static uint32_t const pwm;
            static uint32_t const clock;
            static uint32_t const sio; // See fc_clock_sources for available clock sources.
            static uint32_t const cortex;
            static uint32_t const nvic_iser;
    };

    // enum class register_offsets : uint32_t
    // {
    //     RESET = 0x4000c000,
    //     BANK0 = 0x40014000, // io bank 0 registers memory address start.
    //     ADC = 0x4004c000, // adc registers memory address start.
    //     PWM = 0x40050000, // pwm registers memory address start.
    //     CLOCK = 0x40008000,
    //     SIO = 0xd0000000, // Sio registers memory address start.
    //     CORTEX = 0xe0000000,
    //     NVIC_ISER = 0xe1000000,
    // };

    enum class reset_register
    {
        DONE = 0x8, // This register is set when a peripheral is done resetting.
    };

    enum class peripheral
    {
        IO_BANK0 = 5,
    };

    enum class interrupt_register
    {
        TIMER_IRQ_0 = 0,
        TIMER_IRQ_1 = 1,
        TIMER_IRQ_2 = 2,
        TIMER_IRQ_3 = 3,
        PWM_IRQ_WRAP = 4,
        USBCTRL_IRQ = 5,
        XIP_IRQ = 6,
        PIO0_IRQ_0 = 7,
        PIO0_IRQ_1 = 8,
        PIO1_IRQ_0 = 9,
        PIO1_IRQ_1 = 10,
        DMA_IRQ_0 = 11,
        DMA_IRQ_1 = 12,
        IO_IRQ_BANK0 = 13
    };
} // namespace tp_pico

#endif // PICO_TYPES_H