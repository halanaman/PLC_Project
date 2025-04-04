#ifndef POKEMON_H
#define POKEMON_H

#define MAX_POKEMON_NAME_LENGTH 20  /** Maximum length for a Pokemon's Name */
#define MAX_POKEMON_TYPE_LENGTH 10  /** Maximum length for a Pokemon's Type */
#define MAX_POKEMON_DESC_LENGTH 100 /** Maximum length for a Pokemon's Description */

/**
 * Struct: Pokemon
 * ---------------
 * Represents a Pokémon and its attributes.
 * 
 * Fields:
 * - id: The unique identifier for the Pokémon.
 * - name: The name of the Pokémon (limited to MAX_POKEMON_NAME_LENGTH).
 * - type: The Pokémon's type (e.g., "Fire", "Water", "Grass").
 * - hp: The Pokémon's hit points (health).
 * - atk: The Pokémon's attack power.
 * - def: The Pokémon's defense power.
 * - spd: The Pokémon's speed stat.
 * - acc: The Pokémon's accuracy stat.
 * - desc: A brief description of the Pokémon (limited to MAX_POKEMON_DESC_LENGTH).
 */
typedef struct {
    int id;                             /** Pokémon ID */
    char name[MAX_POKEMON_NAME_LENGTH]; /** Pokémon name */
    char type[MAX_POKEMON_TYPE_LENGTH]; /** Pokémon type (e.g., "Fire") */
    int hp;                             /** Hit Points (HP) */
    int atk;                            /** Attack stat */
    int def;                            /** Defense stat */
    int spd;                            /** Speed stat */
    int acc;                            /** Accuracy stat */
    char desc[MAX_POKEMON_DESC_LENGTH]; /** Pokémon description */
} Pokemon;

#endif
