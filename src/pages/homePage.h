#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "../util/page.h"
#include "../fsm.h"


typedef enum {
    SHOW_HOMEPAGE,
    EXIT_HOMEPAGE
} HomePageState;


void run_home_page(AppStateStruct *appStateStruct);

#endif
