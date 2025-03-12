#ifndef INPUT_H
#define INPUT_H

struct InputState; /*Forward declaration*/

/*
    Object that captures information about current/next state of 
    appState_fsm and main_fsm, and stores logic on how to parse inputs
*/
typedef struct InputState {
    int errorState;
    const int inputSize;
    int appState;
    int stateAppState;
    void (*parserFunction)(struct InputState *inputState, char *input);
    char *previousInput; /*for debugging purpose*/
} InputState;

/**
 * @brief Clears the input buffer to remove any leftover characters.
 *
 * This function reads and discards characters from the input buffer until 
 * a newline ('\n') or EOF is encountered. It is used to prevent unintended 
 * input behavior caused by excess characters in the buffer.
 */
void clear_input_buffer(void);

/**
 * @brief Updates the input state structure with new values.
 *
 * This function modifies the `InputState` structure by updating its error state, 
 * application state, and sub-state (`stateAppState`). It is used to manage the 
 * application's flow based on user input.
 *
 * @param inputState Pointer to the `InputState` structure to be updated.
 * @param errorState New error state value.
 * @param stateAppState New stateAppState value (represents sub-state within a page).
 * @param appState New appState value (represents high-level application state).
 */
void updateInputState(InputState *inputState, int errorState, int stateAppState, int appState);

/**
 * @brief Handles user input and updates the application's state accordingly.
 *
 * This function prompts the user for input and reads it using `fgets`. 
 * If the input buffer contains excess characters (i.e., user input exceeds buffer size), 
 * it calls `clear_input_buffer()` to remove the remaining characters.
 * After processing the input, it passes the string to the parser function 
 * (`inputState->parserFunction`) for further handling.
 *
 * @param inputState Pointer to the `InputState` structure, which contains 
 *                   the application's current state and parser function.
 */
void get_user_input(InputState *inputState);

#endif
