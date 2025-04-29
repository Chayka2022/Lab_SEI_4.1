#include "control_relay.h"

void relayInit( Relay_t *relay,
    uint8_t wasModified,
    uint8_t pin, 
    RelayState_t value, 
    void(*pinInit)(uint8_t pin), 
    void(*setState)(uint8_t pin, RelayState_t value)
)
{
    if (relay == NULL || pinInit == NULL || setState == NULL)
    {
        return;
    }
    relay->wasModified = false;
    relay->pin = pin;
    relay->currentState = value;
    relay->pinInit = pinInit;
    relay->pinSetState = setState;

    relay->pinInit(pin);
    relay->pinSetState(pin, value); // Set the initial state of the relay
}

void relayCycleCall(Relay_t* relay)
{
    if (relay->wasModified)
    {
#ifdef DEBUG
        printf("Relay state changed to %d\n\r", relay->currentState);
#endif
        relay->pinSetState(relay->pin, relay->currentState); // Set the new state of the relay
        relay->wasModified = false;
    }
}

inline void relaySetState(Relay_t* relay, RelayState_t value)
{
    relay -> currentState = value;
    relay -> wasModified = true;
}

void relayToggle(Relay_t* relay)
{
#ifdef DEBUG
    printf("Relay state toggled\n\r");
#endif
    if (relay->currentState == RELAY_ON)
    {
        relaySetState(relay, RELAY_OFF);
    }
    else
    {
        relaySetState(relay, RELAY_ON);
    }
}

void relaySet(Relay_t* relay)
{
    relaySetState(relay, RELAY_ON);
}

void relayReset(Relay_t* relay)
{
    relaySetState(relay, RELAY_OFF);
}