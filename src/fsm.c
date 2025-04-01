#include <stdio.h>
#include "fsm.h"
#include "pages/homePage.h"
#include "pages/pokedexPage.h"
#include "pages/adventurePage.h"
#include "util/input.h"
#include "util/page.h" /*temp until we figure where to place clear_screen() */
#include "util/db.h"

Pokedex pokedex;

const char *savefile = "data/pokedex.dat";

void update_app_state_struct(AppStateStruct *appStateStruct, AppState nextAppState, int nextStateNextAppState) {
    if (!appStateStruct) return;
    appStateStruct->nextAppState = nextAppState;
    appStateStruct->nextStateNextAppState = nextStateNextAppState;
}

/**
 * place init logic here, initial loading from db etc
 */
void init_fsm(void) {
    /* LOAD DB HERE */
    loadPokedex(&pokedex, savefile);
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
    /*int choice;*/ /* placeholder until logic for other states are placed into their own file*/
    /** 1) initialise the struct/ list to store pokemonlist pokemon info here. I will use it 
     * in STATE_POKEDEX switch statement 
     * 
     */
    AppState *currentState;
    currentState = &(appStateStruct->nextAppState);
    init_fsm();
    while (*currentState != STATE_EXIT) {
        switch (*currentState) {
            case STATE_HOME:
                run_home_page(appStateStruct);
                break;

            case STATE_POKEDEX:
                run_pokedex_page(appStateStruct);
                break;

            case STATE_ADVENTURE:
                run_adv_page(appStateStruct);
                break;

            case STATE_SAVE:
                clear_screen();
                /** SAVE DB HERE */
                /* Here you put logic to save progress into db. code will exit the moment gave has been successfully saved*/
                savePokedex(&pokedex, savefile);
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
