#ifndef FILE_IO_H
#define FILE_IO_H

#include "../util/pokedex.h"

#define MAX_LINE_LENGTH 256 /** Maximum length for a line in the CSV file */

/**
 * Function: trimNewline
 * ---------------------
 * Removes the newline character (`\n`) from a string and replaces it with `\0`.
 * 
 * Parameters:
 * - str: Pointer to the string to be modified.
 */
void trimNewline(char *str);

/**
 * Function: countLinesInFile
 * --------------------------
 * Counts the number of lines in a CSV file.
 * 
 * Parameters:
 * - filename: The name of the CSV file to read.
 * 
 * Returns:
 * - The number of lines (Pokémon entries) in the file on success.
 * - -1 on failure (e.g., file not found or read error).
 */
int countLinesInFile(const char *filename);

/**
 * Function: loadPokedexFromCSV
 * ----------------------------
 * Loads Pokédex data from a CSV file.
 * 
 * Parameters:
 * - pokedex: Pointer to the Pokedex structure where data will be loaded.
 * - filename: The name of the CSV file containing Pokémon data.
 * 
 * Notes:
 * - This function dynamically allocates memory for the Pokédex.
 * - Use `deletePokedex` to free memory when it's no longer needed.
 */
void loadPokedexFromCSV(Pokedex *pokedex, const char *filename);

#endif


