#ifndef DB_H
#define DB_H

#include "pokedex.h"

/**
 * Function: savePokedex
 * ---------------------
 * Saves the current Pokédex data to a binary file.
 * 
 * Parameters:
 * - pokedex: Pointer to the Pokedex structure to be saved.
 * - filename: The name of the file where the Pokédex will be stored.
 * 
 * Returns:
 * - 0 on success.
 * - -1 on failure (e.g., file write error).
 * 
 * Notes:
 * - This function writes the entire Pokédex structure to a file.
 * - Memory for the Pokédex will be freed after saving, so no further cleanup is required.
 */
int savePokedex(Pokedex *pokedex, const char *filename);

/**
 * Function: loadPokedex
 * ---------------------
 * Loads Pokédex data from a binary file.
 * 
 * Parameters:
 * - pokedex: Pointer to the Pokedex structure where data will be loaded.
 * - filename: The name of the file from which to load the Pokédex.
 * 
 * Returns:
 * - 0 on success.
 * - -1 on failure (e.g., file read error, memory allocation failure).
 * 
 * Notes:
 * - This function dynamically allocates memory for the Pokédex.
 * - Use `deletePokedex` to free memory when it's no longer needed.
 */
int loadPokedex(Pokedex *pokedex, const char *filename);

#endif


