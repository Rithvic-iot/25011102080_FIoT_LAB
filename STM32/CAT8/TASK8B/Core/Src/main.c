#include "main.h"

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    uint8_t last_btn = GPIO_PIN_RESET;
    
    while (1) {
        uint8_t curr = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        if (curr == GPIO_PIN_SET && last_btn == GPIO_PIN_RESET) {
            HAL_Delay(25); /* Debounce */
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET);
                HAL_Delay(25);
            }
        }
        last_btn = curr;
    }
}
