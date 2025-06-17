#ifndef PICO_SYSTEM_H
#define PICO_SYSTEM_H

#include <cstdint>

# include <pico_types.h>

namespace tp
{

    class system
    {
        public:
            static void interrupt_enable(tp::INTERRUPT_REGISTER interrupt_register);
            static void reset_peripheral(tp::PERIPHERAL peripheral, uint32_t value=1);
    };

    // extern system system;

} // namespace tp
#endif // PICO_SYSTEM_H