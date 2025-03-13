#ifndef INPUT_H
#define INPUT_H

#include "../fsm.h"

struct InputState; /*Forward declaration*/

/*
    Object that captures information about current/next state of 
    appState_fsm and main_fsm, and stores logic on how to parse inputs
*/
typedef struct InputState {
    int errorState;
    AppState appState; 
    int stateAppState; /** Represents state of appState_fsm. There is no safety check at compile time, so please ensure you use this correctly.*/
    void (*parserFunction)(struct InputState *inputState, char *input);
    char *previousInput; /*for debugging purpose*/
    int nextStateNextAppState;
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
 * Always set nextStateNextAppState to 0, unless you want to dictate the sub-state of
 * the main_fsm's new state.
 *
 * @param inputState Pointer to the `InputState` structure to be updated.
 * @param errorState New error state value.
 * @param stateAppState New stateAppState value of current appState(represents sub-state within a page).
 * @param appState New appState value (represents high-level application state).
 * @param nextStateNextAppState New stateAppState value of next appState(also represents sub-state within a page).
 */
void update_input_state(InputState *inputState, int errorState, int stateAppState, int appState, int nextStateNextAppState);

/**
 * @brief Handles user input and updates the application state accordingly.
 *
 * This function retrieves user input from standard input, processes it,
 * and applies a parser function to determine the next state of the application.
 * It also handles error messages and ensures memory safety.
 *
 * @param inputState A pointer to the InputState structure, which tracks the input state.
 * @param leaveAppStateEnumValue The enum value representing exiting current state into the main fsm.
 *
 * @note If inputState is NULL or does not have a valid parser function, the function 
 *       will call update_input_state to set an error state and terminate early.
 *
 * @details 
 * - First, the function checks if inputState is valid; if not, it triggers early termination.
 * - It prints any relevant error messages based on `inputState->errorState`.
 * - It prompts the user for input and reads it using `fgets`.
 * - If the input is too long and exceeds the buffer, it clears the input buffer.
 * - The newline character is removed to ensure proper string handling.
 * - Finally, it calls the parser function stored in `inputState->parserFunction` 
 *   to process the input and determine the next state.
 *
 * @note If memory allocation issues occur, or `fgets` fails, the function sets 
 *       `inputState->errorState` to `-1` and transitions the application to `STATE_SAVE` 
 *       to ensure graceful termination.
 */
void get_user_input(InputState *inputState, int leaveAppStateEnumValue);

#endif
