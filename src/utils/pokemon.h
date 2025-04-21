#ifndef POKEMON_H
#define POKEMON_H

#define MAX_POKEMON_NAME_LENGTH 20
#define MAX_POKEMON_TYPE_LENGTH 10
#define MAX_POKEMON_DESC_LENGTH 100

/**
 * Define the Pokemon structure
 */
typedef struct {
    int id;
    char name[MAX_POKEMON_NAME_LENGTH];
    char type[MAX_POKEMON_TYPE_LENGTH];
    int hp;
    int atk;
    int def;
    int spd;
    int acc;
    char desc[MAX_POKEMON_DESC_LENGTH];
} Pokemon;

char** get_pokemon_ascii(int pokemonId);
char** get_pokemon_subtitle(int pokemonId);

#endif
