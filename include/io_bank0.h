#ifndef IO_BANK0_H
#define IO_BANK0_H

#include <stdint.h>

#include "pico_types.h"

namespace tp
{

    class io_bank0
    {
        public:
            static void reset();
            static uint32_t gpio_control_offset(int pin);
            static uint32_t gpio_status_offset(int pin);
            static void set_gpio_function(int pin, tp::GPIO_FUNCTION function);
            static void set_sio_register(int pin, tp::GPIO_ACTION sio_register, uint32_t value=1);
            static uint32_t get_sio_register(int pin, tp::GPIO_ACTION sio_register);
    };

} // namespace tp
#endif // IO_BANK0_H