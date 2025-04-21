#include <stdio.h>
#include <string.h>
#include "printhelper.h"

void print_side_border(void) {
    printf("│");
}

void print_bottom_border(int length) {
    /* Prints bottom border */
    /* └─────────────────────────────────────┘ */
    int i;
    printf("└");
    for (i = 0; i < length - 2; i++) { printf("─"); }
    printf("┘");
    printf("\n");
}

void print_spaces(int count) {
    int i;
    for (i = 0; i < count; i++) printf(" ");
}

void print_empty_line(int screen_length) {
    /* Prints an empty line with borders */
    /* │                                       │ */
    print_side_border();
    print_spaces(screen_length - 2);
    print_side_border();
    printf("\n");
}

void print_title(const char* title, int screen_length) {
    /* Print title in the center of the screen */
    int i, title_len, left_padding, right_padding, total_padding;

    title_len = strlen(title);
    total_padding = (screen_length - 4 - title_len < 0) ? 0 : screen_length - 4 - title_len;
    left_padding = total_padding / 2;
    right_padding = total_padding - left_padding;

    /* ┌───── Print The Title Like This ─────┐ */
    /* │                                     │ */
    printf("┌");
    for (i = 0; i < left_padding; i++)  { printf("─"); }
    printf(" %s ", title);
    for (i = 0; i < right_padding; i++) { printf("─"); }
    printf("┐\n");
    print_empty_line(screen_length);
}

void print_centered_text(char* text, int screen_length) {
    /* Prints a line of centered text with borders */
    /* │           some text here            │ */
    int line_length, total_padding, left_padding, right_padding;
    line_length = strlen(text);
    total_padding = screen_length - 2;
    left_padding = (total_padding - line_length) / 2;
    right_padding = total_padding - line_length - left_padding;

    print_side_border();
    print_spaces(left_padding);
    printf("%s", text);
    print_spaces(right_padding);
    print_side_border();
    printf("\n");
}

void print_left_aligned_text(char* text, int screen_length) {
    /* Prints a line of left-aligned text with borders */
    /* │ some text here                      │ */
    int line_length, total_padding, right_padding;
    line_length = strlen(text);
    total_padding = screen_length - 2;

    print_side_border();
    printf(" %s", text);
    right_padding = total_padding - line_length - 1;
    print_spaces(right_padding);    
    print_side_border();
    printf("\n");
}

void print_content_subtitle(ContentAlignment contentAlignment, char** content, char** subtitle, int screen_length, int height) {
    int content_line_count, subtitle_line_count, total_line_count;
    int top_padding, bottom_padding;
    int i;
    
    /* Count number of lines */
    content_line_count = 0;
    subtitle_line_count = 0;
    if (content) {
        while (content[content_line_count] != NULL) { 
            content_line_count++;
       }
    }
    if (subtitle) {
        while (subtitle[subtitle_line_count] != NULL) {
            subtitle_line_count++;
        }
    }
    
    /* Add one line in between content and subtitle */
    total_line_count = content_line_count + subtitle_line_count + 1;
    top_padding = ((height - total_line_count) < 0) ? 0 : (height - total_line_count) / 2;
    bottom_padding = (height - total_line_count - top_padding) < 0 ? 0 : (height - total_line_count - top_padding);

    /* Print top padding */
    for (i = 0; i < top_padding; i++) { print_empty_line(screen_length); }
    
    /* Print content */
    for (i = 0; i < content_line_count; i++) {
        switch (contentAlignment) {
            case ALIGN_LEFT:
                print_left_aligned_text(content[i], screen_length);
                break;
            case ALIGN_CENTER:
                print_centered_text(content[i], screen_length);
                break;
        }
    }
    /* One empty line between content and subtitle */
    print_empty_line(screen_length);
    /* Print subtitle */
    if (subtitle) {
        for (i = 0; i < subtitle_line_count; i++) {
            print_centered_text(subtitle[i], screen_length);
        }
    }
    /* Print bottom padding*/
    for (i = 0; i < bottom_padding; i++) { print_empty_line(screen_length); }
}

void print_actions(const Action* actions, int actionsCount, int screen_length) {
    /* Print centered box of actions
    │     ┌────────────────────┐     │
    │     │ 1: View Pokedex    │     │
    │     │ 2: Start Adventure │     │
    │     │ 3: Settings        │     │
    │     │ s: Save & Exit     │     │
    │     └────────────────────┘     │ */
    int line_length, max_line_length, key_length, max_key_length;
    int box_width;
    int total_padding, left_padding, right_padding;
    int i;

    /* Do nothing if there are no actions */
    if (actionsCount <= 0) {
        return;
    }

    line_length = 0;
    max_key_length = 0;
    max_line_length = 0;

    /* Calculate required box width */
    for (i = 0; i < actionsCount; i++) {
        key_length = strlen(actions[i].key);
        line_length = key_length + strlen(actions[i].description);
        if (line_length > max_line_length) {
            max_line_length = line_length;
        }
        if (key_length > max_key_length) {
            max_key_length = key_length;
        }
    }
    box_width = max_line_length + 6;
    
    total_padding = screen_length - 2;
    left_padding = (total_padding - box_width) / 2;
    right_padding = total_padding - box_width - left_padding;

    /* Print top of the box */
    /* │     ┌────────────────────┐     │ */
    print_side_border();
    print_spaces(left_padding);
    printf("┌");
    for (i = 0; i < box_width - 2; i++) printf("─");
    printf("┐");
    print_spaces(right_padding);
    print_side_border();
    printf("\n");

    /* Print actions inside box */
    /* │     │ 1: View Pokedex    │     │ */
    for (i = 0; i < actionsCount; i++) {
        print_side_border();
        print_spaces(left_padding);
        print_side_border();

        key_length = strlen(actions[i].key);
        print_spaces(1 + max_key_length - key_length);
        printf("%s: %s", actions[i].key, actions[i].description);
        print_spaces(box_width - 5 - key_length - strlen(actions[i].description));

        print_side_border();
        print_spaces(right_padding);
        print_side_border();
        printf("\n");
    }

    /* Print bottom of the box */
    /* │     └────────────────────┘     │ */
    print_side_border();
    print_spaces(left_padding);

    printf("└");
    for (i = 0; i < box_width - 2; i++) { printf("─"); }
    printf("┘");

    print_spaces(right_padding);
    print_side_border();
    printf("\n");
}

void print_error_msg(const char* errorMsg) {
    if (errorMsg) {
        printf("Error: %s\n", errorMsg);
    }
    else {
        printf("\n");
    }
}

