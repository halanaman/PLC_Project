#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "page.h"

/**
 * @brief Creates and initializes a new RenderedBlock structure.
 * 
 * Allocates memory for a new RenderedBlock and initializes its dimensions 
 * and displayed text. If memory allocation fails, the function returns NULL.
 * 
 * @param numRows Number of text rows in the block.
 * @param numCols Maximum width of each text row.
 * @param displayText A 2D array (DisplayStrings) containing the text to display.
 * @return Pointer to the newly allocated RenderedBlock, or NULL if allocation fails.
 */
RenderedBlock *create_rendered_block(int numRows, int numCols, DisplayStrings displayText) {
    int i;
    RenderedBlock *block = malloc(sizeof(RenderedBlock));
    if (!block) return NULL;

    block->numRows = numRows;
    block->numCols = numCols;
    for (i = 0; i < numRows; i++) {
        strcpy(block->displayedText[i], displayText[i]);
    }
    return block;
}

/**
 * @brief Creates and initializes a new Page structure.
 * 
 * Allocates memory for a new Page and initializes its name, number of blocks, 
 * and rendered blocks. If memory allocation fails, the function returns NULL.
 * 
 * Future: Have not taken in account Page.actions yet 
 * 
 * @param name Name of the page.
 * @param numBlocks Number of rendered blocks in the page.
 * @param blocks Pointer to an array of RenderedBlock structures.
 * @return Pointer to the newly allocated Page, or NULL if allocation fails.
 */
Page *create_page(char *name, int numBlocks, RenderedBlock *blocks) {
    Page *page = malloc(sizeof(Page));
    if (!page) return NULL;

    page->name = name;
    page->numBlocks = numBlocks;
    page->renderedBlocks = blocks;
    return page;
}

/**
 * @brief Frees the memory allocated for a Page structure.
 * 
 * This function releases the memory allocated for the page and its associated 
 * rendered blocks. If the page is NULL, the function does nothing.
 * 
 * @param page Pointer to the Page structure to free.
 */
void free_page(Page *page) {
    if (page) {
        free(page->renderedBlocks);
        free(page);
    }
}


/*
Future: Can add in functionality to add padding on both sides
*/
void render_block(RenderedBlock *block) {
    int i;
    for (i = 0; i < block->numRows; i++) {
        /*
        int displayWidth = get_display_width(block.displayedText[i]);
        if (displayWidth > maxWidth) {
            maxWidth = displayWidth; // Store the maximum width found
        }
        */
        printf("%s%s", LEFT_PADDING , block->displayedText[i]);
    }
}

/**
 * @brief Renders the given page by clearing the screen and displaying its blocks.
 * 
 * If the page is NULL, the function does nothing. Otherwise, it clears the screen
 * and iterates through the blocks of the page, rendering each one.
 * 
 * Future: Can add in functionality to add space between blocks
 * 
 * @param page Pointer to the Page structure to render.
 */
void render_page(Page *page) {
    int i;
    if (!page) return;
    clear_screen();
    for (i = 0; i < page->numBlocks; i++) {
        render_block(&page->renderedBlocks[i]);
    }
}

void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int get_display_width(const char *str) {
    int i, w, width;
    wchar_t wideStr[100];   /*Temporary buffer*/
    setlocale(LC_ALL, "");  /*Enable UTF-8 handling*/
    mbstowcs(wideStr, str, 100); /*Convert UTF-8 string to wide characters*/

    width = 0;
    for (i = 0; wideStr[i] != L'\0'; i++) {
        w = wcwidth(wideStr[i]);
        if (w > 0) width += w;  /*Count only valid display characters*/
    }
    return width;
}
