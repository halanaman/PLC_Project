#include <stdio.h>
#include "fsm.h"
#include "utils/db.h"

State fsm_getCurrentState(FSM* fsm)     { return fsm->currentState; }
int fsm_getCurrentSubState(FSM* fsm)    { return fsm->currentSubState; }
int fsm_getErrorState(FSM* fsm)         { return fsm->errorState; }

void fsm_init(FSM* fsm) {
    fsm->currentState = STATE_HOME;
    fsm->currentSubState = 0;
    fsm->errorState = 0;
}

void fsm_updateState(FSM* fsm, State state, int subState, int errorState) {
    fsm->currentState = state;
    fsm->currentSubState = subState;
    fsm->errorState = errorState;
}

