
#include "fsm.h"

/* Main function: entry point for execution */
int main(int argc, char ** argv)
{
    AppState currentState = STATE_HOME;
    handle_state(&currentState);
    return 0;
}

