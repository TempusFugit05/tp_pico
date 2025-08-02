#include "spinlock.h"
#include "binary_helpers.h"
#include "debug.h"

const uint32_t* const tp::hw_spinlock::status_reg = (uint32_t*)(tp::register_offsets::sio + 0x05c);

tp::hw_spinlock::hw_spinlock(const unsigned int num) : spinlock_num(num){}

void tp::hw_spinlock::lock()
{
    volatile uint32_t foo = spinlocks[spinlock_num];
    while (true)
    {
        if(foo != 0)
        {
            return;
        }
        foo = spinlocks[spinlock_num];
    }
}

void tp::hw_spinlock::release()
{
    TP_ASSERT_MSG(tp::hw_spinlock::peek(), "Cannot release an unlocked spinlock.");
    spinlocks[spinlock_num] = 0;
}

bool tp::hw_spinlock::peek()
{
    return GET_BIT(*status_reg, spinlock_num);
}

tp::hw_spinlock::use::use(const unsigned int spinlock_num) : spinlock(hw_spinlock(spinlock_num))
{
    spinlock.lock();
}

tp::hw_spinlock::use::~use()
{
    spinlock.release();   
}