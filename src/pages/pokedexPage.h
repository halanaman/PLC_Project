#ifndef POKEDEXPAGE_H
#define POKEDEXPAGE_H

#include "../util/page.h"
#include "../fsm.h"
#include "../util/input.h"

typedef enum {
    SHOW_POKEDEXLIST,
    SHOW_POKEMONCARD,
    SHOW_ADDPOKEMON,
    EXIT_POKEDEXPAGE
} PokedexPageState;

typedef struct {
    InputState globalInputState;
    int lowestIndexDisplayed; /* This represents the first index of the pokemon showed on pokedex list page*/
} PokedexPageInputState;

void pokedex_list_page_parser(InputState *inputState, char *input);
void run_pokedex_page(AppStateStruct *appStateStruct);

#endif
