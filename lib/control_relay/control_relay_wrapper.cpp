#include "Arduino.h"
#include "control_relay.h"
#include "config.h"

void relaySetupPinAsOut(uint8_t pin)
{
    if (pin >= 0 || pin <= 13) // Assuming pin numbers are from 0 to 13
    {
#ifdef ARDUINO
        pinMode(pin, OUTPUT); // Set the pin as output
#elif STM32
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        __HAL_RCC_GPIOB_CLK_ENABLE(); // Enable the GPIO clock for port B

        GPIO_InitStruct.Pin = GPIO_PIN_0; // Assuming pin 0 is used for the relay
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Set as push-pull output
        GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down resistors
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Set speed to low
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); // Initialize the pin
#endif
    }
    else
    {
#ifdef DEBUG
        printf("Invalid pin number. Pin must be between 0 and 13.\n\r");
#endif
    }
}

void relayWrite(uint8_t pin, RelayState_t value)
{
    if (value == RELAY_ON)
    {
#ifdef ARDUINO
        digitalWrite(pin, HIGH); // Turn the relay ON
#elif STM32
        HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_SET); // Turn the relay ON
#endif
    }
    else if (value == RELAY_OFF)
    {
#ifdef ARDUINO
        digitalWrite(pin, LOW); // Turn the relay OFF
#elif STM32
        HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_RESET); // Turn the relay OFF
#endif
    }
}