#include "io_bank0.h"

#include "pico_system.h"
#include "pico_types.h"

void tp::io_bank0::reset()
{
    tp::system::reset_peripheral(tp::peripheral::IO_BANK0);
}