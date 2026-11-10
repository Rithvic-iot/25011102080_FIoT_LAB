# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 11  

**DATE:** 14/10/2026  

**NAME OF EXP:** STM32F401RE Cortex-M4: GPIO and User Input Programming  

**HARDWARE SETUP / PLATFORM:** STMicroelectronics NUCLEO-F401RE Board (ARM Cortex-M4 with FPU @ 84 MHz) + Integrated ST-LINK/V2-1 + Keil MDK-ARM + STM32CubeMX  

---

## TASK 11A, 11B & 11C : On-Board Peripherals & Button State Machine

### 1. Circuit Diagram

This experiment transitions to the high-performance STM32 Nucleo-F401RE development board, using its built-in hardware peripherals.

- **Board:** STMicroelectronics NUCLEO-F401RE
- **Core:** ARM Cortex-M4 running at 84 MHz
- **On-board User LED (LD2):** Connected to pin `PA5` (Active HIGH: logic 1 = ON, logic 0 = OFF)
- **On-board User Push Button (B1):** Connected to pin `PC13` with hardware pull-up (Active LOW: logic 0 = Pressed, logic 1 = Released)
- **Built-in Programmer:** ST-LINK/V2-1 on USB (provides programming, debugging, and Virtual COM Port)

![Circuit Diagram](circuit.png)

### 2. Tasks Performed

1. **Task 1 (Basic LED Blink):** Configured `PA5` as GPIO output and toggled the green LED LD2 at 1 Hz using `HAL_Delay(500)`.
2. **Task 2 (Button State Remembrance):** Read the blue button on `PC13`. Each button press toggles the LED state and keeps it in that state even after the button is released.
3. **Task 3 (Short vs Long Press Event Classifier):**
   - **Short Press (< 1000 ms):** Toggles the LED on/off.
   - **Long Press (>= 1000 ms):** Puts the LED into a fast 5 Hz blinking mode.
   - **Subsequent Press:** Clears blinking mode and turns off the LED.

### 3. Core Logic & State Tracking

```c
uint32_t press_start = 0;
uint8_t is_blinking = 0;
uint32_t last_blink_time = 0;

void check_user_button(void) {
    /* Button on PC13 is Active LOW */
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
        if (press_start == 0) {
            press_start = HAL_GetTick();
        }
    } else {
        if (press_start != 0) {
            uint32_t duration = HAL_GetTick() - press_start;
            press_start = 0;
            
            if (duration >= 50 && duration < 1000) {
                /* Short press: toggle LED */
                is_blinking = 0;
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            } else if (duration >= 1000) {
                /* Long press: toggle blinking mode */
                is_blinking = !is_blinking;
            }
        }
    }
}
```

### 4. Inference

The on-board LED and user button on the Nucleo-F401RE board functioned properly. Notice that unlike the Blue Pill where the LED on `PC13` was active-LOW, the Nucleo LD2 on `PA5` is active-HIGH, which required inverting our logic levels accordingly.
