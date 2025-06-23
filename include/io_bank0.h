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
    };

} // namespace tp
#endif // IO_BANK0_H