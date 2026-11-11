/*
 * ============================================================================
 * Experiment: CAT 8 (Week 7)
 * Title: STM32 GPIO Bring-Up and Switch-Controlled LED
 * Platform: STM32 Blue Pill (STM32F103C8T6 ARM Cortex-M3)
 * Peripherals: On-board User LED (PC13 - Active LOW), Push Button (PA0)
 * Description:
 *   - Task 8A: Direct GPIO Input/Output mirror
 *   - Task 8B: Event-based switch toggle with software debouncing
 *   - Task 8C: Non-blocking Short Press (< 1s) vs Long Press (>= 1s) classifier
 * ============================================================================
 */

#include "main.h"

/* Private variables */
uint32_t press_start_time = 0;
uint8_t button_pressed = 0;
uint8_t blinking_mode = 0;
uint32_t last_blink_tick = 0;

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
    /* Reset of all peripherals, Initializes the Flash interface and Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize configured GPIOs */
    MX_GPIO_Init();

    /* Ensure LED is initially OFF (PC13 is Active LOW on Blue Pill) */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

    while (1) {
        GPIO_PinState btn_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        uint32_t current_time = HAL_GetTick();

        /* Detect Button Press (Transition to HIGH) */
        if (btn_state == GPIO_PIN_SET && !button_pressed) {
            button_pressed = 1;
            press_start_time = current_time;
        }
        /* Detect Button Release (Transition to LOW) */
        else if (btn_state == GPIO_PIN_RESET && button_pressed) {
            button_pressed = 0;
            uint32_t press_duration = current_time - press_start_time;

            if (press_duration >= 50) { /* Debounce threshold */
                if (press_duration < 1000) {
                    /* --- SHORT PRESS (< 1 second) --- */
                    if (blinking_mode) {
                        blinking_mode = 0; /* Stop blinking */
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET); /* OFF */
                    } else {
                        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); /* Toggle LED */
                    }
                } else {
                    /* --- LONG PRESS (>= 1 second) --- */
                    blinking_mode = !blinking_mode; /* Toggle blinking state */
                }
            }
        }

        /* Non-blocking continuous blinking mode execution */
        if (blinking_mode) {
            if ((current_time - last_blink_tick) >= 200) { /* 5 Hz toggle */
                last_blink_tick = current_time;
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            }
        }
    }
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure PC13 as Output (User LED) */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Configure PA0 as Input (User Push-Button with pull-down) */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
