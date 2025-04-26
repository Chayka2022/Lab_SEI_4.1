#ifndef freeRTOS_TASK_SCHEDULER_H
#define freeRTOS_TASK_SCHEDULER_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include "config.h"
#include "own_stdio.h"
#include "control_relay.h"
#include "control_interface.h"

void tasksSetup(void);
void controlRelayTaskInit(void);
void controlRelayTask(void *pvParameters);

#endif // !freeRTOS_TASK_SCHEDULER_H