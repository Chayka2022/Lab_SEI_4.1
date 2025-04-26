#include "freeRTOS_task_scheduler.h"

static Relay_t theRelay;
Relay_t *relay1 = &theRelay;


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

void controlRelayTaskInit(void)
{
    // Initialize the relay
    printf("Initializing relay...\n\r");
    relayInit(
        relay1,
        false,  
        CONTROL_PIN,
        RELAY_OFF,
        relaySetup,
        relaySetState
    );
    printf("Relay initialized");
}

void controlRelayTask(void *pvParameters)
{
	static uint8_t needInit = true;
	if (needInit)
	{
		controlRelayTaskInit();
		needInit = false;
	}

    for(;;)
    {
        relayCycleCall(relay1); // Call the relay cycle function
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
    controlExecute(relay1);
}