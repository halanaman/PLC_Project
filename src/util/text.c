#include <stdio.h>
#include <string.h>

#include "text.h"

void printCenteredText(const char *text, int width) {
    int len = strlen(text);
    int padding = (width - 2 - len) / 2;
    int extra = (width - 2 - len) % 2;  

    printf("|%*s%s%*s|\n", padding, "", text, padding + extra, "");
}

void printLeftAlignedText(const char *text, int width) {
    int len = strlen(text);
    int padding = width - 4 - len;

    printf("| %s%*s |\n", text, padding, "");
}

void printWrappedText(const char *text, int width) {
    int start, end, len, line_width;
    char line[100], buffer[100];
    start = 0;
    strcpy(line, text);
    len = strlen(line);
    line[strcspn(line, "\r")] = 0;
    line_width = width - 4;
    
    while (start < len) {
        end = start + line_width;
        if (end > len) end = len;

        if (end < len) {
            while (end > start && line[end] != ' ') end--;
            if (end == start) end = start + line_width;
        }
        strncpy(buffer, line+start, end-start);
        buffer[end - start] = 0;
        printCenteredText(buffer, width);

        start = end;
        while (line[start] == ' ' && start < len) start++;
    }
}

void printPokemonAscii(const char *name, int width) {
    FILE *file;
    char filename[100];
    char line[100];
    sprintf(filename, "data/ascii/%s.txt", name);

    file = fopen(filename, "r");
    if (!file) {
        printCenteredText("ASCII art not found", width);
        return;
    }

    while (fgets(line, sizeof(line)-1, file)) {
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;
        printCenteredText(line, width);
    }

    fclose(file);
}

void printBorder(const char *text, int width) {
    char buffer[100];
    if (strcmp(text, "top")==0) {
        memset(buffer, '_', width);
        buffer[width] = 0;
        printf("%s\n", buffer);
    }
    else if (strcmp(text, "middle")==0) {
        memset(buffer, '-', width-2);
        buffer[width-2] = 0;
        printf("|%s|\n", buffer);
    }
    else if (strcmp(text, "space")==0) {
        memset(buffer, ' ', width-2);
        buffer[width-2] = 0;
        printf("|%s|\n", buffer);
    }
    else if (strcmp(text, "bottom")==0) {
        memset(buffer, '_', width-2);
        buffer[width-2] = 0;
        printf("|%s|\n\n", buffer);
    }
}


