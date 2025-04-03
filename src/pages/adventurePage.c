#include "adventurePage.h"
#include "homePage.h"
#include "pokedexPage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void initialize_adv_page_data(InputState *inputState) {
    inputState->errorState = 0;
    inputState->appState = STATE_ADVENTURE;
    inputState->stateAppState = SHOW_ADVPAGE;
    inputState->parserFunction = adv_page_parser;
}

/* ADV PAGE */
void adv_page_parser(InputState *inputState, char *input) {
    if (strcmp(input, "1") == 0) {
        /* 70% chance of encountering pokemon, 30% chance of encountering nothing */
        int chance;
        srand(time(NULL));
        chance = rand() % 100;
        if (chance < 70) {
            update_input_state(inputState, 0, SHOW_POKEMON_ENCOUNTERED, STATE_ADVENTURE, 0);
        } else {
            update_input_state(inputState, 0, SHOW_NOTHING_ENCOUNTERED, STATE_ADVENTURE, 0);
        }
        
    } else if (strcmp(input, "2") == 0) {
        update_input_state(inputState, 0, EXIT_ADVPAGE, STATE_HOME, SHOW_HOMEPAGE);    
    } else {
        /** This means invalid input, and appropriate error message should be shown */
        update_input_state(inputState, 1, SHOW_ADVPAGE, STATE_ADVENTURE, 0);
    }
}

Page *create_adv_page(void) {
    RenderedBlocks *advPageBlocks;
    Page *advPage; 
    DisplayStrings blockZeroText = {"Adventure\n"};
    DisplayStrings blockOneText = {"Something's moving in the grass!\n"};
    DisplayStrings blockTwoText = {
        "┌────────────────────┐\n",
        "│ 1: Check it out    │\n",
        "│ 2: Back to menu    │\n",
        "└────────────────────┘\n"
    };

    advPageBlocks = create_blocks(3);
    if (!advPageBlocks) return NULL;

    /** advPageTitle will be rendered starting from 0th to 5th row (height == 6). */
    add_block_to_blocks(advPageBlocks, 0, 0, 6, SCREEN_LENGTH, blockZeroText);
    /** this means that blockOneText will be rendered starting from 6th row to 7th row (height == 2) */
    add_block_to_blocks(advPageBlocks, 1, 6, 1, SCREEN_LENGTH, blockOneText);
    add_block_to_blocks(advPageBlocks, 2, 7, 4, SCREEN_LENGTH, blockTwoText);

    advPage = create_page("adv", advPageBlocks);
    if (!advPage) {
        free_blocks(advPageBlocks);
        return NULL;
    }

    return advPage;
}


/* ENCOUNTER POKEMON */
void pokemon_encountered_page_parser(InputState *inputState, char *input) {
    if (strcmp(input, "1") == 0) {
        update_input_state(inputState, 0, SHOW_ADVPAGE, STATE_ADVENTURE, 0);    
    } else if (strcmp(input, "2") == 0) {
        /* This should lead to view pokemon page*/
        update_input_state(inputState, 0, SHOW_POKEDEXLIST, STATE_POKEDEX, 0);   
    } else if (strcmp(input, "3") == 0) {
        update_input_state(inputState, 0, EXIT_ADVPAGE, STATE_HOME, SHOW_HOMEPAGE);
    } else {
        /* This means invalid input, and appropriate error message should be shown */
        update_input_state(inputState, 1, SHOW_POKEMON_ENCOUNTERED, STATE_ADVENTURE, 0);
    }
}


/* ENCOUNTER NOTHING */
void nothing_encountered_page_parser(InputState *inputState, char *input) {
    if (strcmp(input, "1") == 0) {
        update_input_state(inputState, 0, SHOW_ADVPAGE, STATE_ADVENTURE, 0);
    } else if (strcmp(input, "2") == 0) {
        update_input_state(inputState, 0, EXIT_ADVPAGE, STATE_HOME, SHOW_HOMEPAGE);
    } else {
        /** This means invalid input, and appropriate error message should be shown */
        update_input_state(inputState, 1, SHOW_NOTHING_ENCOUNTERED, STATE_ADVENTURE, 0);
    }
}


/*
Process flow on any appState (how adv_page works)
1) enter starting state
2) at each state, function will create, then render page. then wait for human input.
3) function processes human input to determine next state
4) right before exiting current appState, function should indicate which appState (+sub-state)
    to go to next.
    
run_appState function
    (-b) initialise inputState, which represents how your appState_fsm/parser can interact with your
            appState_fsm/main_fsm/ error message. 
    (-a) set the starting sub-state of the current page.
    (a) enter appState_fsm.
    (b) for each state in appState_fsm, you will: 
        - create display page for that state, render it. (page will be freed in render function)
        - process inputs using sub-state specific parser function
        - use update_input_state() to indicate what the next sub-state is. 
    (c) if appState_fsm moves to a state that requires it to exit current appState, make sure function
        calls update_app_state_struct() to update the state of main fsm before exiting, so main fsm knows where to go next.
    */


void run_adv_page(AppStateStruct *appStateStruct) {
    Page *advPage;
    InputState inputState;
    AdvPageState advPageState;
    DisplayStrings cutSceneText1 = {
        "Let's go explore\n", 
        "and hopefully encounter\n",
        "some new Pokemon!\n"};
    DisplayStrings cutSceneText2 = {"Exploring...\n"};

    initialize_adv_page_data(&inputState);
    /**
     * Here we are copying the starting state of homePage fsm by using
     * nextStateNextAppState, not assigning them to the same address.
     */
    advPageState = (AdvPageState) appStateStruct->nextStateNextAppState;

    while (advPageState != EXIT_ADVPAGE) {
        switch(advPageState) {
            case SHOW_ADVPAGE:
                advPage = create_adv_page();
                if (!advPage) {
                    advPageState = EXIT_ADVPAGE;
                    update_app_state_struct(appStateStruct, STATE_SAVE, 0); /** Called this because function is leaving homePage */
                    break;
                }
                render_adv_cutscene(cutSceneText1, 3);
                render_adv_cutscene(cutSceneText2, 1);

                render_page(advPage);
                get_user_input(&inputState, EXIT_ADVPAGE);
                advPageState = inputState.stateAppState;
                update_app_state_struct(appStateStruct, inputState.appState, inputState.nextStateNextAppState); /** Called this because function is leaving homePage */
                break;
            case SHOW_POKEMON_ENCOUNTERED:
            case SHOW_NOTHING_ENCOUNTERED:
            case EXIT_ADVPAGE:
                break;
        }
    }
}

