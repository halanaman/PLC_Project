#ifndef PAGE_H
#define PAGE_H
#include "fsm.h"

typedef enum {
    STANDARD_PAGE,
    TYPING_PAGE
} PageType;

typedef enum {
    ALIGN_CENTER = 0,
    ALIGN_LEFT = 1
} ContentAlignment;

typedef struct {
    const char* key;
    const char* description;
} Action;

typedef struct {
    PageType pageType;
    ContentAlignment contentAlignment;
    const char* title;

    /* For TYPING_PAGE */
    const char*** typedScenes;
    int typedSceneCount;

    /* For STANDARD_PAGE */
    char** content;
    char** subtitle;

    const Action* actions;
    int actionsCount;
    const char* errorMsg;
} Page;

const char* getTitle(State state);
const char* getErrorMsg(int errorState);

Page* page_get(State state, int subState, int errorState, int screenWidth, int screenHeight);
void page_free(Page* page);

#endif
