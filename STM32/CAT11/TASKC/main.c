/*
 * ============================================================================
 * Experiment: CAT 11 (Week 11)
 * Title: STM32F401RE Cortex-M4: GPIO and User Input Programming
 * Platform: STMicroelectronics NUCLEO-F401RE Development Board (Cortex-M4 @ 84 MHz)
 * Peripherals: On-board Green User LED (LD2 - PA5), User Push-Button (B1 - PC13)
 * Description:
 *   - Task 1: On-board LED bring-up with fixed 1 Hz toggling
 *   - Task 2: Push-button toggle with state remembrance after release
 *   - Task 3: Non-blocking Short-Press (< 1s) vs Long-Press (>= 1s) duration detector
 * ============================================================================
 */

#include "main.h"

uint32_t btn_down_tick = 0;
uint8_t btn_active = 0;
uint8_t fast_blink_active = 0;
uint32_t last_toggle_time = 0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    /* Initial state: LED OFF */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    while (1) {
        /* On Nucleo-64, B1 is Active LOW (normally HIGH, pressed = LOW) */
        GPIO_PinState pin_val = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
        uint32_t now = HAL_GetTick();

        if (pin_val == GPIO_PIN_RESET && !btn_active) {
            btn_active = 1;
            btn_down_tick = now;
        } else if (pin_val == GPIO_PIN_SET && btn_active) {
            btn_active = 0;
            uint32_t duration = now - btn_down_tick;

            if (duration >= 40) { /* Debounce filter */
                if (duration < 1000) {
                    /* Short Press Action: Toggle or stop blinking */
                    if (fast_blink_active) {
                        fast_blink_active = 0;
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
                    } else {
                        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                    }
                } else {
                    /* Long Press Action: Enter 5 Hz continuous blinking */
                    fast_blink_active = !fast_blink_active;
                }
            }
        }

        /* Non-blocking background blink handler */
        if (fast_blink_active) {
            if ((now - last_toggle_time) >= 100) { /* 100ms interval = 5 Hz */
                last_toggle_time = now;
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            }
        }
    }
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure PA5 as Output (User LED LD2) */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Configure PC13 as Input (Blue User Button B1) */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL; /* Pull-up is on board */
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
