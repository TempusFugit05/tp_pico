#include "clock.h"
#include "pico_system.h"

namespace tp
{
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
        return 6000000; // Default ref clock frequency is 6mhz; TODO: find a way to get the actual frequency.
    }

    uint32_t tp::system::clock::get_frequency(fc_clock_sources source)
    {
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
        return fraction + khz;
    }

} // namespace tp
