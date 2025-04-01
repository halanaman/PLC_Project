#ifndef ADVENTUREPAGE_H
#define ADVENTUREPAGE_H

#include "../util/page.h"
#include "../util/adventure.h"
#include "../fsm.h"
#include "../util/input.h"

typedef enum {
    SHOW_ADVPAGE,
    SHOW_POKEMON_ENCOUNTERED,
    SHOW_NOTHING_ENCOUNTERED,
    EXIT_ADVPAGE
} AdvPageState;

void initialize_adv_page_data(InputState *inputState);

void adv_page_parser(InputState *inputState, char *input);

Page *create_adv_page(void);

void pokemon_encountered_page_parser(InputState *inputState, char *input);
void nothing_encountered_page_parser(InputState *inputState, char *input);

void run_adv_page(AppStateStruct *appStateStruct);

#endif
