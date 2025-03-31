#include <regex.h>
#include <stdio.h>
#include <string.h>
#include "pokemon.h"
#include <ctype.h>
#include <stdlib.h>
#include "../util/constants.h"

/**
 * id: given by program
 * name: max is MAX_POKEMON_NAME_LENGTH, spaces allows, only alphabets allowed, only punctuation of - ' allowed.
 * ---> first letter and first char after space is captitalised, every other char should be small letters
 * type: max is MAX_POKEMON_TYPE_LENGTH, spaces not allowed, only alphabets allowed. Follows one of the assigned type. 
 * ---> first letter capitalised, every other char are small letters
 * hp, atk, def, spd, acc: numbers only, no dots, 2 digits or 100 allowed. 
 * ---> convert to int type 
 * desc: max is MAX_POKEMON_DESC_LENGTH, spaces and punctuation allowed. Grammer should be enforced, char after . should be captitalized, char after , should not be capitalized.
 * ---> apply similar pre-processing for name?
 */

static const char *pokemonNamePattern = "^[A-Z][a-zA-Z'-]*( [A-Z][a-zA-Z'-]*)*$";
static const char *pokemonTypePattern = "^[a-zA-Z]+(/[a-zA-Z]+)?$"; /* multiple types will be fire/ice */
static const char *pokemonFieldIntegerPattern = "^([1-9][0-9]{0,1}|100)$"; /* 0 not accepted*/
static const char *pokemonDescriptionPattern = "^([A-Z][a-z]*(,? [a-z]+)*[.?!] ?)+$";
static const char acceptedPokemonTypes[][MAX_POKEMON_TYPE_LENGTH] = {
    "Normal",
    "Fire",
    "Water",
    "Grass",
    "Electric",
    "Ice",
    "Fighting",
    "Poison",
    "Ground",
    "Flying",
    "Psychic",
    "Bug",
    "Rock",
    "Ghost",
    "Dragon",
    "Dark",
    "Steel",
    "Fairy"
};
#define NUM_POKEMON_TYPES (sizeof(acceptedPokemonTypes) / sizeof(acceptedPokemonTypes[0]))
#define MAX_2_POKEMON_TYPE_LENGTH (MAX_POKEMON_TYPE_LENGTH * 2 + 1)


/* Helper Function*/

/** Checks for valid regex and length
 *  1 for valid
 *  0 for invalid
 */
int isInputValueValid(const char *inputValue, const char *pattern, const int maxLength) {
    int result;
    regex_t regex;
    regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (strlen(inputValue) <= maxLength && regexec(&regex, inputValue, 0, NULL, 0) == 0) {
        result = 1;
    } else {
        result = 0;
    }
    regfree(&regex);
    return result;
}

/* Main functions */

/** 
 * writes to valid out put buffer. returns 1 for valid input, returns 0 for invalid input
 */
int processPokemonNameInput(const char *inputPokemonName, char *outputPokemonName) {
    int isValid;
    isValid = isInputValueValid(inputPokemonName, pokemonNamePattern, MAX_POKEMON_NAME_LENGTH);
    if (isValid == 1) 
        snprintf_implement(outputPokemonName, MAX_POKEMON_NAME_LENGTH + 1, "%s", inputPokemonName);
    
    return isValid;
}

/** 
 *  writes to valid out put buffer. returns 1 for valid input, returns 0 for invalid input
 */
int processPokemonTypeInput(const char *inputPokemonType, char *outputPokemonType1, char *outputPokemonType2) {
    int isValid, i, j, found;
    char *token;
    char inputString[MAX_2_POKEMON_TYPE_LENGTH + 1];
    
    isValid = isInputValueValid(inputPokemonType, pokemonTypePattern, MAX_2_POKEMON_TYPE_LENGTH);
    if (isValid == 0) return 0;

    /* copy input string to buffer */
    snprintf_implement(inputString, MAX_2_POKEMON_TYPE_LENGTH + 1, "%s", inputPokemonType);

    token = strtok(inputString, "/");
    for (i = 0; token != NULL; i++) {
        /* invalid if more than 2 types detected. Should never come here as above pattern already checks for max 2 types.*/
        if (i > 1) return 0;

        /* make first letter capitalized, and the rest lower case. */
        for (j = 0; token[j]; j++) {
            if (j == 0) token[0] = toupper((unsigned char) token[0]);
            else token[j] = tolower((unsigned char) token[j]);
        }

        /* check that token exist in accepted types*/
        found = 0;
        for (j = 0; j < NUM_POKEMON_TYPES; j++) {
            if (strcmp(token, acceptedPokemonTypes[j]) == 0) {
                found = 1;
                if (i == 0) {
                    snprintf_implement(outputPokemonType1, MAX_POKEMON_TYPE_LENGTH + 1, "%s", token);
                    break;
                } else if (i == 1) {
                    /* invalid if 1st and 2nd token have the same value */
                    if (strcmp(token, outputPokemonType1) == 0) return 0;
                    snprintf_implement(outputPokemonType2, MAX_POKEMON_TYPE_LENGTH + 1, "%s", token);
                    break;
                } 
            }
        }
        /* invalid if current token not found in accepted type */
        if (found == 0) return 0; 
        else token = strtok(NULL, "/");
    }
    /* if only 1 type found, ensure outputPokemonType2 points to null */
    if (i == 1) outputPokemonType2[0] = '\0';
    return 1;
}

int processPokemonFieldIntegerInput(const char *inputPokemonFieldInteger, int *outputPokemonFieldInteger) {
    int isValid;
    isValid = isInputValueValid(inputPokemonFieldInteger, pokemonFieldIntegerPattern, 3);
    if (isValid == 1) 
        *outputPokemonFieldInteger = atoi(inputPokemonFieldInteger);
    return isValid;
}

int processPokemonDescriptionInput(const char *inputPokemonDescription, char *outputPokemonDescription) {
    int isValid;
    isValid = isInputValueValid(inputPokemonDescription, pokemonDescriptionPattern, MAX_POKEMON_DESC_LENGTH);
    if (isValid == 1) 
        snprintf_implement(outputPokemonDescription, MAX_POKEMON_DESC_LENGTH + 1, "%s", inputPokemonDescription);
    return isValid;
}

