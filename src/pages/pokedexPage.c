#include "pokedexPage.h"
#include "../util/page.h"
#include "homePage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/input.h"
#include <regex.h>
#include "../fsm.h"
#include "../util/pokedex.h"
#include "../util/constants.h"

#define POKEMON_LIST_MAX_ROWS 8
#define MAX_COLUMNS_PER_ENTRY 16

/**
 * TODO
 * - what happen if i want to view a pokemon that has not been seen? 
 * should i reject input on this page, or navigate to view pokemon, and view pokemon handles unseen pokemon?
 * - should we add a total_seen count in pokedex.c?
 */

/* Helper functions */
void initialize_pokedex_page_data(PokedexPageInputState *inputState, PokedexPageState *pokedexPageState, AppStateStruct *appStateStruct) {
    InputState *base = (InputState *)inputState;
    base->errorState = 0;
    base->appState = STATE_POKEDEX;
    base->stateAppState = SHOW_POKEDEXLIST;
    base->parserFunction = &pokedex_list_page_parser;

    *pokedexPageState = (PokedexPageState) appStateStruct->nextStateNextAppState;
}

void create_pokemon_list_string_array(PokedexListItem *pokemonList, DisplayStrings pokemonListText, int startIndex) {
    int rowsInColumnOne, rowsInColumnTwo, indexOnePokemonList, indexTwoPokemonList, i;
    char columnOneName[SCREEN_LENGTH - 1 / 2], columnTwoName[SCREEN_LENGTH - 1 / 2];

    rowsInColumnOne = (startIndex + POKEMON_LIST_MAX_ROWS < pokedex.size) ? 
        POKEMON_LIST_MAX_ROWS :
        pokedex.size - startIndex;

    rowsInColumnTwo = (startIndex + rowsInColumnOne >= pokedex.size) ? 
        0 :
        (startIndex + rowsInColumnOne + POKEMON_LIST_MAX_ROWS < pokedex.size) ? 
        POKEMON_LIST_MAX_ROWS :
        pokedex.size - (startIndex + rowsInColumnOne);

    for (i = 0; i < 8; i++) {
        /* clear current row and replace with default of newline first*/
        snprintf_implement(pokemonListText[i],sizeof(char) * 2, "\n");
        if (i >= rowsInColumnOne) continue;

        /* assign pokemon name for column 1*/
        indexOnePokemonList = i + startIndex;
        if (pokemonList[indexOnePokemonList].seen < 1)
            snprintf_implement(columnOneName, sizeof(columnOneName), "%03d %-*s", indexOnePokemonList + 1, MAX_COLUMNS_PER_ENTRY, "-----");
        else
            snprintf_implement(columnOneName, sizeof(columnOneName), "%03d %-*s", indexOnePokemonList + 1, MAX_COLUMNS_PER_ENTRY, pokemonList[indexOnePokemonList].name);
        
        /* assign pokemon name for column 2 if relevant*/
        if (i >= rowsInColumnTwo) {
            snprintf_implement(columnTwoName, sizeof(columnTwoName), "");
        } else {
            indexTwoPokemonList = indexOnePokemonList + POKEMON_LIST_MAX_ROWS;
            if (pokemonList[indexTwoPokemonList].seen < 1)
                snprintf_implement(columnTwoName, sizeof(columnTwoName), "%03d %-*s", indexTwoPokemonList + 1, MAX_COLUMNS_PER_ENTRY,"-----");
            else
                snprintf_implement(columnTwoName, sizeof(columnTwoName), "%03d %-*s", indexTwoPokemonList + 1, MAX_COLUMNS_PER_ENTRY, pokemonList[indexTwoPokemonList].name);
        }
        /* assign row string to relevant row of pokemonListText*/
        snprintf_implement(
            pokemonListText[i], 
            sizeof(pokemonListText[i]),
            "%s%s\n",
            columnOneName,
            columnTwoName
        );

    }
}

/* Main functions */

/**
 * parser function. Valid inputs are 1,2,3,4 
 * or 3 digit string, where the max value is at most MAX_POKEMON
 */
