# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 8  

**DATE:** 18/09/2026  

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill Development Board (STM32F103C8T6 ARM Cortex-M3 @ 72 MHz) + ST-Link V2 Debugger + External Push-Button + Keil MDK-ARM + STM32CubeMX  

---

## TASK 8A : Basic GPIO Input/Output Bring-Up

### 1. Circuit Diagram

The experiment demonstrates basic GPIO configuration and input/output control on the STM32F103C8T6 Blue Pill development board.

- **Development Board:** STM32 Blue Pill
- **Microcontroller:** STM32F103C8T6 (32-bit ARM Cortex-M3)
- **Clock Frequency:** 72 MHz (8 MHz external crystal multiplied via PLL)
- **On-board User LED:** Connected to `PC13` (Active LOW: writing logic 0 turns ON, logic 1 turns OFF)
- **Input Switch:** Tactile push-button connected to `PA0` with a 10 kΩ pull-down resistor to GND and button contact to +3.3V

![Circuit Diagram](circuit.png)

### 2. Core HAL Functions Utilized

| Purpose | HAL Function | Implementation in Experiment |
|---|---|---|
| **Read Switch State** | `HAL_GPIO_ReadPin()` | Polls logic state of pin `PA0` (Pressed = `GPIO_PIN_SET`) |
| **Direct LED Output** | `HAL_GPIO_WritePin()` | Sets `PC13` to `GPIO_PIN_RESET` (ON) or `GPIO_PIN_SET` (OFF) |
| **Toggle Output State** | `HAL_GPIO_TogglePin()` | Inverts current logic state of `PC13` |
| **Millisecond Timebase** | `HAL_GetTick()` | Returns millisecond system tick counter for non-blocking timing |

---

## TASK 8B & 8C : Non-Blocking Short Press vs Long Press Event Classifier

### 1. Core Logic & State Machine

**Working Principle:**

Rather than using CPU-blocking delay functions (`HAL_Delay()`), which paralyze the processor and ignore incoming events, timing duration is classified asynchronously via `HAL_GetTick()`.

```text
Button Pressed (PA0 == HIGH)
       │
       ▼
Record start_time = HAL_GetTick()
       │
       ▼
Continue background execution
       │
       ▼
Button Released (PA0 == LOW)
       │
       ▼
duration = HAL_GetTick() - start_time
       │
       ├── If 50ms <= duration < 1000ms  ──> Short Press Event: Toggle LED / Stop Blinking
       └── If duration >= 1000ms         ──> Long Press Event: Toggle 5 Hz Blinking Mode
```

| User Action | Duration ($\Delta t$) | System Response |
|---|---|---|
| **Short Press** | $< 1000	ext{ ms}$ | Toggle LED ON/OFF state |
| **Long Press** | $\ge 1000	ext{ ms}$ | LED enters continuous 5 Hz blinking mode |
| **Subsequent Short Press** | $< 1000	ext{ ms}$ | Stop blinking mode immediately |
| **Subsequent Long Press** | $\ge 1000	ext{ ms}$ | Re-enter continuous blinking mode |

### 2. Code Base

Implemented in `Core/Src/main.c` utilizing STM32 HAL GPIO and SysTick APIs without any blocking delay loops.

### 3. Inference

The STM32 HAL GPIO drivers performed reliable switch detection. The non-blocking millisecond timestamping technique accurately distinguished between short toggles and sustained long presses while maintaining seamless concurrent LED blinking.
