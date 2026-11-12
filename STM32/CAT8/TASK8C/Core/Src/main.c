#include "main.h"

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    uint32_t press_start = 0;
    uint8_t is_blinking = 0;
    uint32_t last_blink = 0;
    
    while (1) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
            if (press_start == 0) press_start = HAL_GetTick();
        } else {
            if (press_start != 0) {
                uint32_t dur = HAL_GetTick() - press_start;
                press_start = 0;
                if (dur >= 50 && dur < 1000) {
                    is_blinking = 0;
                    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                } else if (dur >= 1000) {
                    is_blinking = !is_blinking;
                }
            }
        }
        
        if (is_blinking && (HAL_GetTick() - last_blink >= 100)) {
            last_blink = HAL_GetTick();
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        }
    }
}
