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
            static uint64_t elapsed_time_us;
            static tp::system _instance; // This is simply used for initializing the system.
            static void systick_exception_handler();

        public:

            struct reset_registers
            {
                public:
                    static uint32_t* const reset;
                    static uint32_t* const wdsel;
                    static uint32_t* const done;
            };

            struct systick_registers
            {
                public:
                    static uint32_t* const csr;
                    static uint32_t* const rvr;
                    static uint32_t* const cvr;
                    static uint32_t* const calib;
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

            static void enable_systick(const bool enable);
            static void enable_systick_exception(const bool enable);
            static void set_systick_reload_value(const uint32_t value);
            static uint32_t get_systick_reload_value();
            static uint32_t get_systick_value();
            static void set_systick_value(const uint32_t value);

            static void wait_us(uint64_t us);
            static void wait_ms(uint32_t ms);

            static float cpu_temp();
            
            static uint64_t current_time_us();

            class clock;  
    };

} // namespace tp

#endif // PICO_SYSTEM_H