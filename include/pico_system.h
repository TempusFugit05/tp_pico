#ifndef PICO_SYSTEM_H
#define PICO_SYSTEM_H

#include <cstdint>

#include "pico_system.h"
#include "pico_types.h"
#include "nvic.h"

namespace tp
{
    class system
    {
        private:
            /**
             * @brief This is a constructor used for initialization of the system before main is called.
             */
            system();
            static tp::system _instance; // This is simply used for initializing the system.

        public:

            struct reset_registers
            {
                public:
                    static uint32_t* const reset;
                    static uint32_t* const wdsel;
                    static uint32_t* const done;
            };

            enum class peripheral
            {
                ADC = 0,
                BUSCTRL = 1,
                DMA = 2,
                I2C0 = 3,
                I2C1 = 4,
                IO_BANK0 = 5,
                IO_QSPI = 6,
                JTAG = 7,
                PADS_BANK0 = 8,
                PADS_QSPI = 9,
                PIO0 = 10,
                PIO1 = 11,
                PLL_SYS = 12,
                PLL_USB = 13,
                PWM = 14,
                RTC = 15,
                SPI0 = 16,
                SPI1 = 17,
                SYSCFG = 18,
                SYSINFO = 19,
                TBMAN = 20,
                TIMER = 21,
                UART0 = 22,
                UART1 = 23,
                USBCTRL = 24,
            };

            /**
             * @brief Get the core id of the executing core.
             * 
             * @return The core id of the executing core.
             */
            static core_id get_core_id();

            /**
             * @brief Reset a hardware peripheral.
             * 
             * @param peripheral The peripheral to reset.
             */
            static void reset_peripheral(peripheral peripheral);

            static float cpu_temp();

            class clock;
    };

} // namespace tp

#endif // PICO_SYSTEM_H