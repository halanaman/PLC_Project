#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <time.h>

#include "page.h"
#include "pokedex.h"
#include "db.h"
#include "text.h"

const char *savefile = "data/pokedex.dat";

void clear_screen()
{
    #ifdef _WIN32
    #define CLEAR "cls"
    #else /* In any other OS */
    #define CLEAR "clear"
    #endif
    system(CLEAR);
}

PageOptions pageOptions[] = {
    {MENU, 
        {"1. View Pokedex", "2. Adventure", "3. Save & Exit"},
        3, 20},
    {POKEDEX, 
        {"1. Previous Page", "2. Next Page", "3. Adventure", "4. Back to Menu", "5. Save & Exit", "XXX. Access Pokemon #XXX"},
        6, 30},
    {CARDVIEW, 
        {"1. Save Pokemon Card", "2. Back to Pokedex"},
        2, 25},
    {ADVENTURE, 
        {"1. Start Adventure", "2. Back to Menu", "3. Save & Exit"},
        3, 25},
    {ADVENTURE_SUCCESS, 
        {"1. Adventure Again", "2. View Pokemon", "3. Back to Menu"},
        3, 25},
    {ADVENTURE_FAIL, 
        {"1. Adventure Again", "2. Back to Menu"},
        2, 25}
};

void print_options(PageState state)
{
    int i, j, num_page_options;
    num_page_options = sizeof(pageOptions)/sizeof(pageOptions[0]);
    for (i = 0; i < num_page_options; i++){
        if (pageOptions[i].currentState == state){
            for (j = 0; j < pageOptions[i].width; j++)
            {
                printf("_");
            }
            printf("\n");
            printLeftAlignedText("", pageOptions[i].width);
            for (j = 0; j < pageOptions[i].num_options; j++)
            {
                printLeftAlignedText(pageOptions[i].options[j], pageOptions[i].width);
            }
            printf("|");
            for (j = 0; j < pageOptions[i].width-2; j++)
            {
                printf("_");
            }
            printf("|\n\n");
        }
    }
}

void printMenuPage()
{   int width = 45;
    printBorder("top", width);
    printCenteredText("Welcome to the Pokedex Game!", width);
    printBorder("middle", width);
    printWrappedText("Gotta catch 'em all! Start your journey to discover and learn about different Pokemon!", width);
    printBorder("bottom", width);
}

