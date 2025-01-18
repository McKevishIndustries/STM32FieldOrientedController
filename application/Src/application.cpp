//
// Created by Kevin McElligott on 15/01/2025.
//

#include "application.h"

#include "stm32f4xx_ll_gpio.h"
#include "main.h"

extern "C" {

    void setup() {
        // For future use
    }

    void loop() {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay (200);
    }
}