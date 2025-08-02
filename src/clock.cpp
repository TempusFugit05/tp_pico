#include <cstring>

#include "pico_system.h"
#include "sys_config.h"

#include "clock.h"
#include "binary_helpers.h"
#include <stdio.h>

namespace tp
{
    uint32_t* const tp::system::clock::rosc_registers::ctrl =      (uint32_t*)(0x0 + tp::register_offsets::rosc);
    uint32_t* const tp::system::clock::rosc_registers::freqa =     (uint32_t*)(0x4 + tp::register_offsets::rosc);
    uint32_t* const tp::system::clock::rosc_registers::freqb =     (uint32_t*)(0x08 + tp::register_offsets::rosc);
    uint32_t* const tp::system::clock::rosc_registers::dormant =   (uint32_t*)(0x0c + tp::register_offsets::rosc);
    uint32_t* const tp::system::clock::rosc_registers::div =       (uint32_t*)(0x10 + tp::register_offsets::rosc);
    uint32_t* const tp::system::clock::rosc_registers::phase =     (uint32_t*)(0x14 + tp::register_offsets::rosc);
    uint32_t* const tp::system::clock::rosc_registers::status =    (uint32_t*)(0x18 + tp::register_offsets::rosc);
    uint32_t* const tp::system::clock::rosc_registers::randombit = (uint32_t*)(0x1c + tp::register_offsets::rosc);
    uint32_t* const tp::system::clock::rosc_registers::count =     (uint32_t*)(0x20 + tp::register_offsets::rosc);

    uint32_t tp::system::clock::cached_frequencies[(uint32_t)tp::fc_clock_sources::NUM_CLOCKS];

    tp::system::clock::clock()
    {
        memset(cached_frequencies, 0, sizeof(cached_frequencies));
    }

    bool tp::system::clock::frequency_measure_done()
    {       
        return *tp::system::clock::fc::status & (1 << (uint32_t)tp::fc0_status_bits::DONE) >> 4;
    }

    void tp::system::clock::start_measurement(fc_clock_sources source)
    {
        constexpr uint32_t src_bits_size = 7;
        *tp::system::clock::fc::src = ((*tp::system::clock::fc::src >> src_bits_size) << src_bits_size) | (uint32_t)source;
    }

    void tp::system::clock::set_ref_frequency(const uint32_t frequency)
    {
        constexpr uint32_t ref_bits_size = 19;
        *tp::system::clock::fc::ref = ((*tp::system::clock::fc::ref >> ref_bits_size) << ref_bits_size) | frequency;
    }

    void tp::system::clock::set_accuracy(uint32_t accuracy)
    {
        *tp::system::clock::fc::interval = ((*tp::system::clock::fc::interval >> 3) << 3) | accuracy;
    }

    uint32_t tp::system::clock::get_ref_clock_freq()
    {
        return REFERENCE_CLOCK_FREQUENCY; // TODO: find a way to get the actual frequency during runtime.
    }

    bool tp::system::clock::rosc_stable()
    {
        return EXTRACT_BIT(*tp::system::clock::rosc_registers::status, 31);
    }

    uint32_t tp::system::clock::get_frequency(fc_clock_sources source)
    {
        // if(cached_frequencies[(uint32_t)source] != 0)
        // {
        //     return cached_frequencies[(uint32_t)source];
        // }

        // while(!rosc_stable() || system::current_time_us() < 100 * 1000){asm volatile("" : "+g"(source));}
        
        while(!frequency_measure_done()){} // Await previous conversions to finish.
        set_ref_frequency(get_ref_clock_freq() / 1000); // The reference frequency should be the frequency of clk_ref in khz. 
        start_measurement(source);
        while(!frequency_measure_done()){} // Wait for the current conversion to finish.
        uint32_t measurement = *tp::system::clock::fc::result;

        constexpr uint32_t frac_bits_size = 4;
        constexpr uint32_t khz_bits_size = 29;

        constexpr uint32_t frac_offset = (sizeof(uint32_t) * 8) - frac_bits_size;
        constexpr uint32_t khz_offset = (sizeof(uint32_t) * 8) - khz_bits_size;

        uint32_t fraction = (((measurement << frac_offset) >> frac_offset) * 1000) / 16; // Get the fraction part of the result.
        uint32_t khz = ((measurement << khz_offset) >> (khz_offset + frac_bits_size)) * 1000; // Get the khz part of the result.
        
        uint32_t result = fraction + khz;
        cached_frequencies[(uint32_t)source] = result;
        
        return result;
    }

} // namespace tp
