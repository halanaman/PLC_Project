#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "../util/pokedex.h"

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int countLinesInFile(const char *filename) {
    int count;
    char buffer[MAX_LINE_LENGTH];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    count = 0;
    while (fgets(buffer, MAX_LINE_LENGTH, file)) {
        count++;
    }

    fclose(file);
    return count - 1; /* Exclude Header Line */
}

void loadPokedexFromCSV(Pokedex *pokedex, const char *filename) {
    int numPokemon;
    FILE *file;
    char buffer[MAX_LINE_LENGTH];
    int index;
    char *token;
    Pokemon p;
    
    /* Count lines to allocate memory */
    numPokemon = countLinesInFile(filename);
    if (numPokemon <= 0) {
        printf("No data found.\n");
        exit(1);
    }

    *pokedex = createPokedex(numPokemon);

    file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    /* Skip Header Line */
    fgets(buffer, MAX_LINE_LENGTH, file);

    index = 0;
    while (fgets(buffer, MAX_LINE_LENGTH, file)) {
        trimNewline(buffer);

        token = strtok(buffer, ",");
        if (!token) continue;

        p.id = atoi(token);
        strcpy(p.name, strtok(NULL, ","));
        strcpy(p.type, strtok(NULL, ","));
        p.hp = atoi(strtok(NULL, ","));
        p.atk = atoi(strtok(NULL, ","));
        p.def = atoi(strtok(NULL, ","));
        p.spd = atoi(strtok(NULL, ","));
        p.acc = atof(strtok(NULL, ","));
        strcpy(p.desc, strtok(NULL, ","));

        /* Store in Pokedex */
        pokedex->pokemonList[index] = p;

        /* Populate Pokedex List */
        pokedex->pokedexList[index].id = p.id;
        strcpy(pokedex->pokedexList[index].name, p.name);
        pokedex->pokedexList[index].seen = 0; /* Default 0 */

        index++;
    }

    pokedex->size = index;
    fclose(file);
}
