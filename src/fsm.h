#ifndef FSM_H
#define FSM_H

typedef enum {
    STATE_HOME,
    STATE_ADVENTURE,
    STATE_POKEDEX,
    STATE_POKEMON,
    STATE_SAVE,
    STATE_EXIT
} State;

typedef struct {
    State currentState;
    int currentSubState;
    int errorState;
} FSM;

State fsm_getCurrentState(FSM* fsm);
int fsm_getCurrentSubState(FSM* fsm);
int fsm_getErrorState(FSM* fsm);

void fsm_init(FSM* fsm);
void fsm_updateState(FSM* fsm, State state, int subState, int errorState);

#endif
