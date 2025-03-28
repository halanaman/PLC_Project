#include <string.h>
#include <stdio.h>
#include "input.h"
#include <stdlib.h> 
#include "constants.h"

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void update_input_state(InputState *inputState, int errorState, int stateAppState, int appState, int nextStateNextAppState) {
    if (!inputState) return;
    inputState->errorState = errorState;
    inputState->stateAppState = stateAppState;
    inputState->appState = appState;
    inputState->nextStateNextAppState = nextStateNextAppState; 
}

void get_user_input(InputState *inputState, int leaveAppStateEnumValue) {
    char input[MAX_MENU_INPUT_LENGTH + 1]; /** fget() will make last character a new line char */
    if (!inputState || !inputState->parserFunction) {
        update_input_state(inputState, -1, leaveAppStateEnumValue, STATE_SAVE, 0); /*terminates if mem not allocated*/
        return;
    }

    /* printing errors based on errorState */
    switch(inputState->errorState) {
        case -1: /* should never come here, as program should terminate in this scenario*/
            printf("memory problems or program problems, resulting in early termination");
            break;
        case 0:
            break;
        case 1:
            printf("Invalid input, try again!");
            break;
        case 2:
            printf("Pokemon with this number does not exist.");
            break;
        case 3:
            printf("Memory allocation error. Try again.");
            break;
    }
    printf("\nEnter choice: ");
    
    /* Gets input based on input size, clear stdin buffer if needed, then replaces newline character with /0 */
    if (fgets(input, sizeof(input), stdin) == NULL) {
        update_input_state(inputState, -1, leaveAppStateEnumValue, STATE_SAVE, 0); /*terminates if fgets() fail*/
        return;
    }
    if (strchr(input, '\n') == NULL) {
        clear_input_buffer();
    }
    input[strcspn(input, "\n")] = '\0';  /*Remove newline*/
    
    /* 
    this is the part where your parser will be applied onto the input to determine 
    your next input
    */
    inputState->parserFunction(inputState, input);
}
