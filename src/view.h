#ifndef VIEW_H
#define VIEW_H
#include "controller.h"
#include "page.h"

typedef struct {
    Controller* controller;
} View;

void clear_screen(void);
void clear_input_buffer(void);
char* clean_input(char* input);

void display_typing_page(Page* page, int screen_length, int screen_height, int typing_delay_ms, int typing_screen_delay_ms);
void display_standard_page(Page* page, int screen_length, int screen_height);
void view_displayPage(Page* page);

char* view_getInput(void);

void view_init(View* view, Controller* controller);

#endif
