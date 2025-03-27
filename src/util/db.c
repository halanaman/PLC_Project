#include <stdio.h>
#include <stdlib.h>

#include "db.h"
#include "pokedex.h"

int savePokedex(Pokedex *pokedex, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return -1;
    }
    
    /* Write the size of the Pokedex */
    fwrite(&pokedex->size, sizeof(int), 1, file);
    
    /* Write the PokedexList */
    fwrite(pokedex->pokedexList, sizeof(PokedexListItem), pokedex->size, file);
    
    /* Write the PokemonList */
    fwrite(pokedex->pokemonList, sizeof(Pokemon), pokedex->size, file);
    
    fclose(file);

    /* Free Memory */
    deletePokedex(pokedex);

    return 0;
}

int loadPokedex(Pokedex *pokedex, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return -1;
    }
    
    /* Read the size of the Pokedex */
    fread(&pokedex->size, sizeof(int), 1, file);
    
    *pokedex = createPokedex(pokedex->size);
    
    if (!pokedex->pokedexList || !pokedex->pokemonList) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }
    
    /* Read the PokedexList */
    fread(pokedex->pokedexList, sizeof(PokedexListItem), pokedex->size, file);
    
    /* Read the PokemonList */
    fread(pokedex->pokemonList, sizeof(Pokemon), pokedex->size, file);
    
    fclose(file);
    return 0;
}
