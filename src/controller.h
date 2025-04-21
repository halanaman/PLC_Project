#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "fsm.h"
#include "page.h"

typedef struct {
    FSM* fsm;
    int isRunning;
    int pokemonId;
    int pokedexPage;
} Controller;

void controller_init(Controller* controller, FSM* fsm);
Page* controller_getPage(Controller* controller);
void controller_handleInput(Controller* controller, const char* input);

#endif

