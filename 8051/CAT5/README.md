# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 5  

**DATE:** 10/08/2026  

**NAME OF EXP:** Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control  

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller Board + 28BYJ-48 Stepper Motor + ULN2003 Driver + Oscilloscope + Keil µVision C51  

---

## TASK 5A : Hardware Timer 0 Interrupt (1ms Time Base)

### 1. Circuit Diagram

Instead of locking up the CPU with delay loops, we configure Timer 0 to generate an interrupt every 1 millisecond. This 1 ms tick is used to control software PWM for LED dimming, generate square wave pulses, and step the motor.

- **Microcontroller:** AT89S52 @ 11.0592 MHz
- **Timer Preload Calculation:**
  - One machine cycle $= 12 / 11.0592	ext{ MHz} pprox 1.085\,\mu	ext{s}$
  - Counts needed for $1	ext{ ms} = 1000\,\mu	ext{s} / 1.085\,\mu	ext{s} pprox 922	ext{ counts}$
  - In 16-bit Timer Mode 1: Preload $= 65536 - 922 = 64614 = 	ext{0xFC66}$
  - Therefore: `TH0 = 0xFC` and `TL0 = 0x66`
- **Pins Used:** `P1.0` (PWM LED), `P1.1` (Scope test point), `P2.0`-`P2.3` (ULN2003 Stepper Inputs)

![Circuit Diagram](circuit.png)

---

## TASK 5B & 5C : Software PWM LED Fading & Stepper Motor Control

### 1. Software PWM LED Fading

Within the 1 ms timer interrupt, a counter cycles from 0 to 9 (100 Hz PWM frame). If the counter is less than `duty_cycle`, the LED is turned ON; otherwise, it is turned OFF.
- We vary the duty cycle from 0% (OFF) $	o$ 25% (Dim) $	o$ 50% (Medium) $	o$ 75% (Bright) $	o$ 100% (Full) and back down, creating a smooth fading effect.

### 2. Stepper Motor Commutation

The 28BYJ-48 unipolar stepper motor is connected to `P2.0`-`P2.3` through a ULN2003 Darlington driver. We step the motor through a 4-step sequence:
$$	ext{Step 1: } 1000_2 	o 	ext{Step 2: } 0100_2 	o 	ext{Step 3: } 0010_2 	o 	ext{Step 4: } 0001_2$$
- Changing the step interval changes the speed (100ms for slow, 50ms for medium, 10ms for fast).

### 3. Inference

Using hardware timer interrupts allowed multiple time-dependent tasks (PWM dimming, square wave generation, and stepper motor stepping) to run smoothly at the same time without the CPU blocking on delay loops.
