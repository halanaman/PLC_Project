
#include "fsm.h"
#include "pages/homePage.h"

/* Main function: entry point for execution */
int main(int argc, char ** argv)
{
    AppStateStruct appStateStruct = {
        .nextAppState = STATE_HOME,
        .nextStateNextAppState = SHOW_HOMEPAGE
    };
    run_main_fsm(&appStateStruct);
    return 0;
}