void pokedex_list_page_parser(InputState *inputState, char *input) {
    PokedexPageInputState *pokedexPageInputState;
    regex_t regex;
    char *pattern = "^[0-9]{3}$";
    pokedexPageInputState = (PokedexPageInputState *) inputState;
    if (strcmp(input, "1") == 0 && pokedexPageInputState->lowestIndexDisplayed + 16 < pokedex.size) {
        pokedexPageInputState->lowestIndexDisplayed += 16; 
        update_input_state(inputState, 0, SHOW_POKEDEXLIST, STATE_POKEDEX, 0);
    } else if (strcmp(input, "2") == 0 && pokedexPageInputState->lowestIndexDisplayed != 0) {
        pokedexPageInputState->lowestIndexDisplayed -= 16;
        update_input_state(inputState, 0, SHOW_POKEDEXLIST, STATE_POKEDEX, 0);
    } else if (strcmp(input, "3") == 0) {
        update_input_state(inputState, 0, SHOW_POKEDEXLIST, STATE_POKEDEX, 0);
    } else if (strcmp(input, "4") == 0) {
        update_input_state(inputState, 0, EXIT_POKEDEXPAGE, STATE_HOME, SHOW_HOMEPAGE);
    } else {
        if(regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
            /* assigning memory to regex in regcompile failed */
            update_input_state(inputState, 3, SHOW_POKEDEXLIST, STATE_POKEDEX, 0);
            return;
        }
        if (regexec(&regex, input, 0, NULL, 0) == 0)
            if (atoi(input) <= pokedex.size)
                /* This should lead to view pokemon page*/
                update_input_state(inputState, 0, SHOW_POKEDEXLIST, STATE_POKEDEX, 0);
            else 
                /* Valid pokemon number syntax, but number is higher than total number of pokemon*/
                update_input_state(inputState, 2, SHOW_POKEDEXLIST, STATE_POKEDEX, 0);
        else
            /** This means invalid input, and appropriate error message should be shown */
            update_input_state(inputState, 1, SHOW_POKEDEXLIST, STATE_POKEDEX, 0);
        regfree(&regex);
    }
}

Page *create_pokedex_list_page(int lowestIndexDisplayed) {
    PokedexListItem *pokemonList;
    RenderedBlocks *pokedexPageBlocks;
    Page *pokedexListPage; 

    /* Init display strings */
    DisplayStrings blockZeroText = {"Pokedex List\n"};
    DisplayStrings blockOneText;
    DisplayStrings blockTwoText = {
        "┌──────────────────────────────┐\n",
        "│ 1: Next Pokedex Page         │\n",
        "│ 2: Previous Pokedex Page     │\n",
        "│ 3: Add Custom Pokemon        │\n",
        "│ 4: Back To Home Menu         │\n",
        "│ XXX: View Pokemon XXX(001)   │\n",
        "└──────────────────────────────┘\n"
    };
    if (lowestIndexDisplayed == 0)
        snprintf_implement(blockTwoText[2], SCREEN_LENGTH_BYTES, "│ 2: Previous Pokedex Page (NA)│\n");
    if (lowestIndexDisplayed + 16 >= pokedex.size)
        snprintf_implement(blockTwoText[1], SCREEN_LENGTH_BYTES, "│ 1: Next Pokedex Page     (NA)│\n");
    pokemonList = pokedex.pokedexList;
    create_pokemon_list_string_array(pokemonList, blockOneText, lowestIndexDisplayed);

    /* create blocks/ page */
    pokedexPageBlocks = create_blocks(3);
    if (!pokedexPageBlocks) return NULL;

    add_block_to_blocks(pokedexPageBlocks, 0, 0, 1, SCREEN_LENGTH, blockZeroText);
    add_block_to_blocks(pokedexPageBlocks, 1, 2, POKEMON_LIST_MAX_ROWS, SCREEN_LENGTH, blockOneText);
    add_block_to_blocks(pokedexPageBlocks, 2, 11, 7, SCREEN_LENGTH, blockTwoText);

    pokedexListPage = create_page("pokedex", pokedexPageBlocks);
    if (!pokedexListPage) {
        free_blocks(pokedexPageBlocks);
        return NULL;
    }

    return pokedexListPage;
}

void run_pokedex_page(AppStateStruct *appStateStruct) {
    Page *pokedexPage;
    PokedexPageInputState inputState;
    InputState *baseInputState;
    PokedexPageState pokedexPageState;

    initialize_pokedex_page_data(
        &inputState, 
        &pokedexPageState, 
        appStateStruct
    );
    /* Typecast specialized PokedexPageInputState back to InputState, because get_user_input() only accepts type InputState*/
    baseInputState = (InputState *) &inputState;

    while (pokedexPageState != EXIT_POKEDEXPAGE) {
        switch(pokedexPageState) {
            case SHOW_POKEDEXLIST:
                pokedexPage = create_pokedex_list_page(inputState.lowestIndexDisplayed);
                if (!pokedexPage) {
                    pokedexPageState = EXIT_POKEDEXPAGE;
                    update_app_state_struct(appStateStruct, STATE_SAVE, 0);
                    break;
                }
                render_page(pokedexPage);
                get_user_input(baseInputState, EXIT_POKEDEXPAGE);
                pokedexPageState = baseInputState->stateAppState;
                update_app_state_struct(
                    appStateStruct, 
                    baseInputState->appState, 
                    baseInputState->nextStateNextAppState
                );
                break;
            case SHOW_POKEMONCARD:
                break;
            case SHOW_ADDPOKEMON:
                break;
            case EXIT_POKEDEXPAGE:
                break;
        }
    }
}
