#ifndef DB_H
#define DB_H

#include "pokedex.h"

/**
 * Save the Pokedex to a binary file
 * Input: Pokedex
 * Output: 0 on success, -1 on failure
 */
int savePokedex(Pokedex *pokedex, const char *filename);

/**
 * Load the Pokedex from a binary file
 * Input: Pokedex
 * Output: 0 on success, -1 on failure
 */
int loadPokedex(Pokedex *pokedex, const char *filename);

#endif