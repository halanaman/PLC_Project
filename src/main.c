#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#include "util/pokedex.h"
#include "util/db.h"

Pokedex pokedex;
const char *savefile = "data/pokedex.dat";
#define POKEMON_ROW 10
#define POKEMON_PER_PAGE 20
int cardViewIdx;

typedef enum {
    MENU,
    POKEDEX,
    CARDVIEW,
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
        3, 20},
    {POKEDEX, 
        {"1. Previous Page", "2. Next Page", "3. Adventure", "4. Back to Menu", "5. Save & Exit", "XXX. Access Pokemon #XXX"},
        6, 25},
    {CARDVIEW, 
        {"1. Save Pokemon Card", "2. Back to Pokedex"},
        2, 25},
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

void printCenteredText(const char *text, int width) {
    int len = strlen(text);
    int padding = (width - 2 - len) / 2;
    int extra = (width - 2 - len) % 2;  

    printf("|%*s%s%*s|\n", padding, "", text, padding + extra, "");
}

void printWrappedText(const char *text, int width) {
    int start = 0, end, len = strlen(text) - 1;
    width = width - 4;

    while (start < len) {
        end = start + width;
        if (end > len) end = len;

        if (end < len) {
            while (end > start && text[end] != ' ') end--;
            if (end == start) end = start + width;
        }

        printf("| %-*.*s |\n", width, end - start, text + start);

        start = end;
        while (text[start] == ' ' && start < len) start++;
    }
}

void printPokemonAscii(const char *name, int width) {
    FILE *file;
    char filename[100];
    char line[100];
    sprintf(filename, "data/ascii/%s.txt", name);

    file = fopen(filename, "r");
    if (!file) {
        printCenteredText("ASCII art not found", width);
        return;
    }

    while (fgets(line, sizeof(line)-1, file)) {
        line[strcspn(line, "\n")] = 0;
        printCenteredText(line, width);
    }

    fclose(file);
}


void printCardView(Pokemon *pokemon) {
    int width = 49;  
    char buffer[50];
    

    printf("_________________________________________________\n");
    printCenteredText(pokemon->name, width);

    sprintf(buffer, "%s | HP: %d", pokemon->type, pokemon->hp);
    printCenteredText(buffer, width);

    printf("|-----------------------------------------------|\n");

    printPokemonAscii(pokemon->name, width);

    printf("|-----------------------------------------------|\n");

    sprintf(buffer, "ATK: %-3d | DEF: %-3d | SPD: %-3d | ACC: %-3d%%", 
            pokemon->atk, pokemon->def, pokemon->spd, pokemon->acc);
    printCenteredText(buffer, width);

    printf("|-----------------------------------------------|\n");

    printWrappedText(pokemon->desc, width);
    printf("|_______________________________________________|\n\n");
}


void update_page_state(Page *page, Pokedex *pokedex, char *input)
{
    PageState prevState;
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
    
    if (status1 == 0)
    {
        prevState = page->currentState;
        if (strcmp(input,"1")==0)
        {page->currentState = (prevState == MENU)? POKEDEX : 
                                (prevState == CARDVIEW)? POKEDEX : prevState;}
        else if (strcmp(input,"2")==0)
        {page->currentState = (prevState == MENU)? ADVENTURE : 
                                (prevState == CARDVIEW)? POKEDEX :
                                (prevState == ADVENTURE)? MENU : prevState;}
        else if (strcmp(input,"3")==0)
        {page->currentState = (prevState == MENU)? SAVE :
                                (prevState == POKEDEX)? ADVENTURE : 
                                (prevState == ADVENTURE)? SAVE : prevState;}
        else if (strcmp(input,"4")==0)
        {page->currentState = (prevState == POKEDEX)? MENU : prevState;}
        else if (strcmp(input,"5")==0)
        {page->currentState = (prevState == POKEDEX)? SAVE : prevState;}
    }
    else if (status2 == 0 && page->currentState == POKEDEX)
    {
        cardViewIdx = atoi(input) - 1;
        page->currentState = CARDVIEW;
    }

    
    switch (page->currentState) {
        case MENU:
            printf("Menu:\n");
            break;
        case POKEDEX:
            printf("Pokedex:\n");
            if ((strcmp(input,"1")==0) && page->pokedexPage > 0) {page->pokedexPage--;}
            else if ((strcmp(input,"2")==0) && (page->pokedexPage + 1) * POKEMON_PER_PAGE < pokedex->size) {page->pokedexPage++;}
            printPokedexPage(pokedex, page->pokedexPage);
            break;
        case CARDVIEW:
            printf("CardView:\n");
            printCardView(&pokedex->pokemonList[cardViewIdx]);
            break;
        case ADVENTURE:
            printf("Adventure:\n");
            break;
        case SAVE:
            printf("Saving...\n");
            savePokedex(pokedex, savefile);
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
    char input[65];

    Page page = {MENU, 0};
    loadPokedex(&pokedex, savefile);
    printf("Pokedex Loaded.\n");

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

