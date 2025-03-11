#include <stdio.h>
#include "fsm.h"
#include "pages/homePage.h"
#include "util/input.h"
#include "util/page.h" /*temp until we figure where to place clear_screen() */

/**
 * place init logic here, initial loading from db etc
 */
void init_fsm(void) {
    printf("Starting Pokedex...\n");
}

void handle_state(AppState *currentState) {
    int choice;
    
    init_fsm();
    while (*currentState != STATE_EXIT) {
        switch (*currentState) {
            case STATE_HOME:
                render_home_page();
                printf("Enter choice (1: Pokédex, 2: Adventure, 3: Exit): ");
                choice = get_user_input();
                if (choice == 1) *currentState = STATE_POKEDEX;
                else if (choice == 2) *currentState = STATE_ADVENTURE;
                else if (choice == 3) *currentState = STATE_SAVE;
                break;

            case STATE_POKEDEX:
                clear_screen();
                printf("Rendering Pokédex Page...\n");
                printf("Enter choice (1: Home, 2: Adventure, 3: Exit): ");
                choice = get_user_input();
                if (choice == 1) *currentState = STATE_HOME;
                else if (choice == 2) *currentState = STATE_ADVENTURE;
                else if (choice == 3) *currentState = STATE_SAVE;
                break;

            case STATE_ADVENTURE:
                clear_screen();
                printf("Rendering Adventure Page...\n");
                printf("Enter choice (1: Pokédex, 2: Home, 3: Exit): ");
                choice = get_user_input();
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

            case STATE_EXIT:
                break;
        }
    }
    printf("Game exited!\n");
}
