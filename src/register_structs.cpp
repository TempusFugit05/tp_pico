/**
 * @file register_structs.cpp
 * @brief Here we initialize all register structs. 
 *        Addresses are calculated by the peripheral base address + register offset (As outlined in the datasheet).
*/

#include "io_bank0.h"

uint32_t* const tp::io_bank0::registers::gpio_status_control =  (uint32_t*)(tp::register_offsets::bank0 + 0);
uint32_t* const tp::io_bank0::registers::intr =                 (uint32_t*)(tp::register_offsets::bank0 + 0x0f0);
uint32_t* const tp::io_bank0::registers::proc0_inte =           (uint32_t*)(tp::register_offsets::bank0 + 0x100);
uint32_t* const tp::io_bank0::registers::proc0_intf =           (uint32_t*)(tp::register_offsets::bank0 + 0x110);
uint32_t* const tp::io_bank0::registers::proc0_ints =           (uint32_t*)(tp::register_offsets::bank0 + 0x120);
uint32_t* const tp::io_bank0::registers::proc1_inte =           (uint32_t*)(tp::register_offsets::bank0 + 0x130);
uint32_t* const tp::io_bank0::registers::proc1_intf =           (uint32_t*)(tp::register_offsets::bank0 + 0x140);
uint32_t* const tp::io_bank0::registers::proc1_ints =           (uint32_t*)(tp::register_offsets::bank0 + 0x150);

#include "clock.h"

uint32_t* const tp::system::clock::fc::ref  =       (uint32_t*)(tp::register_offsets::clock + 0x80);
uint32_t* const tp::system::clock::fc::min_hrz  =   (uint32_t*)(tp::register_offsets::clock + 0x84);
uint32_t* const tp::system::clock::fc::max_hrz  =   (uint32_t*)(tp::register_offsets::clock + 0x88);
uint32_t* const tp::system::clock::fc::delay  =     (uint32_t*)(tp::register_offsets::clock + 0x8c);
uint32_t* const tp::system::clock::fc::interval  =  (uint32_t*)(tp::register_offsets::clock + 0x90);
uint32_t* const tp::system::clock::fc::src  =       (uint32_t*)(tp::register_offsets::clock + 0x94);
uint32_t* const tp::system::clock::fc::status  =    (uint32_t*)(tp::register_offsets::clock + 0x98);
uint32_t* const tp::system::clock::fc::result  =    (uint32_t*)(tp::register_offsets::clock + 0x9c);