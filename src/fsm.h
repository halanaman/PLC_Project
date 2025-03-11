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

void handle_state(AppState *currentState);

#endif
