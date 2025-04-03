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

    Page page = {MENU, 0};
    loadPokedex(&pokedex, loadfile);
    printf("Pokedex Loaded.\n");
    update_page_state(&page, &pokedex, "0");

    while(1)
    {
        print_options(page.currentState);
        printf("Enter Choice: ");
        scanf(" %64s", input);
        printf("You picked %s\n\n", input);
        update_page_state(&page, &pokedex, input);
    }
    return 0;
}

