#ifndef FSM_H
#define FSM_H

#include "util/pokedex.h"

extern Pokedex pokedex;

typedef enum {
    STATE_HOME,
    STATE_POKEDEX,
    STATE_ADVENTURE,
    STATE_SAVE,
    STATE_EXIT
} AppState;

typedef struct {
    AppState nextAppState;
    int nextStateNextAppState;
} AppStateStruct;

/**
 * @brief Updates the application state structure with new state values.
 *
 * This function modifies an existing `AppStateStruct` by updating its
 * `nextAppState` and `nextStateNextAppState` fields with the provided values.
 * 
 * Use this function if program is exiting current page, and moving back to main fsm. 
 * This function will update `nextAppState` and `nextStateNextAppState` fields, helping 
 * main fsm to move to the correct page. If nextStateNextAppState is 0, it is telling
 * the program to go to the default page of the next appState.
 *
 * @param appStateStruct Pointer to the `AppStateStruct` to be updated.
 * @param nextAppState The new application state to assign to `appState`.
 * @param nextStateNextAppState The new sub-state to assign to `nextStateNextAppState`.
 *
 * @note This function does nothing if `appStateStruct` is NULL.
 */
void update_app_state_struct(AppStateStruct *appStateStruct, AppState nextAppState, int nextStateNextAppState);

void init_fsm(void);

void run_main_fsm(AppStateStruct *appStateStruct);

#endif
