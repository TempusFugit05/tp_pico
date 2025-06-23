#include "clock.h"
#include "pico_system.h"

namespace tp
{
    uint32_t* const tp::fc::ref  = (uint32_t*)(tp::register_offsets::clock + 0x80);
    uint32_t* const tp::fc::min_hrz  = (uint32_t*)(tp::register_offsets::clock + 0x84);
    uint32_t* const tp::fc::max_hrz  = (uint32_t*)(tp::register_offsets::clock + 0x88);
    uint32_t* const tp::fc::delay  = (uint32_t*)(tp::register_offsets::clock + 0x8c);
    uint32_t* const tp::fc::interval  = (uint32_t*)(tp::register_offsets::clock + 0x90);
    uint32_t* const tp::fc::src  = (uint32_t*)(tp::register_offsets::clock + 0x94);
    uint32_t* const tp::fc::status  = (uint32_t*)(tp::register_offsets::clock + 0x98);
    uint32_t* const tp::fc::result  = (uint32_t*)(tp::register_offsets::clock + 0x9c);


    bool tp::system::clock::frequency_measure_done()
    {       
        return *tp::fc::status & (1 << (uint32_t)tp::fc0_status_bits::DONE) >> 4;
    }

    void tp::system::clock::start_measurement(fc_clock_sources source)
    {
        constexpr uint32_t src_bits_size = 7;
        *tp::fc::src = ((*tp::fc::src >> src_bits_size) << src_bits_size) | (uint32_t)source;
    }

    void tp::system::clock::set_ref_frequency(const uint32_t frequency)
    {
        constexpr uint32_t ref_bits_size = 19;
        *tp::fc::ref = ((*tp::fc::ref >> ref_bits_size) << ref_bits_size) | frequency;
    }

    void tp::system::clock::set_accuracy(uint32_t accuracy)
    {
        *tp::fc::interval = ((*tp::fc::interval >> 3) << 3) | accuracy;
    }

    uint32_t tp::system::clock::get_ref_clock_freq()
    {
        return 6000; // Default ref clock frequency is 6mhz; TODO: find a way to get the actual frequency.
    }

    float tp::system::clock::get_frequency(fc_clock_sources source)
    {
        while(!frequency_measure_done()){} // Await previous conversions to finish.
        set_ref_frequency(get_ref_clock_freq()); // The reference frequency should be the frequency of clk_ref in khz. 
        start_measurement(source);
        while(!frequency_measure_done()){} // Wait for the current conversion to finish.
        uint32_t measurement = *tp::fc::result;

        constexpr uint32_t frac_bits_size = 4;
        constexpr uint32_t khz_bits_size = 29;

        constexpr uint32_t frac_offset = (sizeof(uint32_t) * 8) - frac_bits_size;
        constexpr uint32_t khz_offset = (sizeof(uint32_t) * 8) - khz_bits_size;

        float result = (float)((measurement << frac_offset) >> frac_offset) / (float)16; // Get the fraction part of the result.
        result += (measurement << khz_offset) >> (khz_offset + frac_bits_size); // Get the khz part of the result.
        return result * 1000;
    }

} // namespace tp
