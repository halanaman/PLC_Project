#ifndef POKEDEX_H
#define POKEDEX_H

#include "pokemon.h"

/**
 * Define the PokedexListItem structure
 */
typedef struct {
    int id;
    char name[MAX_POKEMON_NAME_LENGTH];
    int seen;
} PokedexListItem;

/**
 * Define the Pokedex structure
 */
typedef struct {
    PokedexListItem *pokedexList;
    Pokemon *pokemonList;
    int size;
} Pokedex;

/**
 * For Testing: Print the contents of Pokedex
 * Input: Pokedex
 */
void printPokedex(Pokedex *pokedex);

/**
 * Create a Pokedex, and allocate memory
 * Input: Number of Pokemons
 * Output: Pokedex
 */
Pokedex createPokedex(int size);

/**
 * Free allocated memory, delete Pokedex
 * Input: Pokedex
 */
void deletePokedex(Pokedex *pokedex);

#endif