void printPokedexPage(Pokedex *pokedex, int page) {
    int startIdx, leftIdx, rightIdx, i;

    startIdx = page * POKEMON_PER_PAGE;
    
    printf("_______________________________________\n");

    for (i = 0; i < POKEMON_ROW; i++) {  
        leftIdx = startIdx + i;
        rightIdx = startIdx + i + POKEMON_ROW;

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
    printf("Page %d/%d\n\n", page + 1, (pokedex->size + POKEMON_PER_PAGE - 1) / POKEMON_PER_PAGE);
}

void printCardViewPage(Pokemon *pokemon, PokedexListItem *pokemonSeen) {
    int width = 99;  
    char buffer[50];
    
    if (pokemonSeen->seen) {
        printBorder("top", width);
        printCenteredText(pokemon->name, width);
        sprintf(buffer, "%s | HP: %d", pokemon->type, pokemon->hp);
        printCenteredText(buffer, width);
        printBorder("middle", width);
        printPokemonAscii(pokemon->name, width);
        printBorder("middle", width);
        sprintf(buffer, "ATK: %-3d | DEF: %-3d | SPD: %-3d | ACC: %-3d%%", 
                pokemon->atk, pokemon->def, pokemon->spd, pokemon->acc);
        printCenteredText(buffer, width);
        printBorder("middle", width);
        printWrappedText(pokemon->desc, width);
        printBorder("bottom", width);
    }
    else {
        printBorder("top", width);
        sprintf(buffer, "%03d Pokemon Name", pokemon->id);
        printCenteredText(buffer, width);
        printCenteredText("Type | HP: --", width);
        printBorder("middle", width);
        printCenteredText("Pokemon Not Found", width);
        printBorder("middle", width);
        printCenteredText("ATK: --- | DEF: --- | SPD: --- | ACC: ---%%", width);
        printBorder("middle", width);
        printCenteredText("Description", width);
        printBorder("bottom", width);
    }
}

void printAdventurePage(Page *page, Pokedex *pokedex) {
    char buffer[100], pokemonName[20];
    int width = 40;
    strcpy(pokemonName, pokedex->pokedexList[page->cardViewIdx].name);

    printBorder("top", width);
    if (page->currentState == ADVENTURE) {
        printWrappedText("Hello Trainer, are you ready to adventure?", width);
        printBorder("space", width);
        printCenteredText("Let's go!", width);
    }
    else if (page->currentState == ADVENTURE_SUCCESS) {
        printPokemonAscii(pokemonName, width);
        printBorder("middle", width);
        sprintf(buffer, "Wild %s appeared ", pokemonName);
        printWrappedText(buffer, width);
    }
    else if (page->currentState == ADVENTURE_FAIL) {
        printWrappedText("No luck today! You did not see any Pokemon.", width);
    }
    printBorder("bottom", width);
}

void update_page_state(Page *page, Pokedex *pokedex, char *input)
{
    PageState prevState;
    /* Uses regex to capture sigle digit and 3-digit inputs */
    char pattern1[8], pattern2[11];
    regex_t regex, regex2;
    int status1, status2;
    strcpy(pattern1, "^[0-9]$");
    strcpy(pattern2, "^[0-9]{3}$");
    printf("%s\n", input);
    status1 = regcomp(&regex, pattern1, REG_EXTENDED);
    status2 = regcomp(&regex2, pattern2, REG_EXTENDED);
    printf("%d, %d\n", status1, status2);
    status1 = regexec(&regex, input, 0, NULL, 0);
    status2 = regexec(&regex2, input, 0, NULL, 0);
    printf("%d, %d\n", status1, status2);
    /* random seed, used for adveture page */
    srand(time(NULL));
    
    prevState = page->currentState;
    /* Single digit input, handle PageState changes */
    if (status1 == 0)
    {
        if (strcmp(input,"1")==0)
        {page->currentState = (prevState == MENU)? POKEDEX : 
                                (prevState == CARDVIEW)? POKEDEX : 
                                (prevState == ADVENTURE_SUCCESS)? ADVENTURE :
                                (prevState == ADVENTURE_FAIL)? ADVENTURE : prevState;
            
            if (prevState == ADVENTURE) {
                if ( (rand() % 10) < 7) {
                    int id = rand() % pokedex->size;
                    page->cardViewIdx = id;
                    pokedex->pokedexList[id].seen = 1;
                    page->currentState = ADVENTURE_SUCCESS;
                }
                else {
                    page->currentState = ADVENTURE_FAIL;
                }
            }
        }
        else if (strcmp(input,"2")==0)
        {page->currentState = (prevState == MENU)? ADVENTURE : 
                                (prevState == CARDVIEW)? POKEDEX :
                                (prevState == ADVENTURE)? MENU : 
                                (prevState == ADVENTURE_SUCCESS)? CARDVIEW : 
                                (prevState == ADVENTURE_FAIL)? MENU : prevState;}
        else if (strcmp(input,"3")==0)
        {page->currentState = (prevState == MENU)? SAVE :
                                (prevState == POKEDEX)? ADVENTURE : 
                                (prevState == ADVENTURE)? SAVE : 
                                (prevState == ADVENTURE_SUCCESS)? MENU : prevState;}
        else if (strcmp(input,"4")==0)
        {page->currentState = (prevState == POKEDEX)? MENU : prevState;}
        else if (strcmp(input,"5")==0)
        {page->currentState = (prevState == POKEDEX)? SAVE : prevState;}
    }
    /* 3-digit input, handles CardView Page if valid */
    else if (status2 == 0 && page->currentState == POKEDEX)
    {
        int i = atoi(input) - 1, start, end;
        start = page->pokedexPage * POKEMON_PER_PAGE;
        end = start + POKEMON_PER_PAGE - 1;
        if (i >= start && i <= end) {
            page->cardViewIdx = atoi(input) - 1;
            page->currentState = CARDVIEW;
        }
    }

    /* clear screen and display Page */
    clear_screen();
    switch (page->currentState) {
        case MENU:
            printf("Menu:\n");
            printMenuPage();
            break;
        case POKEDEX:
            printf("Pokedex:\n");
            if (prevState == POKEDEX) {
                if ((strcmp(input,"1")==0) && page->pokedexPage > 0) {page->pokedexPage--;}
                else if ((strcmp(input,"2")==0) && (page->pokedexPage + 1) * POKEMON_PER_PAGE < pokedex->size) {page->pokedexPage++;}
            }
            printPokedexPage(pokedex, page->pokedexPage);
            if (status2 == 0) {printf("Invalid Input, Please Choose from Pokemons displayed\n");}
            break;
        case CARDVIEW:
            printf("CardView:\n");
            printCardViewPage(&pokedex->pokemonList[page->cardViewIdx], &pokedex->pokedexList[page->cardViewIdx]);
            break;
        case ADVENTURE:
            printf("Adventure:\n");
            printAdventurePage(page, pokedex);
            break;
        case ADVENTURE_SUCCESS:
            printf("Adventure Success:\n");
            printAdventurePage(page, pokedex);
            break;
        case ADVENTURE_FAIL:
            printf("Adventure Fail:\n");
            printAdventurePage(page, pokedex);
            break;
        case SAVE:
            printf("Saving...\n");
            if (savePokedex(pokedex, savefile)==0) {
                printf("Pokedex Saved.\n");
                exit(0);
            }
            else {
                printf("Unable to save your progress. Try again!!\n");
                page->currentState = MENU;
            }
            break;
        default:
            printf("404 Page Not Found.\n");
            break;
    }
}





