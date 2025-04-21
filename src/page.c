#include "page.h"
#include "fsm.h"
#include "utils/pokemon.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

const char* getTitle(State state) {
    switch (state) {
        case STATE_HOME:      return "Home";
        case STATE_ADVENTURE: return "Adventure";
        case STATE_POKEDEX:   return "Pokedex";
        case STATE_POKEMON:   return "Pokemon";
        case STATE_SAVE:      return "Save & Exit";
        default: return "Unknown Title";
    }
}

const char* getErrorMsg(int errorState) {
    switch (errorState) {
        case 0: return NULL;
        case 1: return "Invalid input, please try again!";
        case 2: return "Pokemon with this number does not exist.";
        case 3: return "Memory allocation error. Try again.";
        case 4: return "Unknown State detected, returning to HOME state.";
        default: return "Unknown error.";
    }
}

Page* page_get(FSM* fsm, int pokemonId, int screenWidth, int screenHeight) {
    State state;
    int subState, errorState;
    
    Page* page = malloc(sizeof(Page));
    static const Action nullActions[] = {{NULL, NULL}};
    static const Action errorActions[] = {
        {"1", "Back"},
    };

    state = fsm_getCurrentState(fsm);
    subState = fsm_getCurrentSubState(fsm);
    errorState = fsm_getErrorState(fsm);

    /* Set page default values */
    page->pageType = STANDARD_PAGE;
    page->contentAlignment = ALIGN_CENTER;
    page->title = getTitle(state);
    page->typedScenes = NULL;
    page->typedSceneCount = 0;
    page->content = NULL;
    page->subtitle = NULL;
    page->actions = nullActions;
    page->actionsCount = 0;
    page->errorMsg = getErrorMsg(errorState);
    
    /* Customize pages */
    if (state == STATE_HOME) {
        /* Home Page */
        static const Action homeActions[] = {
            {"1", "View Pokedex"},
            {"2", "Start Adventure"},
            {"s", "Save & Exit"},
        };
        
        page->subtitle = malloc(3 * sizeof(char*));
        page->subtitle[0] = strdup("Welcome to PokeVenture!");
        page->subtitle[1] = strdup("Start exploring now and catch 'em all!");
        page->subtitle[2] = NULL;
        page->actions = homeActions;
        page->actionsCount = 3;

    } else if (state == STATE_ADVENTURE) {
        /* Adventure Page */
        static const Action advActions[] = {
            {"1", "Check it out"},
            {"b", "Back to menu"},
        };

        static const char* typedScene1[] = {
            "Let's go explore and hopefully",
            "encounter some new Pokemon!",
            NULL
        };
        static const char* typedScene2[] = {
            "Exploring...",
            NULL
        };
        static const char** typedScenes[] = {typedScene1, typedScene2};
        
        static const Action encPkmActions[] = {
            {"1", "Adventure again"},
            {"2", "View Pokemon"},
            {"b", "Back to menu"},
        };
        static const Action encNthActions[] = {
            {"1", "Adventure again"},
            {"b", "Back to menu"},
        };

        switch (subState) {
            case 0:
                /* Adventure Cutscene */
                page->pageType = TYPING_PAGE;
                page->typedScenes = typedScenes;
                page->typedSceneCount = 2;

                page->subtitle = malloc(2 * sizeof(char*));
                page->subtitle[0] = strdup("Something's moving in the grass!");
                page->subtitle[1] = NULL;

                page->actions = advActions;
                page->actionsCount = 2;
                break;
            case 1:
                /* Encounter Pokemon */
                page->content = get_pokemon_ascii(pokemonId);
                page->subtitle = get_pokemon_subtitle(pokemonId);
                page->actions = encPkmActions;
                page->actionsCount = 3;
                break;
            case 2:
                /* Encounter Nothing */                
                srand(time(NULL));
                /* Randomly choose one fail message */

                page->subtitle = malloc(2 * sizeof(char*));
                page->subtitle[0] = strdup("Oh... it was just the wind...");
                page->subtitle[1] = NULL;

                page->actions = encNthActions;
                page->actionsCount = 2;
                break;
            default:
                page->subtitle = malloc(2 * sizeof(char*));
                page->subtitle[0] = strdup("Invalid state!");
                page->subtitle[1] = NULL;
                
                page->actions = errorActions;
                page->actionsCount = 1;
        }
    } else if (state == STATE_POKEDEX) {
        /* code */
    } else if (state == STATE_SAVE) {
        static const char* typedText1[] = {
            "Saving game...",
            NULL
        };
        static const char** typedScenes[] = {typedText1};
        page->pageType = TYPING_PAGE;
        page->typedScenes = typedScenes;
        page->typedSceneCount = 1;

        page->subtitle = malloc(2 * sizeof(char*));
        page->subtitle[0] = strdup("Game saved successfully");
        page->subtitle[1] = NULL;

    } else {
        page->subtitle = malloc(2 * sizeof(char*));
        page->subtitle[0] = strdup("Invalid state!");
        page->subtitle[1] = NULL;
        page->actions = errorActions;
        page->actionsCount = 1;
    }
    return page;
}


void page_free(Page* page) {
    if (page->content) {
        int i;
        for (i = 0; page->content[i] != NULL; i++) {
            free(page->content[i]);
        }
        for (i = 0; page->subtitle[i] != NULL; i++) {
            free(page->subtitle[i]);
        }
        free(page->content);
        free(page->subtitle);
    }
    free(page);
}


