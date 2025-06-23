#ifndef PICO_SYSTEM_H
#define PICO_SYSTEM_H

#include <cstdint>

#include "pico_system.h"
#include "pico_types.h"

namespace tp
{

    enum class core_id
    {
        CORE_0 = 0,
        CORE_1 = 1,
    };

    class system
    {
        public:
            static core_id get_core_id();
            static void interrupt_enable(tp::interrupt_register interrupt_register);
            static void reset_peripheral(tp::peripheral peripheral, uint32_t value=1);

            class clock;
    };

} // namespace tp
#endif // PICO_SYSTEM_H