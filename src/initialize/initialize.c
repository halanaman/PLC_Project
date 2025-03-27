#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "../util/pokedex.h"
#include "../util/db.h"

Pokedex pokedex;
const char *filename = "../../data/pokemon.csv";
const char *savefile = "../../data/pokedex.dat";

int main(int argc, char ** argv) {
    
    /* Convert csv to Pokedex */
    loadPokedexFromCSV(&pokedex, filename);

    /* Print Pokedex */
    printPokedex(&pokedex);

    /* Save Pokedex to a binary file*/
    savePokedex(&pokedex, savefile);

    return 0;
}


