#include <stdio.h>
#include <string.h>

#include "text.h"

void printCenteredText(const char *text, int width) {
    int len, padding, extra;
    char buffer[128];
    len = strlen(text);
    if (len > width-2) {len = width-2;}
    padding = (width - 2 - len) / 2;
    extra = (width - 2 - len) % 2;
    strncpy(buffer, text, len);
    buffer[len] = 0;

    printf("|%*s%s%*s|\n", padding, "", buffer, padding + extra, "");
}

void printLeftAlignedText(const char *text, int width) {
    int len = strlen(text);
    int padding = width - 4 - len;

    printf("| %s%*s |\n", text, padding, "");
}

void printWrappedText(const char *text, int width) {
    int start, end, len, line_width;
    char line[128], buffer[128];
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
    char filename[128];
    char line[128];
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
    char buffer[128];
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

void printCenteredTextToFile(FILE *out, const char *text, int width) {
    int len, padding, extra;
    char buffer[128];
    len = strlen(text);
    if (len > width-2) {len = width-2;}
    padding = (width - 2 - len) / 2;
    extra = (width - 2 - len) % 2;
    strncpy(buffer, text, len);
    buffer[len] = 0;

    fprintf(out, "|%*s%s%*s|\n", padding, "", buffer, padding + extra, "");
}

void printWrappedTextToFile(FILE *out, const char *text, int width) {
    int start, end, len, line_width;
    char line[128], buffer[128];
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
        printCenteredTextToFile(out, buffer, width);

        start = end;
        while (line[start] == ' ' && start < len) start++;
    }
}

void printPokemonAsciiToFile(FILE *out, const char *name, int width) {
    FILE *file;
    char filename[128];
    char line[128];
    sprintf(filename, "data/ascii/%s.txt", name);

    file = fopen(filename, "r");
    if (!file) {
        printCenteredTextToFile(out, "ASCII art not found", width);
        return;
    }

    while (fgets(line, sizeof(line)-1, file)) {
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;
        printCenteredTextToFile(out, line, width);
    }

    fclose(file);
}

void printBorderToFile(FILE *out, const char *text, int width) {
    char buffer[128];
    if (strcmp(text, "top")==0) {
        memset(buffer, '_', width);
        buffer[width] = 0;
        fprintf(out, "%s\n", buffer);
    }
    else if (strcmp(text, "middle")==0) {
        memset(buffer, '-', width-2);
        buffer[width-2] = 0;
        fprintf(out, "|%s|\n", buffer);
    }
    else if (strcmp(text, "space")==0) {
        memset(buffer, ' ', width-2);
        buffer[width-2] = 0;
        fprintf(out, "|%s|\n", buffer);
    }
    else if (strcmp(text, "bottom")==0) {
        memset(buffer, '_', width-2);
        buffer[width-2] = 0;
        fprintf(out, "|%s|\n\n", buffer);
    }
}

