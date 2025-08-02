#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <stdint.h>

#include "pico_types.h"

namespace tp
{
    
    class hw_spinlock
    {
        public:
            static constexpr const unsigned int num_spinlocks = 32;
            class use;
        
        private:
            uint32_t* const spinlocks = (uint32_t*)(tp::register_offsets::sio + 0x100);
            unsigned int spinlock_num;

        public:
            static const uint32_t* const status_reg;

            enum class type
            {
                ISR_SET = 0,
            };

            hw_spinlock(unsigned int spinlock_num);
            
            void lock();
            void release();
            bool peek();

    };

    class hw_spinlock::use
    {
        private:
            hw_spinlock spinlock;

        public:
            use(unsigned int spinlock_num);
            ~use();
    };

} // namespace tp


#endif // SPINLOCK_H