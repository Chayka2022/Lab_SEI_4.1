#include "control_interface.h"

static char commandBuffer[COMMAND_BUFFER_SIZE] = {0};

static const char *controlCommands[NUMBER_OF_COMMANDS] = 
{
    "Relay ON",
    "Relay OFF",
    "Relay TOGGLE",
};

static const char *controlDescriptions[NUMBER_OF_COMMANDS] = 
{
    "Turn the relay ON",
    "Turn the relay OFF",
    "Toggle the relay state"
};

static void (*controlCommandHandler[NUMBER_OF_COMMANDS])(Relay_t *relay) = 
{
    relaySet, // Turn the relay ON
    relayReset,  // Turn the relay OFF
    relayToggle // Toggle the relay state
};

Relay_t theRelay;

void controlInit(void)
{
    relayInit(
        &theRelay,
        false,  
        CONTROL_PIN,
        RELAY_OFF,
        relaySetupPinAsOut,
        relayWrite
    );

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
    // Читаем строку целиком до '\n'
    if (scanf(" %" "255[^\n]", commandBuffer) == 1)  // 255 = COMMAND_BUFFER_SIZE - 1
    {
        // Строка уже не содержит '\n'
    }
    else
    {
        commandBuffer[0] = '\0';
    }

    // Считываем оставшийся символ новой строки, чтобы не остался в буфере
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    controlExecute();
}

void controlExecute(void)
{
    bool matched = false;

    for (uint8_t i = 0; i < NUMBER_OF_COMMANDS; i++)
    {
        // case-insensitive compare full string
        if (strcasecmp(commandBuffer, controlCommands[i]) == 0)
        {
            matched = true;
            //printf executing coomand name
            printf("Executing command: %s\n\r", controlCommands[i]);
            controlCommandHandler[i](&theRelay); // Call the command handler
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