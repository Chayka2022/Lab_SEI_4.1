#include "control_interface.h"

static char commandBuffer[COMMAND_BUFFER_SIZE] = {0};

static const char *controlCommands[NUMBER_OF_COMMANDS] = 
{
    "Relay ON",
    "Relay OFF"
};

static const char *controlDescriptions[NUMBER_OF_COMMANDS] = 
{
    "Turn the relay ON",
    "Turn the relay OFF"
};

static void (*controlCommandHandler[NUMBER_OF_COMMANDS])(Relay_t *relay) = 
{
    relaySetStateOnWrapper, // Turn the relay ON
    relaySetStateOffWrapper  // Turn the relay OFF
};

void controlInit(void)
{
    printf("Control interface initialized!\n\r");
    printf("Available commands:\n\r");
    for (uint8_t i = 0; i < NUMBER_OF_COMMANDS; i++)
    {
        printf("%s: %s\n\r", controlCommands[i], controlDescriptions[i]);
    }
    printf("Enter command:\n\r");
}

void controlGetCommand(void)
{
    // Read a line (up to COMMAND_BUFFER_SIZE-1 chars) from stdin
    // Note: fgets will include the '\n' if there's room.
    if (fgets(commandBuffer, COMMAND_BUFFER_SIZE, stdin) != NULL)
    {
        // strip trailing newline, if present
        size_t len = strlen(commandBuffer);
        if (len > 0 && commandBuffer[len - 1] == '\n')
        {
            commandBuffer[len - 1] = '\0';
        }
    }
    else
    {
        // In case of error or EOF, make it an empty string
        commandBuffer[0] = '\0';
    }
}

void controlExecute(Relay_t *relay)
{
    if (relay == NULL)
    {
        printf("Relay is not initialized.\n\r");
        return;
    }

    bool matched = false;

    for (uint8_t i = 0; i < NUMBER_OF_COMMANDS; i++)
    {
        // case-insensitive compare full string
        if (strcasecmp(commandBuffer, controlCommands[i]) == 0)
        {
            matched = true;
            //printf executing coomand name
            printf("Executing command: %s\n\r", controlCommands[i]);
            controlCommandHandler[i](relay);
            break;
        }
    }

    if (!matched)
    {
        if (commandBuffer[0] != '\0')
        {
            printf("Unknown command: '%s'\n\r", commandBuffer);
        }
        else
        {
            printf("No command entered.\n\r");
        }
    }

    // prompt for the next command
    printf("Enter command:\n\r");
}


void relaySetStateOnWrapper(Relay_t *relay)
{
    relay->currentState = RELAY_ON;
    relay->wasModified = true;
}

void relaySetStateOffWrapper(Relay_t *relay)
{
    relay->currentState = RELAY_OFF;
    relay->wasModified = true;
}