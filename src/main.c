#include <stdio.h>
#include <stdlib.h>

#include "util/pokedex.h"
#include "util/db.h"

Pokedex pokedex;
const char *savefile = "data/pokedex.dat";
#define POKEMON_ROW 10
#define POKEMON_PER_PAGE 20

typedef enum {
    MENU,
    POKEDEX,
    ADVENTURE,
    SAVE
} PageState;

typedef struct {
    PageState currentState;
    int pokedexPage;
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

typedef struct {
    PageState currentState;
    const char *options[6];
    int num_options;
    int buffer;
} PageOptions;

PageOptions pageOptions[] = {
    {MENU, 
        {"1. View Pokedex", "2. Adventure", "3. Save & Exit"},
        3, 15},
    {POKEDEX, 
        {"1. Previous Page", "2. Next Page", "3. Adventure", "4. Back to Menu", "5. Save & Exit", "XXX. Access Pokemon #XXX"},
        6, 25},
    {ADVENTURE, 
        {"1. Start Adventure", "2. Back to Menu", "3. Save & Exit"},
        3, 20}
};

void print_options(PageState state)
{
    int i, j;
    for (i = 0; i < 3; i++){
        if (pageOptions[i].currentState == state){
            for (j = 0; j < pageOptions[i].buffer+4; j++)
            {
                printf("_");
            }
            printf("\n");
            for (j = 0; j < pageOptions[i].num_options; j++)
            {
                printf("| %-*s |\n", pageOptions[i].buffer, pageOptions[i].options[j]);
            }
            printf("|");
            for (j = 0; j < pageOptions[i].buffer+2; j++)
            {
                printf("_");
            }
            printf("|\n\n");
        }
    }
}

void printPokedexPage(Pokedex *pokedex, int page) {
    int pokemonPerRow, pokemonPerPage;
    int startIdx, leftIdx, rightIdx, i;

    pokemonPerRow = 10;
    pokemonPerPage = pokemonPerRow * 2;
    startIdx = page * pokemonPerPage;
    
    printf("_______________________________________\n");

    for (i = 0; i < pokemonPerRow; i++) {  
        leftIdx = startIdx + i;
        rightIdx = startIdx + i + pokemonPerRow;

        if (leftIdx < pokedex->size) {
            printf("| %03d %-12s ", 
                pokedex->pokedexList[leftIdx].id, 
                pokedex->pokedexList[leftIdx].seen ? pokedex->pokedexList[leftIdx].name : "----------");
        } else {
            printf("|                  "); 
        }

        if (rightIdx < pokedex->size) {
            printf("| %03d %-12s |\n", 
                pokedex->pokedexList[rightIdx].id, 
                pokedex->pokedexList[rightIdx].seen ? pokedex->pokedexList[rightIdx].name : "----------");
        } else {
            printf("|                  |\n");
        }
    }

    printf("|__________________|__________________|\n");
    printf("Page %d/%d\n\n", page + 1, (pokedex->size + pokemonPerPage - 1) / pokemonPerPage);
}

void update_page_state(Page *page, char input)
{
    PageState prevState = page->currentState;
	if (input == '1') 
    {page->currentState = (prevState == MENU)? POKEDEX : prevState;}
    else if (input == '2') 
    {page->currentState = (prevState == MENU)? ADVENTURE : 
                            (prevState == ADVENTURE)? MENU : prevState;}
    else if (input == '3') 
    {page->currentState = (prevState == MENU)? SAVE :
                            (prevState == POKEDEX)? ADVENTURE : 
                            (prevState == ADVENTURE)? SAVE : prevState;}
    else if (input == '4') 
    {page->currentState = (prevState == POKEDEX)? MENU : prevState;}
    else if (input == '5') 
    {page->currentState = (prevState == POKEDEX)? SAVE : prevState;}

    clear_screen();
        switch (page->currentState) {
            case MENU:
                printf("Menu:\n");
                break;
            case POKEDEX:
                printf("Pokedex:\n");
                if (input == '1' && page->pokedexPage > 0) {page->pokedexPage--;}
                else if (input == '2' && (page->pokedexPage + 1) * POKEMON_PER_PAGE < pokedex.size) {page->pokedexPage++;}
                printPokedexPage(&pokedex, page->pokedexPage);
                break;
            case ADVENTURE:
                printf("Adventure:\n");
                break;
            case SAVE:
                printf("Saving...\n");
                savePokedex(&pokedex, savefile);
                printf("Pokedex Saved.\n");
                exit(0);
                break;
            default:
                printf("404 Page Not Found.\n");
                break;
        }
}

/* Main function: entry point for execution */
int main(int argc, char ** argv)
{
    char input;

    Page page = {MENU, 0};
    loadPokedex(&pokedex, savefile);
    printf("Pokedex Loaded.\n");

    while(1)
    {
        print_options(page.currentState);
        printf("Enter Choice: ");
        scanf(" %c", &input);
        printf("You picked %c\n\n", input);
        update_page_state(&page, input);
    }
    return 0;
}

