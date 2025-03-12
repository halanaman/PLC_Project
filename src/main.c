
#include "fsm.h"

/* Main function: entry point for execution */
int main(int argc, char ** argv)
{
    AppState currentState = STATE_HOME;
    run_main_fsm(&currentState);
    return 0;
}

