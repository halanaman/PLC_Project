#include <stdio.h>
#include <stdlib.h>

#include "pokedex.h"

void printPokedex(Pokedex *pokedex) {
    int i;
    printf("Pokedex:\n");
    for (i = 0; i < pokedex->size; i++) {
        printf("ID: %03d | Name: %-10s | Type: %-15s | HP: %d | Atk: %d | Def: %-3d | Spd: %-3d | Acc: %-3d%% | Desc: %s\n",
               pokedex->pokemonList[i].id,
               pokedex->pokemonList[i].name,
               pokedex->pokemonList[i].type,
               pokedex->pokemonList[i].hp,
               pokedex->pokemonList[i].atk,
               pokedex->pokemonList[i].def,
               pokedex->pokemonList[i].spd,
               pokedex->pokemonList[i].acc,
               pokedex->pokemonList[i].desc);
    }

    printf("Pokedex Seen List:\n");
    for (i = 0; i < pokedex->size; i++) {
        printf("ID: %03d | Name: %-10s | Seen: %d\n",
               pokedex->pokedexList[i].id,
               pokedex->pokedexList[i].name,
               pokedex->pokedexList[i].seen);
    }
}

Pokedex createPokedex(int size) {
    Pokedex pokedex;

    pokedex.size = size;
    /* Allocate memory */
    pokedex.pokedexList = (PokedexListItem *)malloc(size * sizeof(PokedexListItem));
    pokedex.pokemonList = (Pokemon *)malloc(size * sizeof(Pokemon));

    return pokedex;
}

void deletePokedex(Pokedex *pokedex) {
    free(pokedex->pokedexList);
    free(pokedex->pokemonList);
}