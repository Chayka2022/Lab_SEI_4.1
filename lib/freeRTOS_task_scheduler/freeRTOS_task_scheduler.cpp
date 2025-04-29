#include "freeRTOS_task_scheduler.h"

extern Relay_t theRelay;

void tasksSetup()
{
    xTaskCreate(controlRelayTask,
                "Control Relay Task",
                128,
                NULL,
                1,
                NULL
            );

    vTaskStartScheduler();
}

void controlRelayTask(void *pvParameters)
{
	static uint8_t needInit = true;
	if (needInit)
	{
		needInit = false;
	}

    for(;;)
    {
        relayCycleCall(&theRelay); // Call the relay cycle function
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
    }

}

void vApplicationIdleHook(void)
{
    static uint8_t needInit = true;
    if (needInit)
    {
        own_stdio_setup(BAUDRATE);
        controlInit();
        needInit = false;
    }

    controlGetCommand();
}