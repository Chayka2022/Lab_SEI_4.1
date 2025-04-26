#ifndef CONTROL_RELAY_H
#define CONTROL_RELAY_H

#include <Arduino.h>
#include "config.h"

typedef enum
{
    RELAY_OFF = 0,
    RELAY_ON
} RelayState_t;


typedef struct Relay_t
{
    uint8_t wasModified;
    uint8_t pin;
    RelayState_t currentState;
    void(*relaySetup)(struct Relay_t *self, uint8_t pin);
    void(*setState)(struct Relay_t *self, RelayState_t value); 
} Relay_t;

void relayInit( Relay_t *relay,
                uint8_t wasModified,
                uint8_t pin, 
                RelayState_t value, 
                void(*relaySetup)(Relay_t *self, uint8_t pin), 
                void(*setState)(Relay_t *self, RelayState_t value));
void relayCycleCall(Relay_t* relay);
void relaySetup(Relay_t* relay, uint8_t pin);
void relaySetState(Relay_t* relay, RelayState_t value);

#endif // !CONTROL_RELAY_H