#ifndef CONTROL_RELAY_H
#define CONTROL_RELAY_H

#include <stdint.h>
#include <stdlib.h>
#include "config.h"

typedef enum
{
    RELAY_OFF = 0,
    RELAY_ON
} RelayState_t;

typedef struct
{
    // Private members
    uint8_t wasModified;
    uint8_t pin;
    RelayState_t currentState;
    void(*pinInit)(uint8_t pin);
    void(*pinSetState)(uint8_t pin, RelayState_t value); 
} Relay_t;

void relayInit( Relay_t *relay,
                uint8_t wasModified,
                uint8_t pin, 
                RelayState_t value, 
                void(*relaySetup)(uint8_t pin), 
                void(*setState)(uint8_t pin, RelayState_t value)
            );

void relayCycleCall(Relay_t* relay);

void relaySetState(Relay_t* relay, RelayState_t value);
void relayToggle(Relay_t* relay);
void relaySet(Relay_t* relay);
void relayReset(Relay_t* relay);

#endif // !CONTROL_RELAY_H