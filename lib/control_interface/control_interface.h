#ifndef CONTROL_INTERFACE_H
#define CONTROL_INTERFACE_H

#include "config.h"
#include "own_stdio.h"

#include "control_relay.h"

#include <string.h>   // for strlen(), fgets()
#include <stdlib.h>  // for atoi()

void controlInit(void);
void controlGetCommand(void);
void controlExecute(Relay_t *relay);
void relaySetStateOnWrapper(Relay_t *relay);
void relaySetStateOffWrapper(Relay_t *relay);

#endif // !CONTROL_INTERFACE_H