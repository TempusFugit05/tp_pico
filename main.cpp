#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#include "pico/stdlib.h"
#include "tp_pico.h"

#define REPEAT(count) for (size_t _i = 0; _i < count; _i++)

constexpr float C = 130.813;
constexpr float CS = 138.591;
constexpr float D = 146.832;
constexpr float DS = 155.563;
constexpr float E = 164.814;
constexpr float F = 174.614;
constexpr float FS = 184.997;
constexpr float G = 195.998;
constexpr float GS = 207.652;
constexpr float A = 220;
constexpr float AS = 233.082;
constexpr float B = 246.942;

constexpr int NOTE_LEN = 1250;

tp::pwm led2 = tp::pwm(17, -1);
tp::pwm led = tp::pwm(25);

void play_note(const float note, const float time)
{
    const uint32_t delay = NOTE_LEN / time;
    if(note == 0)
    {
        led2.enable(false);
        led.set_duty_cycle(0);
        sleep_ms(delay);
        return;
    }
    led.set_duty_cycle(std::max(std::min((((float)note / (E * 4)) * 100) - (((float)C / (E * 4)) * 100), (float)100), (float)2));
    led2.enable(true);
    led2.set_frequency(note);
    sleep_ms((delay * 4) / 5);
    led.set_duty_cycle(0);
    led2.enable(false);
    sleep_ms(delay / 5);
}

void intro()
{
    play_note(E * 2, 8);
    play_note(E * 2, 8);
    play_note(0, 8);
    play_note(E * 2, 8);
    play_note(0, 8);
    play_note(C * 2, 8);
    play_note(E * 2, 4);

    play_note(G * 2, 4);
    play_note(0, 4);
    play_note(G, 4);
    play_note(0, 4);
}

void main_section()
{
    play_note(C * 2, 4);
    play_note(0, 8);
    play_note(G, 4);
    play_note(0, 8);
    play_note(E, 4);

    play_note(0, 8);
    play_note(A, 4);
    play_note(B, 4);
    play_note(AS, 8);
    play_note(A, 4);
    
    play_note(G, 6);
    play_note(E * 2, 6);
    play_note(G * 2, 6);
    play_note(A * 2, 4);
    play_note(F * 2, 8);
    play_note(G * 2, 8);

    play_note(0, 8);
    play_note(E * 2, 4);
    play_note(C * 2, 8);
    play_note(D * 2, 8);
    play_note(B, 4);
    play_note(0, 8);

}

void funky_section()
{
    play_note(E * 2, 8);
    play_note(C * 2, 4);
    play_note(G, 8);
    play_note(0, 4);
    play_note(GS, 4);

    play_note(A, 8);
    play_note(F * 2, 4);
    play_note(F * 2, 8);
    play_note(A, 4);
    play_note(0, 4);
    
    play_note(B, 6);
    play_note(A * 4, 6);
    play_note(A * 4, 6);
    play_note(A * 4, 6);
    play_note(G * 2, 6);
    play_note(F * 2, 6);

    play_note(E * 2, 8);
    play_note(C * 2, 4);
    play_note(A, 8);
    play_note(G, 4);
    play_note(0, 4);

    play_note(E * 2, 8);
    play_note(C * 2, 4);
    play_note(G, 4);
    play_note(0, 4);
    play_note(GS, 4);
    
    play_note(A, 8);
    play_note(F * 2, 4);
    play_note(F * 2, 8);
    play_note(A * 2, 4);
    play_note(0, 4);

    play_note(B * 2, 8);
    play_note(F * 2, 4);
    play_note(F * 2, 8);
    play_note(F * 2, 6);
    play_note(E * 2, 6);
    play_note(D * 2, 6);

    play_note(G, 8);
    play_note(E, 4);
    play_note(E, 8);
    play_note(C, 4);
    play_note(0, 4);
}

int main()
{
    stdio_init_all();
    
    tp::io_bank0::reset();

    led.enable(true);
    led2.set_duty_cycle(50);

    tp::adc test = tp::adc(tp::adc_pin::GPIO_26);

    while (true)
    {
        intro();

        REPEAT(2){main_section();}
        
        REPEAT(2)
        {
            play_note(0, 4);
            play_note(G * 2, 8);
            play_note(FS * 2, 8);
            play_note(F * 2, 8);
            play_note(DS * 2, 4);
            play_note(E *2, 8);

            play_note(0, 8);
            play_note(GS, 8);
            play_note(A, 8);
            play_note(C * 2, 8);
            play_note(0, 8);
            play_note(A, 8);
            play_note(C * 2, 8);
            play_note(D * 2, 8);

            play_note(0, 4);
            play_note(G * 2, 8);
            play_note(FS * 2, 8);
            play_note(F * 2, 8);
            play_note(DS * 2, 4);
            play_note(E * 2, 8);

            play_note(0, 8);
            play_note(C * 4, 4);
            play_note(C * 4, 8);
            play_note(C * 4, 4);
            play_note(0, 4);

            play_note(0, 4);
            play_note(G * 2, 8);
            play_note(FS * 2, 8);
            play_note(F * 2, 8);
            play_note(DS * 2, 4);
            play_note(E * 2, 8);

            play_note(0, 8);
            play_note(GS, 8);
            play_note(A, 8);
            play_note(C * 2, 8);
            play_note(0, 8);
            play_note(A, 8);
            play_note(C * 2, 8);
            play_note(D * 2, 8);

            play_note(0, 4);
            play_note(DS * 2, 4);
            play_note(0, 8);
            play_note(D * 2, 4);
            play_note(0, 8);
        
            play_note(C * 2, 4);
            play_note(0, 4);
            play_note(0, 2);
        }

        play_note(C * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(D * 2, 4);

        play_note(E * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(A, 8);
        play_note(G, 2);

        play_note(C * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C, 8);
        play_note(D * 2, 8);
        play_note(E * 2, 8);

        play_note(0, 1);
    
        play_note(C * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(D * 2, 4);

        play_note(E * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(A, 8);
        play_note(G, 2);

        intro();

        REPEAT(2){main_section();}
    
        REPEAT(2)
        {
            funky_section();
        }

        play_note(C * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(D * 2, 8);

        play_note(E * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(A, 8);
        play_note(G, 2);

        play_note(C * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(D * 2, 8);
        play_note(E * 2, 8);

        play_note(0, 4);
        play_note(E * 2, 8);
        play_note(G * 2, 8);
        play_note(E * 4, 8);
        play_note(C * 4, 8);
        play_note(D * 4, 8);
        play_note(G * 4, 8);

        play_note(C * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(C * 2, 8);
        play_note(D * 2, 8);

        play_note(E * 2, 8);
        play_note(C * 2, 8);
        play_note(0, 8);
        play_note(A, 8);
        play_note(G, 2);

        intro();

        REPEAT(2)
        {
            funky_section();
        }

        play_note(C * 2, 4);
        play_note(0, 8);
        play_note(G, 4);
        play_note(0, 8);
        play_note(E, 4);

        play_note(A, 3);
        play_note(B, 3);
        play_note(A, 3);
        play_note(GS, 3);
        play_note(AS, 3);
        play_note(A, 3);

        play_note(E, 8);
        play_note(D, 8);
        play_note(E, (float)3 / 4);

        play_note(0, 0.1);
    }
}