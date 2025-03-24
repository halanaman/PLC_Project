#ifndef POKEMON_H
#define POKEMON_H

#define MAX_NAME_LENGTH 20
#define MAX_TYPE_LENGTH 20
#define MAX_DESC_LENGTH 100

/**
 * Define the Pokemon structure
 */
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int hp;
    int atk;
    int def;
    int spd;
    int acc;
    char desc[MAX_DESC_LENGTH];
} Pokemon;

#endif
