#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#include "util/pokedex.h"
#include "util/db.h"
#include "util/page.h"

Pokedex pokedex;
const char *loadfile = "data/pokedex.dat";

/* Main function: entry point for execution */
int main(int argc, char ** argv)
{
    char input[65];

    /* Initial Page when entering the game */
    Page page = {MENU, 0};
    /* Tries to load the Pokedex data first */
    if (loadPokedex(&pokedex, loadfile)==0) {
        printf("Pokedex Loaded.\n");
    }
    else {
        printf("Unable to load Pokedex. Try again!!\n");
        return 0;
    }
    /* Load the Initial Page */
    clearScreen();
    printMenuPage();
    pokedex.pokedexList->seen=1;

    /* Game starts, prints options available, wait for user input, handle page accordingly */
    while(1)
    {
        printOptions(page.currentState);
        printf("Enter Choice: ");
        scanf(" %64s", input);
        printf("You picked %s\n\n", input);
        updatePageState(&page, &pokedex, input);
    }
    return 0;
}

