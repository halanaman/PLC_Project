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

void clearScreen() {
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

void printOptions(PageState state) {
    int i, j, numPageOptions;
    numPageOptions = sizeof(pageOptions)/sizeof(pageOptions[0]);

    for (i = 0; i < numPageOptions; i++){
        if (pageOptions[i].currentState == state){
            printBorder("top", pageOptions[i].width);
            printBorder("space", pageOptions[i].width);
            for (j = 0; j < pageOptions[i].numOptions; j++)
            {
                printLeftAlignedText(pageOptions[i].options[j], pageOptions[i].width);
            }
            printBorder("bottom", pageOptions[i].width);
            break;
        }
    }
}

void printMenuPage() {   
    printf("Menu:\n");
    printBorder("top", PAGE_WIDTH);
    printCenteredText("Welcome to the Pokedex Game!", PAGE_WIDTH);
    printBorder("middle", PAGE_WIDTH);
    printWrappedText("Gotta catch 'em all! Start your journey to discover and learn about different Pokemon!", PAGE_WIDTH);
    printBorder("bottom", PAGE_WIDTH);
}

void printPokedexPage(Pokedex *pokedex, int page) {
    int startIdx, leftIdx, rightIdx, i;

    startIdx = page * POKEMON_PER_PAGE;
    
    printf("Pokedex:\n");
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
    char buffer[100];
    
    printf("CardView:\n");

    printBorder("top", CARD_WIDTH);

    pokemonSeen->seen? sprintf(buffer, "%s", pokemon->name) : 
                        sprintf(buffer, "%03d Pokemon Name", pokemon->id);
    printCenteredText(buffer, CARD_WIDTH);

    pokemonSeen->seen? sprintf(buffer, "%s | HP: %d", pokemon->type, pokemon->hp) : 
                        sprintf(buffer, "Type | HP: --");
    printCenteredText(buffer, CARD_WIDTH);

    printBorder("middle", CARD_WIDTH);

    pokemonSeen->seen? printPokemonAscii(pokemon->name, CARD_WIDTH) : 
                        printCenteredText("Pokemon Not Found", CARD_WIDTH);

    printBorder("middle", CARD_WIDTH);

    pokemonSeen->seen? sprintf(buffer, "ATK: %-3d | DEF: %-3d | SPD: %-3d | ACC: %-3d%%", 
                                pokemon->atk, pokemon->def, pokemon->spd, pokemon->acc) : 
                        sprintf(buffer, "ATK: --- | DEF: --- | SPD: --- | ACC: ---%%");
    printCenteredText(buffer, CARD_WIDTH);

    printBorder("middle", CARD_WIDTH);

    pokemonSeen->seen? printWrappedText(pokemon->desc, CARD_WIDTH) : 
                        printCenteredText("Description", CARD_WIDTH);

    printBorder("bottom", CARD_WIDTH);
}

void saveCardViewPage(FILE *out, Pokemon *pokemon) {
    char buffer[100];
    
    printBorderToFile(out, "top", CARD_WIDTH);

    printCenteredTextToFile(out, pokemon->name, CARD_WIDTH);

    sprintf(buffer, "%s | HP: %d", pokemon->type, pokemon->hp);
    printCenteredTextToFile(out, buffer, CARD_WIDTH);

    printBorderToFile(out, "middle", CARD_WIDTH);

    printPokemonAsciiToFile(out, pokemon->name, CARD_WIDTH);

    printBorderToFile(out, "middle", CARD_WIDTH);

    sprintf(buffer, "ATK: %-3d | DEF: %-3d | SPD: %-3d | ACC: %-3d%%", 
            pokemon->atk, pokemon->def, pokemon->spd, pokemon->acc);
    printCenteredTextToFile(out, buffer, CARD_WIDTH);

    printBorderToFile(out, "middle", CARD_WIDTH);

    printWrappedTextToFile(out, pokemon->desc, CARD_WIDTH);

    printBorderToFile(out, "bottom", CARD_WIDTH);
}

const char *successMsg[] = {
    "You hear rustling nearby... something's definitely out there.",
    "Footprints! Something's been here recently.",
    "Your PokeRadar starts beeping wildly!",
    "The grass starts shaking... get ready!",
    "You feel the air shift. Something approaches.",
    "You hear a distant cry. A Pokemon is near!",
    "The wind carries a strange scent... could it be?",
    "You spot movement in the corner of your eye.",
    "Something glints in the distance—eyes watching?",
    "You kneel and spot fresh claw marks in the soil."
};

const char *failMsg[] = {
    "You search the tall grass... and trip over a banana peel. No Pokemon today.",
    "All you found was a PokeDoll with a creepy smile. It stares back.",
    "You hear rustling... but it's just the wind and your hopes leaving.",
    "You stepped into a puddle. That's it. Just a puddle.",
    "You uncovered a rare item! Oh wait... it's a rock. Just a regular rock.",
    "You spot a shadow in the distance... but it turns out to be your own.",
    "The path is quiet. Too quiet. Not a single Pokemon in sight.",
    "You feel like something is watching you. But it never shows itself.",
    "A strange fog rolls in. When it clears... there's nothing but silence.",
    "You reach into the bushes and pull out... a moldy sandwich.",
    "No Pokemon appeared... but you found some mysterious footprints.",
    "You didn't find one today, but something tells you you're close.",
    "Your PokeRadar beeps once... then goes silent. Next time?"
};

void printAdventurePage(Page *page, Pokedex *pokedex) {
    char buffer[100], pokemonName[20];
    int numSuccessMsg, numFailMsg;
    numSuccessMsg = sizeof(successMsg) / sizeof(successMsg[0]);
    numFailMsg = sizeof(failMsg) / sizeof(failMsg[0]);

    /* random seed, used for adveture page */
    srand(time(NULL));

    strcpy(pokemonName, pokedex->pokedexList[page->cardViewIdx].name);

    printf("Adventure:\n");
    printBorder("top", PAGE_WIDTH);
    if (page->currentState == ADVENTURE) {
        printWrappedText("Hello Trainer, are you ready to adventure?", PAGE_WIDTH);
        printBorder("space", PAGE_WIDTH);
        printCenteredText("Let's go!", PAGE_WIDTH);
    }
    else if (page->currentState == ADVENTURE_SUCCESS) {
        printWrappedText(successMsg[rand()%numSuccessMsg], PAGE_WIDTH);
        printBorder("bottom", PAGE_WIDTH);
        printBorder("top", PAGE_WIDTH);
        printPokemonAscii(pokemonName, PAGE_WIDTH);
        printBorder("middle", PAGE_WIDTH);
        sprintf(buffer, "A Wild %s appeared ", pokemonName);
        printWrappedText(buffer, PAGE_WIDTH);
    }
    else if (page->currentState == ADVENTURE_FAIL) {
        printWrappedText(failMsg[rand()%numFailMsg], PAGE_WIDTH);
    }
    printBorder("bottom", PAGE_WIDTH);
}

void updatePageState(Page *page, Pokedex *pokedex, char *input)
{
    PageState prevState;
    /* Uses regex to capture sigle digit and 3-digit inputs */
    char pattern1[8], pattern2[11];
    regex_t regex, regex2;
    int status1, status2;

    strcpy(pattern1, "^[0-9]$");
    strcpy(pattern2, "^[0-9]{3}$");
    
    printf("input: %s\n", input);
    status1 = regcomp(&regex, pattern1, REG_EXTENDED);
    status2 = regcomp(&regex2, pattern2, REG_EXTENDED);
    printf("status1: %d, status2: %d\n", status1, status2);

    status1 = regexec(&regex, input, 0, NULL, 0);
    status2 = regexec(&regex2, input, 0, NULL, 0);
    printf("status1: %d, status2: %d\n", status1, status2);

    /* random seed, used for adveture page */
    srand(time(NULL));
    
    prevState = page->currentState;
    /* Single digit input, handle PageState changes */
    if (status1 == 0)
    {
        if (strcmp(input,"1")==0)
        {page->currentState = (prevState == MENU)? POKEDEX : 
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
    clearScreen();
    switch (page->currentState) {
        case MENU:
            printMenuPage();
            break;
        case POKEDEX:
            if (prevState == POKEDEX) {
                if ((strcmp(input,"1")==0) && page->pokedexPage > 0) {page->pokedexPage--;}
                else if ((strcmp(input,"2")==0) && (page->pokedexPage + 1) * POKEMON_PER_PAGE < pokedex->size) {page->pokedexPage++;}
            }
            printPokedexPage(pokedex, page->pokedexPage);
            if (status2 == 0) {printf("Invalid Input, Please Choose from Pokemons displayed\n");}
            break;
        case CARDVIEW:
            printCardViewPage(&pokedex->pokemonList[page->cardViewIdx], &pokedex->pokedexList[page->cardViewIdx]);
            if ((strcmp(input,"1")==0) && pokedex->pokedexList[page->cardViewIdx].seen) {
                char filename[100];
                FILE *f;
                sprintf(filename, "user/output/%s.txt", pokedex->pokedexList[page->cardViewIdx].name);
                f = fopen(filename, "w");
                if (f) {
                    saveCardViewPage(f, &pokedex->pokemonList[page->cardViewIdx]);
                    fclose(f);
                    printf("Card saved to %s.\n", filename);
                }
                else {
                    printf("Failed to save card.\n");
                }
            }
            else if (pokedex->pokedexList[page->cardViewIdx].seen==0) {
                printf("Nothing to save here!\n");
            }
            break;
        case ADVENTURE:
            printAdventurePage(page, pokedex);
            break;
        case ADVENTURE_SUCCESS:
            printAdventurePage(page, pokedex);
            break;
        case ADVENTURE_FAIL:
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





