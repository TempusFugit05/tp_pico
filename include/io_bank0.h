#ifndef IO_BANK0_H
#define IO_BANK0_H

#include <stdint.h>

#include "pico_types.h"

namespace tp
{
    class io_bank0
    {
        public:
            struct registers
            {
                public:
                    static uint32_t* const gpio_status_control;
                    static uint32_t* const intr;
                    static uint32_t* const proc0_inte;
                    static uint32_t* const proc0_intf;
                    static uint32_t* const proc0_ints;
                    static uint32_t* const proc1_inte;
                    static uint32_t* const proc1_intf;
                    static uint32_t* const proc1_ints;
            };
    };

} // namespace tp
#endif // IO_BANK0_H