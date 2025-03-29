#include "homePage.h"
#include "../util/page.h"
#include "../util/constants.h"
#include "../fsm.h"
#include "../util/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Process flow on any appState (how run_home_page works)
1) enter starting state
2) at each state, function will create, then render page. then wait for human input.
3) function processes human input to determine next state
4) right before exiting current appState, function should indicate which appState (+sub-state)
    to go to next.

work flow of creating all pages in any appState
1) for every display page in the appState, you should have a separate function,
    like create_page_1(), create_page_2(). The return value of the create page function 
    should be a pointer to a page in the heap, so that run_appState function can pass
    that pointer into render_page function.
2) within each create_page function, you will: 
    (a) create blocks
        - create all block text first
        - create blocks with input of block size (to allocate memory of correct size)
        - fill up every index of blocks with info on every block
    (b) create entire page, then return the pointer to the page itself. 
3) write a parser function that can help process inputs into meaningful results, so you can update
    your inputState object to help determine next step for the fsms.
4) write the run_appState function
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

void initialize_home_page_data(InputState *inputState) {
    inputState->errorState = 0;
    inputState->appState = STATE_HOME;
    inputState->stateAppState = SHOW_HOMEPAGE;
    inputState->parserFunction = &home_page_menu_parser;
}

void home_page_menu_parser(InputState *inputState, char *input) {
    if (strcmp(input, "1") == 0) {
        update_input_state(inputState, 0, EXIT_HOMEPAGE, STATE_POKEDEX, 0);
    } else if (strcmp(input, "2") == 0) {
        update_input_state(inputState, 0, EXIT_HOMEPAGE, STATE_ADVENTURE, 0);
    } else if (strcmp(input, "3") == 0) {
        update_input_state(inputState, 0, EXIT_HOMEPAGE, STATE_SAVE, 0);
    } else {
        /** This means invalid input, and appropriate error message should be shown */
        update_input_state(inputState, 1, SHOW_HOMEPAGE, STATE_HOME, 0);
    }
}

Page *create_home_page(void) {
    RenderedBlocks *homePageBlocks;
    Page *homePage; 
    DisplayStrings blockZeroText = {
        "Home Page\n",
        "┌───────────────────────────┐\n",
        "│ 1: View Pokédex           │\n",
        "│ 2: Adventure              │\n",
        "│ 3: Save & Exit            │\n",
        "└───────────────────────────┘\n"
    };
    /**
    DisplayStrings blockOneText = {
        "this is the second block\n",
        "this is second row of second block\n"
    };
    */

    homePageBlocks = create_blocks(1);
    if (!homePageBlocks) return NULL;

    /** blockZeroText will be rendered starting from 0th to 5th row (height == 6). */
    add_block_to_blocks(homePageBlocks, 0, 0, 6, SCREEN_LENGTH, blockZeroText);
    /** this means that blockOneText will be rendered starting from 6th row to 7th row (height == 2) */
    /** add_block_to_blocks(homePageBlocks, 1, 6, 2, SCREEN_LENGTH, blockOneText); */

    homePage = create_page("home", homePageBlocks);
    if (!homePage) {
        free_blocks(homePageBlocks);
        return NULL;
    }

    return homePage;
}

void run_home_page(AppStateStruct *appStateStruct) {
    Page *homePage;
    InputState inputState;
    HomePageState homePageState;

    initialize_home_page_data(&inputState);
    /**
     * Here we are copying the starting state of homePage fsm by using
     * nextStateNextAppState, not assigning them to the same address.
     */
    homePageState = (HomePageState) appStateStruct->nextStateNextAppState;

    while (homePageState != EXIT_HOMEPAGE) {
        switch(homePageState) {
            case SHOW_HOMEPAGE:
                homePage = create_home_page();
                if (!homePage) {
                    homePageState = EXIT_HOMEPAGE;
                    update_app_state_struct(appStateStruct, STATE_SAVE, 0); /** Called this because function is leaving homePage */
                    break;
                }
                render_page(homePage);
                get_user_input(&inputState, EXIT_HOMEPAGE);
                homePageState = inputState.stateAppState;
                update_app_state_struct(appStateStruct, inputState.appState, inputState.nextStateNextAppState); /** Called this because function is leaving homePage */
                break;
            case EXIT_HOMEPAGE:
                break;
        }
    }
}
