#include "control_relay.h"

void relayInit( Relay_t *relay,
                uint8_t wasModified,
                uint8_t pin, 
                RelayState_t value, 
                void(*relaySetup)(Relay_t*,uint8_t pin),  
                void(*setState)(Relay_t*, RelayState_t value))
{
    printf("!!Init relay init\n\r");

    if (relay == NULL || relaySetup == NULL || setState == NULL)
    {
        return;
    }
    relay->wasModified = false;
    relay->pin = pin;
    relay->currentState = value;
    relay->relaySetup = relaySetup;
    relay->setState = setState;

    relay->relaySetup(relay, pin);
}

void relaySetup(Relay_t* relay, uint8_t pin)
{
    if (pin == 0 || relay == NULL)
    {
        return;
    }
    relay->pin = pin;
    pinMode(relay->pin, OUTPUT);
    digitalWrite(relay->pin, relay->currentState);
}

void relaySetState(Relay_t* relay, RelayState_t value)
{
    if (relay == NULL)
    {
        printf("Relay is not initialized or value is invalid\n\r");
        return;
    }
    if (value == RELAY_ON)
    {
        digitalWrite(relay->pin, HIGH); // Turn the relay ON
    }
    else if (value == RELAY_OFF)
    {
        digitalWrite(relay->pin, LOW); // Turn the relay OFF
    }
    relay->wasModified = true; // Set the wasModified flag to true
}