#ifndef CONTROL_RELAY_WRAPPER_H
#define CONTROL_RELAY_WRAPPER_H

#include <stdint.h>
#include <stdlib.h>
#include <Arduino.h>
#include "config.h"
#include "control_relay.h"


// Wrapper functions for the relay control
void relaySetupPinAsOut(uint8_t pin);
void relayWrite(uint8_t pin, RelayState_t value);

#endif // !CONTROL_RELAY_WRAPPER_H