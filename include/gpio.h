#ifndef GPIO_H
#define GPIO_H

#include "io_bank0.h"
#include "pico_types.h"
namespace tp
{
    
    class gpio
    {
        private:
            int gpio_number;
        
        public:
            gpio(int gpio_number);
            gpio(int gpio_number, tp::GPIO_FUNCTION function);
            void direction(tp::GPIO_INPUT_DIRECTION direction) const;
            void output_flip() const;
            void output_set(bool value) const;
            bool input_read() const;
            uint32_t get_gpio_number() const; 
    };

} // namespace tp
#endif // GPIO_H