#include <stdio.h>
#include <stdlib.h>
#include "homePage.h"
#include "../util/page.h"
#include <string.h>

/*
create blocks
create page
return page
*/
Page *create_home_page(void) {
    RenderedBlock *actionMenu;
    Page *homePage; 

    DisplayStrings actionMenuText = {
        "Home Page\n",
        "┌───────────────────────────┐\n",
        "│ ACTION_1: View Pokédex    │\n",
        "│ ACTION_2: Adventure       │\n",
        "│ ACTION_3: Save & Exit     │\n",
        "└───────────────────────────┘\n"
    };
    actionMenu = create_rendered_block(6, SCREEN_LENGTH, actionMenuText);
    if (!actionMenu) return NULL;

    homePage = create_page("home", 1, actionMenu);
    if (!homePage) return NULL;

    return homePage;
}


/*
render page
read user input inside while loop
exit program with code to switch to different page
*/
int render_home_page(void) {
    /*char input[50];*/

    Page *homePage; 
    homePage = create_home_page();
    if (!homePage) return 1;

    render_page(homePage);
    free_page(homePage);
    return 0;
}
