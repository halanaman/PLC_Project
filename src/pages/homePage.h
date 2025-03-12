#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "../util/page.h"
#include "../fsm.h"


typedef enum {
    ENTER_HOMEPAGE,
    LEAVE_HOMEPAGE
} HomePageState;


void run_home_page(AppState *currentState);

#endif
