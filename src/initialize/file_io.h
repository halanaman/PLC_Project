#ifndef FILE_IO_H
#define FILE_IO_H

#include "../util/pokedex.h"

#define MAX_LINE_LENGTH 256

/**
 * Removes newline from a string and replace with '\0'
 * Input: Pointer to a string
 */
void trimNewline(char *str);

/**
 * Counts the number of lines from a file
 * Input: filename(csv file)
 * Output: Number of lines(Pokemons) on success, -1 on failure
 */
int countLinesInFile(const char *filename);

/**
 * Loads Pokedex data from a csv file
 * Input: Pokedex, filename(csv file)
 * Notes: Memory will be allocated for Pokedex, use deletePokedex if needed
 */
void loadPokedexFromCSV(Pokedex *pokedex, const char *filename);

#endif


