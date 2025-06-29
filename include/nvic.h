#ifndef NVIC_H
#define NVIC_H

#include "pico_types.h"

namespace tp
{
    
    class nvic
    {
        public:

            /**
             * @brief This indicates the start of the device irq's in the vector table.
             *        See https://developer.arm.com/documentation/dui0662/b/The-Cortex-M0--Processor/Exception-model/Vector-table
             */
            static const uint32_t VTABLE_IRQ_START = 16;

            enum class interrupt
            {
                TIMER_IRQ_0 = 0,
                TIMER_IRQ_1 = 1,
                TIMER_IRQ_2 = 2,
                TIMER_IRQ_3 = 3,
                PWM_IRQ_WRAP = 4,
                USB_CTRL_IRQ = 5,
                XIP_IRQ = 6,
                PIO0_IRQ_0 = 7,
                PIO0_IRQ_1 = 8,
                PIO1_IRQ_0 = 9,
                PIO1_IRQ_1 = 10,
                DMA_IRQ_0 = 11,
                DMA_IRQ_1 = 12,
                IO_IRQ_BANK0 = 13,
                IO_IRQ_QSPI = 14,
                SIO_IRQ_PROC0 = 15,
                SIO_IRQ_PROC1 = 16,
                CLOCKS_IRQ = 17,
                SPI0_IRQ = 18,
                SPI1_IRQ = 19,
                UART0_IRQ = 20,
                UART1_IRQ = 21,
                ADC_IRQ_FIFO = 22,
                I2C0_IRQ = 23,
                I2C1_IRQ = 24,
                RTC_IRQ = 25,
            };

            struct registers
            {
                static uint32_t* const iser;
                static uint32_t* const icer;
                static uint32_t* const ispr;
                static uint32_t* const icpr;
                static uint32_t* const ipr_base;
                static uint32_t* const vtor;
            };

            /**
             * @brief Enable an interrupt type.
             * 
             * @param interrupt_register 
             */
            static void enable_interrupt(const interrupt interrupt);
            static void disable_interrupt(const interrupt interrupt);
            static void force_interrupt(const interrupt interrupt);
            static void clear_pending_interrupt(const interrupt interrupt);


            /**
             * @brief Get the interrupt table.
             * 
             * @return tp::vtable 
             */
            static tp::vtable interrupt_table();

            /**
             * @brief Get the hardware interrupt table.
             * 
             * @return tp::vtable 
             */
            static tp::vtable irq_vtable(); // Returns the vtable address starting at the user-definable interrupts.

            /**
             * @brief Assign an isr to an irq.
             * 
             * @param interrupt The type of interrupt to assign an isr to.
             * @param handler The interrupt handler.
             */
            static void assign_isr(const tp::nvic::interrupt interrupt, const tp::isr handler);
    };

} // namespace tp


#endif // NVIC_H