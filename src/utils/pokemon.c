#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pokemon.h"

char** get_pokemon_ascii(int pokemonId) {
    char** ascii = malloc(2 * sizeof(char*));
    char buffer[64];
    /* to fill in code here */
    ascii[0] = strdup(buffer);
    ascii[1] = NULL;
    return ascii;
}

char** get_pokemon_subtitle(int pokemonId) {
    char** subtitle = malloc(3 * sizeof(char*));
    char buffer[30];
    /* to fill in code here */
    snprintf(buffer, sizeof(buffer), "Wild %s appeared!", "Pokemon ID");
    subtitle[0] = strdup(buffer);
    subtitle[1] = strdup("You saved the Pokemon to your Pokedex.");
    subtitle[2] = NULL;
    return subtitle;
}
