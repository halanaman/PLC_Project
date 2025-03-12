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
4) right before exiting current appState, function should indicate which appState
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
    (-a) initialise inputState, which represents how your appState_fsm/parser can interact with your
            appState_fsm/main_fsm/ error message
    (a) enter appState_fsm, which should accept the state of main fsm as input
    (b) for each state in appState_fsm, you will: 
        - create display page for that state, render it. (page will be freed in render function)
        - look for input to move into the next state
    (c) if appState_fsm moves to a state that requires it to exit current appState, make sure function
        updates the state of main fsm before exiting, so main fsm knows which state to go next.
*/

void homePageMenuParser(InputState *inputState, char *input) {
    if (strcmp(input, "1") == 0) {
        updateInputState(inputState, 0, 1, 1);
    } else if (strcmp(input, "2") == 0) {
        updateInputState(inputState, 0, 1, 2);
    } else if (strcmp(input, "3") == 0) {
        updateInputState(inputState, 0, 1, 3);
    } else {
        updateInputState(inputState, 1, 0, 0);
    }
}

Page *create_home_page(void) {
    RenderedBlocks *homePageBlocks;
    Page *homePage; 
    DisplayStrings blockZeroText = {
        "Home Page\n",
        "┌───────────────────────────┐\n",
        "│ ACTION_1: View Pokédex    │\n",
        "│ ACTION_2: Adventure       │\n",
        "│ ACTION_3: Save & Exit     │\n",
        "└───────────────────────────┘\n"
    };
    homePageBlocks = create_blocks(1);
    if (!homePageBlocks) return NULL;

    add_block_to_blocks(0, homePageBlocks, 0, 6, SCREEN_LENGTH, blockZeroText);

    homePage = create_page("home", homePageBlocks);
    if (!homePage) {
        free_blocks(homePageBlocks);
        return NULL;
    }

    return homePage;
}

void run_home_page(AppState *currentAppState) {
    Page *homePage;
    InputState inputState = {
        .errorState = 0,
        .inputSize = 1,
        .appState = 0,
        .stateAppState = 0,
        .parserFunction = &homePageMenuParser,
        .previousInput = ""
    };

    HomePageState homePageState = ENTER_HOMEPAGE;

    while (homePageState != LEAVE_HOMEPAGE) {
        switch(homePageState) {
            case ENTER_HOMEPAGE:
                homePage = create_home_page();
                if (!homePage) {
                    homePageState = LEAVE_HOMEPAGE;
                    *currentAppState = STATE_SAVE;
                    break;
                }
                render_page(homePage);
                get_user_input(&inputState);
                homePageState = inputState.stateAppState;
                *currentAppState = inputState.appState;   
                break;
            case LEAVE_HOMEPAGE:
                break;
        }
    }
}
