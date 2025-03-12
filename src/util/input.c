#include <string.h>
#include <stdio.h>
#include "input.h"
#include <stdlib.h> 
#include "constants.h"

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void updateInputState(InputState *inputState, int errorState, int stateAppState, int appState) {
    if (!inputState) return;
    inputState->errorState = errorState;
    inputState->stateAppState = stateAppState;
    inputState->appState = appState;
}

void get_user_input(InputState *inputState) {
    char input[MAX_MENU_INPUT_LENGTH + 1];
    if (!inputState) {
        updateInputState(inputState, -1, 1, 3); /*terminates if mem not allocated*/
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
            printf("custom error");
            break;
        case 3:
            printf("custom error");
            break;
    }
    printf("\nEnter choice: ");

    /* Gets input, does initial parsing of removing newline and limiting final input size */
    if (fgets(input, sizeof(input), stdin) == NULL) {
        updateInputState(inputState, -1, 1, 3);
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
