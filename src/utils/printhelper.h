#ifndef PRINTHELPER_H
#define PRINTHELPER_H

#include "../page.h"

void print_side_border(void);
void print_bottom_border(int length);
void print_spaces(int count);
void print_empty_line(int screen_length);

void print_title(const char* title, int screen_length);
void print_centered_text(char* text, int screen_length);
void print_left_aligned_text(char* text, int screen_length);

void print_content_subtitle(ContentAlignment contentAlignment, char** content, char** subtitle, int screen_length, int height);
void print_actions(const Action* actions, int actionsCount, int screen_length);
void print_error_msg(const char* errorMsg);


#endif
