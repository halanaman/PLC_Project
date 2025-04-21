#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "controller.h"
#include "view.h"
#include "../utils/constants.h"

void controller_init(Controller* controller, FSM* fsm) {
    controller->fsm = fsm;
    controller->isRunning = 1;
}

Page* controller_getPage(Controller* controller) {
    State currentState;
    int currentSubState, errorState;
    currentState = fsm_getCurrentState(controller->fsm);
    currentSubState = fsm_getCurrentSubState(controller->fsm);
    errorState = fsm_getErrorState(controller->fsm);

    return page_get(currentState, currentSubState, errorState, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void controller_handleInput(Controller* controller, const char* input) {
    State currentState;
    int currentSubState;
    Page* page;
    currentState = fsm_getCurrentState(controller->fsm);
    currentSubState = fsm_getCurrentSubState(controller->fsm);

    switch (currentState) {
        case STATE_HOME:
            if (strcmp(input, "1") == 0)        { fsm_updateState(controller->fsm, STATE_POKEDEX, 0, 0); }
            else if (strcmp(input, "2") == 0)   { fsm_updateState(controller->fsm, STATE_ADVENTURE, 0, 0); }
            else if (strcmp(input, "s") == 0)   { fsm_updateState(controller->fsm, STATE_SAVE, 0, 0); }
            else { fsm_updateState(controller->fsm, STATE_HOME, currentSubState, 1); }
            break;
        case STATE_ADVENTURE:
            switch (currentSubState) {
                case 0:
                    /* Adventure Cutscene */
                    if (strcmp(input, "1") == 0) {
                        /* Generate random number from 0 to 99 */
                        int random_num;
                        srand(time(NULL));
                        random_num = rand() % 100;

                        if (random_num < 70) {
                            /* 70% chance of encountering Pokemon (subState == 1) */
                            fsm_updateState(controller->fsm, STATE_ADVENTURE, 1, 0);
                        } else {
                            /* 30% chance of encountering nothing (subState == 2) */
                            fsm_updateState(controller->fsm, STATE_ADVENTURE, 2, 0);
                        }
                    }
                    else if (strcmp(input, "b") == 0) { fsm_updateState(controller->fsm, STATE_HOME, 0, 0); }
                    else { fsm_updateState(controller->fsm, STATE_ADVENTURE, currentSubState, 1); }
                    break;
                case 1:
                    /* Pokemon encountered */
                    if (strcmp(input, "1") == 0)        { fsm_updateState(controller->fsm, STATE_ADVENTURE, 0, 0); }
                    else if (strcmp(input, "2") == 0)   { fsm_updateState(controller->fsm, STATE_POKEMON, 0, 0); }
                    else if (strcmp(input, "b") == 0)   { fsm_updateState(controller->fsm, STATE_HOME, 0, 0); }
                    else { fsm_updateState(controller->fsm, STATE_ADVENTURE, currentSubState, 1); }
                    break;
                case 2:
                    /* Nothing encountered */
                    if (strcmp(input, "1") == 0)        { fsm_updateState(controller->fsm, STATE_ADVENTURE, 1, 0); }
                    else if (strcmp(input, "b") == 0)   { fsm_updateState(controller->fsm, STATE_HOME, 0, 0); }
                    else { fsm_updateState(controller->fsm, STATE_ADVENTURE, currentSubState, 1); }
                    break;
                default:
                    fsm_updateState(controller->fsm, STATE_HOME, 0, 4);
            }
        case STATE_POKEDEX:
            if (strcmp(input, "a") == 0)        { fsm_updateState(controller->fsm, STATE_POKEDEX, 0, 0); }
            else if (strcmp(input, "d") == 0)   { fsm_updateState(controller->fsm, STATE_POKEDEX, 0, 0); }
            else if (strcmp(input, "1") == 0)   { fsm_updateState(controller->fsm, STATE_POKEDEX, 0, 0); }
            else if (strcmp(input, "b") == 0)   { fsm_updateState(controller->fsm, STATE_HOME, 0, 0); }
            else { fsm_updateState(controller->fsm, STATE_POKEDEX, currentSubState, 1); }
            break;
        case STATE_POKEMON:
            if (strcmp(input, "1") == 0)        { fsm_updateState(controller->fsm, STATE_POKEMON, 0, 0); }
            else if (strcmp(input, "b") == 0)   { fsm_updateState(controller->fsm, STATE_POKEDEX, 0, 0); }
            else { fsm_updateState(controller->fsm, STATE_POKEMON, currentState, 1); }
            break;
        default:
            fsm_updateState(controller->fsm, STATE_HOME, 0, 4);
    }

    page = controller_getPage(controller);
    view_displayPage(page);
    page_free(page);
}

