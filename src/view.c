#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "view.h"
#include "utils/constants.h"
#include "utils/printhelper.h"

#ifdef _WIN32
#include <windows.h>
#define strdup _strdup
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#endif

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clear_input_buffer(void) {
    int c;
    while ( ((c = getchar()) != '\n') && (c != EOF) );
}

char* clean_input(char* input) {
    /* Remove spaces and convert all uppercase inputs to lowercase */
    char* input_ptr = input;
    char* write_ptr = input;

    while (*input_ptr) {
        if (*input_ptr != ' ') {
            *write_ptr = tolower(*input_ptr);
            write_ptr++;
        }
        input_ptr++;
    }
    *write_ptr = '\0';
    return input;
}

void display_typing_page(Page* page, int screen_length, int screen_height, int typing_delay_ms, int typing_screen_delay_ms) {
    int sceneIdx;
    int contentHeight;

    /* For each scene */
    for (sceneIdx = 0; sceneIdx < page->typedSceneCount; sceneIdx++) {
        int currentLine, lineCount, currentChar, totalChars;
        const char** scene = page->typedScenes[sceneIdx];

        /* Count total no of characters and lines */
        lineCount = 0;
        totalChars = 0;
        while (scene[lineCount] != NULL) {
            totalChars += strlen(scene[lineCount]);
            lineCount++;
        }

        /* For each line */
        currentChar = 0;
        for (currentLine = 0; currentLine < lineCount; currentLine++) {
            int i;
            const char* line = scene[currentLine];

            /* For each character */
            for (i = 0; line[i] != '\0' && currentChar < totalChars; i++, currentChar++) {
                int j;

                /* Initialize array of strings */
                char** typedChars = malloc((lineCount + 1) * sizeof(char*));
                for (j = 0; j <= lineCount; j++) {
                    typedChars[j] = NULL;
                }

                /* Copy lines typed so far into array */
                for (j = 0; j < currentLine; j++) {
                    typedChars[j] = strdup(scene[j]);
                }
                /* Copy characters typed so far into the array */
                if (line[i] != '\0') {
                    typedChars[currentLine] = malloc(i + 2);
                    strncpy(typedChars[currentLine], line, i + 1);
                    typedChars[currentLine][i + 1] = '\0';
                } else {
                    typedChars[currentLine] = strdup(line);
                }

                contentHeight = screen_height - 3;
                /* Print the page */
                clear_screen();
                print_title(page->title, screen_length);
                print_content_subtitle(page->contentAlignment, typedChars, NULL, screen_length, contentHeight);
                print_bottom_border(screen_length);
                print_error_msg(page->errorMsg);
                
                /* Free after malloc*/
                for (j = 0; j < lineCount; j++) {
                    if (typedChars[j]) {
                        free(typedChars[j]);
                    }
                }
                free(typedChars);
                
                /* Delay before typing next character */
                SLEEP(typing_delay_ms);
            }
        }
        /* Delay before going to next screen */
        SLEEP(typing_screen_delay_ms);
    }

    /* Display final page */
    display_standard_page(page, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void display_standard_page(Page* page, int screen_length, int screen_height) {
    int contentHeight = (page->actionsCount > 0) ? (screen_height - page->actionsCount - 5) : (screen_height - 3);

    clear_screen();
    print_title(page->title, screen_length);
    print_content_subtitle(page->contentAlignment, page->content, page->subtitle, screen_length, contentHeight);
    print_actions(page->actions, page->actionsCount, screen_length);
    print_bottom_border(screen_length);
    print_error_msg(page->errorMsg);
}

void view_displayPage(Page* page) {
    if (page->pageType == STANDARD_PAGE) {
        display_standard_page(page, SCREEN_WIDTH, SCREEN_HEIGHT);
    } else if ((page->pageType == TYPING_PAGE) && page->errorMsg) {
        /* Skip typing if there's an error message */
        display_standard_page(page, SCREEN_WIDTH, SCREEN_HEIGHT);
    } else {
        display_typing_page(page, SCREEN_WIDTH, SCREEN_HEIGHT, TYPING_DELAY, TYPING_SCREEN_DELAY);
    }
    if (page) { page_free(page); }
}

char* view_getInput(void) {
    static char input[MAX_MENU_INPUT_LENGTH + 2];
    int input_length;

    /* Get input from user */
    printf("Enter choice: ");

    /* If error occurs or EOF is reached */
    if (fgets(input, sizeof(input), stdin) == NULL) {
        input[0] = '\0';
        return input;
    }

    input_length = strlen(input);
    if (input_length > 0 && input[input_length-1] == '\n') {
        /* Remove newline */
        input[input_length-1] = '\0';
    } else {
        /* Clear input buffer if it's not a newline */
        clear_input_buffer();
    }

    return clean_input(input);
}

void view_init(View* view, Controller* controller) {
    view->controller = controller;
    view_displayPage(controller_getPage(view->controller));

    while (view->controller->isRunning) {
        char* input;
        input = view_getInput();
        controller_handleInput(view->controller, input);
    }
}


