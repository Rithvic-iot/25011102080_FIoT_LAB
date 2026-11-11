/*
 * ============================================================================
 * Experiment: CAT 5 (Week 5)
 * Title: Hardware Timer & Interrupt Timing for LED Fading & Stepper Motor
 * Hardware: AT89S52 MCU, Timer 0, P1.0 (PWM LED), P1.1 (Pulse), P2 (ULN2003)
 * Description: Non-blocking 1ms system time base via Timer 0 Interrupt.
 *              Generates software PWM for LED brightness fading (0-100%),
 *              variable frequency square wave, and 4-step stepper motor driver.
 * ============================================================================
 */

#include <reg51.h>

/* Pin Definitions */
sbit PWM_LED    = P1^0; /* Software PWM output */
sbit PULSE_OUT  = P1^1; /* Variable frequency square wave */

/* Global Timebase Counters */
volatile unsigned int system_tick_ms = 0;
volatile unsigned char pwm_counter = 0;
volatile unsigned char duty_cycle = 0;
volatile unsigned char pwm_direction = 1; /* 1: ramping up, 0: ramping down */

/* Stepper motor sequence table (Wave Drive / Full Step) */
code unsigned char stepper_steps[4] = {0x08, 0x04, 0x02, 0x01}; /* P2.3 to P2.0 */
volatile unsigned char step_index = 0;
volatile unsigned int stepper_timer = 0;
volatile unsigned int stepper_interval = 50; /* 50ms per step = Medium Speed */

/**
 * @brief Timer 0 ISR (1.0 ms interrupt rate)
 * Crystal: 11.0592 MHz -> Machine cycle = 1.085 us
 * Counts for 1 ms = 1000 us / 1.085 us = 922 counts
 * Preload: 65536 - 922 = 64614 = 0xFC66
 */
void timer0_ISR(void) interrupt 1 {
    /* Reload Timer 0 registers */
    TH0 = 0xFC;
    TL0 = 0x66;

    system_tick_ms++;
    stepper_timer++;

    /* --- Subtask 1: Software PWM Generation (100 Hz frame, 10 levels) --- */
    pwm_counter++;
    if (pwm_counter >= 10) {
        pwm_counter = 0;
    }
    
    if (pwm_counter < duty_cycle) {
        PWM_LED = 1;
    } else {
        PWM_LED = 0;
    }

    /* --- Subtask 2: Toggle Pulse Out for Frequency Generation --- */
    PULSE_OUT = ~PULSE_OUT;

    /* --- Subtask 3: Stepper Motor Step Generation --- */
    if (stepper_timer >= stepper_interval) {
        stepper_timer = 0;
        P2 = (P2 & 0xF0) | (stepper_steps[step_index] & 0x0F);
        step_index = (step_index + 1) % 4;
    }
}

void timer0_init(void) {
    /* Configure Timer 0 in Mode 1 (16-bit Timer) */
    TMOD = (TMOD & 0xF0) | 0x01;
    
    /* Preload for 1ms */
    TH0 = 0xFC;
    TL0 = 0x66;

    /* Enable Timer 0 Interrupt and Global Interrupt */
    ET0 = 1;
    EA  = 1;

    /* Start Timer 0 */
    TR0 = 1;
}

void main(void) {
    unsigned int last_fade_tick = 0;

    P1 = 0x00;
    P2 = 0x00;

    timer0_init();

    while (1) {
        /* Non-blocking LED fading update every 100 ms */
        if ((system_tick_ms - last_fade_tick) >= 100) {
            last_fade_tick = system_tick_ms;

            if (pwm_direction == 1) {
                duty_cycle++;
                if (duty_cycle >= 10) {
                    duty_cycle = 10;
                    pwm_direction = 0; /* Reverse to fade down */
                }
            } else {
                if (duty_cycle > 0) {
                    duty_cycle--;
                } else {
                    duty_cycle = 0;
                    pwm_direction = 1; /* Reverse to fade up */
                }
            }
        }
    }
}
