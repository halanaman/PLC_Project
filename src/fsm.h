#ifndef FSM_H
#define FSM_H

typedef enum {
    STATE_HOME,
    STATE_POKEDEX,
    STATE_ADVENTURE,
    STATE_SAVE,
    STATE_EXIT
} AppState;

void init_fsm(void);

void run_main_fsm(AppState *currentState);

#endif
