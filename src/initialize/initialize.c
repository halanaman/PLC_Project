#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "../util/pokedex.h"
#include "../util/db.h"

int main(int argc, char ** argv) {
    Pokedex pokedex;
    const char *filename = "../../data/pokemon.csv";
    const char *savefile = "../../data/pokedex.dat";

    /* Count lines to allocate memory */
    int numPokemon = countLinesInFile(filename);
    if (numPokemon <= 0) {
        printf("No data found.\n");
        return 1;
    }

    pokedex = createPokedex(numPokemon);

    /* Convert csv to Pokedex */
    loadPokedexFromCSV(&pokedex, filename);

    /* Print Pokedex */
    printPokedex(&pokedex);

    /* Save Pokedex to a binary file*/
    savePokedex(&pokedex, savefile);

    deletePokedex(&pokedex);

    return 0;
}


