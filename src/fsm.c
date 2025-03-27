#include <stdio.h>
#include "fsm.h"
#include "pages/homePage.h"
#include "util/input.h"
#include "util/page.h" /*temp until we figure where to place clear_screen() */

void update_app_state_struct(AppStateStruct *appStateStruct, AppState nextAppState, int nextStateNextAppState) {
    if (!appStateStruct) return;
    appStateStruct->nextAppState = nextAppState;
    appStateStruct->nextStateNextAppState = nextStateNextAppState;
}

/**
 * place init logic here, initial loading from db etc
 */
void init_fsm(void) {
    printf("Starting Pokedex...\n");
}

/* placeholder until logic for other states are placed into their own file*/
int temp_get_user_input(void) {
    int choice;
    while (1) {
        if (scanf("%d", &choice) == 1) break;
        while (getchar() != '\n');  /* Clear input buffer*/
        printf("Invalid input, try again: ");
    }
    return choice;
}

void run_main_fsm(AppStateStruct *appStateStruct) {
    int choice; /* placeholder until logic for other states are placed into their own file*/
    AppState *currentState;
    currentState = &(appStateStruct->nextAppState);
    init_fsm();
    while (*currentState != STATE_EXIT) {
        switch (*currentState) {
            case STATE_HOME:
                run_home_page(appStateStruct);
                break;

            case STATE_POKEDEX:
                clear_screen();
                printf("Rendering Pokédex Page...\n");
                printf("Enter choice (1: Home, 2: Adventure, 3: Exit): ");
                choice = temp_get_user_input();
                if (choice == 1) *currentState = STATE_HOME;
                else if (choice == 2) *currentState = STATE_ADVENTURE;
                else if (choice == 3) *currentState = STATE_SAVE;
                break;

            case STATE_ADVENTURE:
                clear_screen();
                printf("Rendering Adventure Page...\n");
                printf("Enter choice (1: Pokédex, 2: Home, 3: Exit): ");
                choice = temp_get_user_input();
                if (choice == 1) *currentState = STATE_POKEDEX;
                else if (choice == 2) *currentState = STATE_HOME;
                else if (choice == 3) *currentState = STATE_SAVE;

                break;

            /* Here you put logic to save progress into db. code will exit the moment gave has been successfully saved
            */
            case STATE_SAVE:
                clear_screen();
                printf("Saving Game...\n");
                printf("Exiting Game...\n");
                *currentState = STATE_EXIT;
                break;
            /** This step just a placeholder, it will never actually enter here. */
            case STATE_EXIT:
                break;
        }
    }
    printf("Game exited!\n");
}
