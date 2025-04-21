#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fsm.h"
#include "controller.h"
#include "view.h"
#include "page.h"

int main(int argc, char ** argv)
{
    FSM fsm;
    Controller controller;
    View view;

    fsm_init(&fsm);
    controller_init(&controller, &fsm);
    view_init(&view, &controller);

    return 0;
}

