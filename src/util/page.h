#ifndef PAGE_H
#define PAGE_H

#include "constants.h"

/**
 * @typedef DisplayStrings
 * @brief Defines a fixed-size 2D array to store multiple lines of text.
 *
 * DisplayStrings is used to store formatted text that can be displayed on a 
 * screen. Each entry represents a single line, and the total number of 
 * entries should not exceed `MAX_BLOCK_HEIGHT`. Each line is a fixed-length 
 * character array, ensuring that text remains within the constraints of 
 * `SCREEN_LENGTH_BYTES`.
 * 
 * We need at least 3 * SCREEN_LENGTH of bytes to store SCREEN_LENGTH number of characters, due to the way c handles non-ascii characters.
 *
 * @note - `MAX_BLOCK_HEIGHT` defines the maximum number of lines.
 * @note - `SCREEN_LENGTH_BYTES` defines the maximum size of string per line.
 * @note - This type is primarily used within `RenderedBlock` to store the block's text content.
 */
typedef char DisplayStrings[MAX_BLOCK_HEIGHT][SCREEN_LENGTH_BYTES];

/**
 * @struct RenderedBlock
 * @brief Represents a block of text that can be displayed on a page.
 *
 * A RenderedBlock consists of multiple lines of text, where each line has 
 * a defined maximum width. It is designed to hold formatted text for 
 * display purposes, such as UI components or informational blocks.
 *
 * @note - `numRows` should not exceed `MAX_BLOCK_HEIGHT`.
 * @note - `numCols` should not exceed `SCREEN_LENGTH_BYTES`.
 * @note - `displayedText` can store up to 30 strings, each with a maximum of 100 bytes.
 */
typedef struct{
    int numRows; /*numRows should not exceed MAX_BLOCK_HEIGHT*/
    int numCols; /*numCOls should not exceed SCREEN_LENGTH_BYTES*/
    DisplayStrings displayedText; /*can store up to 30 strings of 100bytes each*/
    /*struct RenderedBlock *renderedBlocks; //disabling this to reduce complexity. */
} RenderedBlock;

/**
 * @struct Page
 * @brief Represents a navigable page that contains one or more RenderedBlocks.
 *
 * A Page serves as a container for multiple RenderedBlocks, allowing the 
 * creation of structured views, such as menu screens or informational pages.
 *
 * @note - `renderedBlocks` is an array of dynamically allocated RenderedBlocks.
 * @note - `numBlocks` specifies the number of blocks contained within the Page.
 */
typedef struct {
    const char *name; /**< The name of the page (e.g., "home", "adventure"). */
    /*Action actions[5];*/ /**< (Future feature) Array of actions available on the page. */
    RenderedBlock *renderedBlocks; /**< Pointer to an array of RenderedBlocks. */
    int numBlocks; /**< Number of blocks in the page. */
} Page;

RenderedBlock *create_rendered_block(int numRows, int numCols, DisplayStrings displayText);
Page *create_page(char *name, int numBlocks,RenderedBlock *blocks);

void free_page(Page *page);

void render_block(RenderedBlock *block);
void render_page(Page *page);
void clear_screen(void);

int get_display_width(const char *str);

#endif
