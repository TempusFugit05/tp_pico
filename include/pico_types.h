#ifndef PICO_TYPES_H
#define PICO_TYPES_H

#include <stdint.h>
namespace tp
{

    enum class register_offsets : uint32_t
    {
        RESET = 0x4000c000,
        BANK0 = 0x40014000, // io bank 0 registers memory address start.
        ADC = 0x4004c000, // adc registers memory address start.
        PWM = 0x40050000, // pwm registers memory address start.
        SIO = 0xd0000000, // Sio registers memory address start.
        CORTEX = 0xe0000000,
        NVIC_ISER = 0xe1000000,
    };

    enum class RESET_REGISTER
    {
        DONE = 0x8, // This register is set when a peripheral is done resetting.
    };

    enum class PERIPHERAL
    {
        IO_BANK0 = 5,
    };

    enum class INTERRUPT_REGISTER
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

    enum class GPIO_ACTION // SIO REGISTERS
    {
        CPUID = 0x000, // Core identifier, 0 when read from the first core, 1 when read from the second.
        GPIO_IN = 0x004, // Input value for gpio.
        GPIO_HI_IN = 0x08, // Input value for QSPI pin.
        GPIO_OUT = 0x010, // The output value of the gpio pin.
        GPIO_OUT_SET = 0x014, // Set gpio high.
        GPIO_OUT_CLEAR = 0x018, // Set gpio low.
        GPIO_OUTPUT_ENABLE_SET = 0x024, // Set gpio to output.
        GPIO_OUTPUT_ENABLE_CLEAR = 0x028, // Set gpio to input.
        GPIO_OUTPUT_ENABLE_XOR = 0x02, // Flip gpio direction (input -> output) || (output -> input).
        GPIO_OUT_XOR = 0x1c, // Flip gpio state (high -> low) || (low -> high).
    };

    enum class GPIO_FUNCTION
    {
        SPI = 1,
        UART = 2,
        I2C = 3,
        PWM = 4,
        SIO = 5, // single-cycle io (regular gpio behavior).
        PIO0 = 6,
        PIO1 = 7,
        CLOCK = 8,
        USB = 9,
    };

    enum class GPIO_INPUT_DIRECTION
    {
        INPUT = (uint32_t)GPIO_ACTION::GPIO_OUTPUT_ENABLE_CLEAR,
        OUTPUT = (uint32_t)GPIO_ACTION::GPIO_OUTPUT_ENABLE_SET,
        FLIP = (uint32_t)GPIO_ACTION::GPIO_OUT_XOR,
    };
} // namespace tp_pico

#endif // PICO_TYPES_H