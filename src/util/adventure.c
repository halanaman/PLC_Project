#include <stdio.h>
#include <string.h>
#include "adventure.h"

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

void type_text(const char* text, int delay_ms) {
    /* Types out some text with specified delay between characters */
    int i;
    for (i = 0; i < strlen(text); i++) {
        putchar(text[i]);
        fflush(stdout);
        SLEEP(delay_ms);
    }
}

void render_adv_cutscene(DisplayStrings displayText, int numRows) {
    int i, rows;
    const char* blockZeroText = "Adventure\n";
    clear_screen();

    printf("%s%s", LEFT_PADDING, blockZeroText);
    for (i = 0; i < 6; i++) {
        printf("\n");
    }
    /* Types out displayText */
    for (rows = 0; rows < numRows; rows++) {
        printf("%s", LEFT_PADDING);
        type_text(displayText[rows], 100);
    }
    SLEEP(1000);
}


