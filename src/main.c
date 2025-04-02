#include <stdio.h>
#include <stdlib.h>

#include "util/pokedex.h"
#include "util/db.h"

Pokedex pokedex;
const char *savefile = "data/pokedex.dat";
char input;
int running;

typedef enum {
    MENU,
    POKEDEX,
    ADVENTURE,
    SAVE
} PageState;

typedef struct {
    PageState currentState;
} Page;

void clear_screen()
{
    #ifdef _WIN32
    #define CLEAR "cls"
    #else /* In any other OS */
    #define CLEAR "clear"
    #endif
    system(CLEAR);
}

void update_state(Page *page, char input)
{
    PageState prevState = page->currentState;
	if (input == '0') {page->currentState = MENU;}
    else if (input == '1') {page->currentState = POKEDEX;}
    else if (input == '2') {page->currentState = ADVENTURE;}
    else if (input == '3') {page->currentState = SAVE;}
    else {printf("Invalid Choice, Try Again...\n");}
}

void print_options(PageState state)
{
    if(state == MENU)
    {
        printf("_____________________\n");
        printf("| Menu Options:     |\n");
        printf("| 1. View Pokedex   |\n");
        printf("| 2. Adventure      |\n");
        printf("| 3. Save & Exit    |\n");
        printf("|___________________|\n\n");
    }
    else if(state == POKEDEX)
    {
        printf("_____________________________\n");
        printf("| Pokedex Options:          |\n");
        printf("| 1. Previous Page          |\n");
        printf("| 2. Next Page              |\n");
        printf("| 3. Back to Menu           |\n");
        printf("| XXX. Access Pokemon #XXX  |\n");
        printf("|___________________________|\n\n");
    }
    else if(state == ADVENTURE)
    {
        printf("_________________________\n");
        printf("| Adventure Options:    |\n");
        printf("| 1. Start Adventure    |\n");
        printf("| 2. Back to Menu       |\n");
        printf("|_______________________|\n\n");
    }
}

/* Main function: entry point for execution */
int main(int argc, char ** argv)
{
    Page page = {MENU};
    running = 1;
    loadPokedex(&pokedex, savefile);
    printf("Pokedex Loaded.\n");

    while(running)
    {
        print_options(page.currentState);
        printf("Enter Choice: ");
        scanf(" %c", &input);
        printf("You picked %c\n\n", input);
        update_state(&page, input);

        clear_screen();
        switch (page.currentState) {
            case MENU:
                printf("Menu:\n");
                break;
            case POKEDEX:
                printf("Pokedex:\n");
                printPokedex(&pokedex);
                break;
            case ADVENTURE:
                printf("Adventure:\n");
                break;
            case SAVE:
                printf("Saving...\n");
                savePokedex(&pokedex, savefile);
                printf("Pokedex Saved.\n");
                running = 0;
                break;
            default:
                printf("404 Page Not Found.\n");
                break;
        }
    }
    return 0;
}

