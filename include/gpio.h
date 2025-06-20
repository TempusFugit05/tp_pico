#ifndef GPIO_H
#define GPIO_H

#include "io_bank0.h"
#include "pico_types.h"
namespace tp
{
    
    enum class gpio_number
    {
        GPIO_0 = 0,
        GPIO_1 = 1,
        GPIO_2 = 2,
        GPIO_3 = 3,
        GPIO_4 = 4,
        GPIO_5 = 5,
        GPIO_6 = 6,
        GPIO_7 = 7,
        GPIO_8 = 8,
        GPIO_9 = 9,
        GPIO_10 = 10,
        GPIO_11 = 11,
        GPIO_12 = 12,
        GPIO_13 = 13,
        GPIO_14 = 14,
        GPIO_15 = 15,
        GPIO_16 = 16,
        GPIO_17 = 17,
        GPIO_18 = 18,
        GPIO_19 = 19,
        GPIO_20 = 20,
        GPIO_21 = 21,
        GPIO_22 = 22,
        GPIO_24 = 24,
        GPIO_25 = 25,
        GPIO_26 = 26,
        GPIO_27 = 27,
        GPIO_28 = 28,
        GPIO_29 = 29,
    };

    class gpio
    {
        private:
            int gpio_number;
        
        public:
            gpio(int gpio_number);
            gpio(int gpio_number, tp::GPIO_FUNCTION function);
            void direction(tp::GPIO_INPUT_DIRECTION direction) const;
            void set_function(tp::GPIO_FUNCTION function) const;
            void output_flip() const;
            void output_set(bool value) const;
            bool input_read() const;
            uint32_t get_gpio_number() const; 
    };

} // namespace tp
#endif // GPIO_H