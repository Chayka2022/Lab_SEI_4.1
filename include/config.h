#ifndef config_h
#define config_h

#define DEBUG

#ifdef DEBUG
#include "stdio.h"
#endif // DEBUG

#define BAUDRATE 115200

#define CONTROL_PIN 13

#define COMMAND_BUFFER_SIZE 64
#define NUMBER_OF_COMMANDS 3

#endif // !config_h