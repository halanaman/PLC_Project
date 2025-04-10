#ifndef POKEDEX_H
#define POKEDEX_H

#include "pokemon.h"

/**
 * Struct: PokedexListItem
 * -----------------------
 * Represents an entry in the Pokédex list.
 * - id: The unique identifier for the Pokémon.
 * - name: The name of the Pokémon (limited to MAX_POKEMON_NAME_LENGTH).
 * - seen: Indicates if the Pokémon has been encountered (1 = seen, 0 = not seen).
 */
typedef struct {
    int id;                             /** Pokemon ID */
    char name[MAX_POKEMON_NAME_LENGTH]; /** Pokemon Name */
    int seen;                           /** 1 if seen, 0 if not seen */
} PokedexListItem;

/**
 * Struct: Pokedex
 * ---------------
 * Represents the entire Pokédex, containing:
 * - pokedexList: An array of PokedexListItem, tracking Pokémon seen.
 * - pokemonList: An array of Pokemon structures (full Pokémon data).
 * - size: The total number of Pokémon in the Pokédex.
 */
typedef struct {
    PokedexListItem *pokedexList;   /** List of Pokemon seen/not seen */
    Pokemon *pokemonList;           /** List of all Pokemon data */
    int size;                       /** Number of Pokemon in the Pokedex */
} Pokedex;

/**
 * Function: printPokedex
 * ----------------------
 * For debugging/testing purposes. Prints the contents of the Pokédex.
 * 
 * Parameters:
 * - pokedex: Pointer to the Pokedex structure.
 */
void printPokedex(Pokedex *pokedex);

/**
 * Function: createPokedex
 * -----------------------
 * Creates a new Pokédex and allocates memory for it.
 * 
 * Parameters:
 * - size: The number of Pokémon to allocate space for.
 * 
 * Returns:
 * - A Pokedex structure with allocated memory.
 */
Pokedex createPokedex(int size);

/**
 * Function: deletePokedex
 * -----------------------
 * Frees allocated memory and deletes the Pokédex.
 * 
 * Parameters:
 * - pokedex: Pointer to the Pokedex structure to be deleted.
 */
void deletePokedex(Pokedex *pokedex);

#endif
