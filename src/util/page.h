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
} RenderedBlock;

typedef struct {
    int numBlocks;
    int *rowToRenderEveryBlock;
    RenderedBlock *blocks;
} RenderedBlocks;

typedef struct {
    const char *name; /**< The name of the page (e.g., "home", "adventure"). */
    /*Action actions[5];*/ /**< (Future feature) Array of actions available on the page. */
    RenderedBlocks *renderedBlocks; /**< Pointer to an array of RenderedBlocks. */
} Page;

/**
 * @brief Creates a RenderedBlocks structure to store multiple RenderedBlock elements.
 *
 * Allocates memory for a RenderedBlocks structure and its associated arrays.
 * The `rowToRenderEveryBlock` array is initialized using calloc to ensure zeroed values.
 *
 * @param numBlocks The number of blocks to allocate.
 * @return A pointer to the allocated RenderedBlocks structure, or NULL if allocation fails.
 */
RenderedBlocks *create_blocks (int numBlocks);

/**
 * @brief Adds a new block to an existing RenderedBlocks structure at a given index.
 *
 * Updates the RenderedBlock at the specified index and sets the display text.
 * Ensures that the memory for `renderedBlocks` is properly allocated before performing updates.
 * Assumes that blocks are added in correct order, if not render_page() will display incorrect behaviour.
 * If addition of new block goes over the SCREEN_HEIGHT, block will not be added.
 *
 * @param index The index where the block should be added.
 * @param renderedBlocks Pointer to the RenderedBlocks structure.
 * @param rowToRenderBlock The starting row where this block will be rendered.
 * @param numRows Number of rows in the block.
 * @param numCols Number of columns in the block.
 * @param displayText The text content to be displayed inside the block.
 */
void add_block_to_blocks(int index, RenderedBlocks *renderedBlocks, int rowToRenderBlock, int numRows, int numCols, DisplayStrings displayText);


/**
 * @brief Checks if the memory allocation for a RenderedBlocks structure was successful.
 *
 * Ensures that `renderedBlocks`, `blocks`, and `rowToRenderEveryBlock` are properly allocated.
 *
 * @param renderedBlocks Pointer to the RenderedBlocks structure.
 * @return 0 if memory is allocated correctly, 1 if there is a memory allocation failure.
 */
int check_memory_allocation_blocks(RenderedBlocks *renderedBlocks);

/**
 * @brief Frees memory allocated for a RenderedBlocks structure.
 *
 * Releases memory allocated for `blocks` and `rowToRenderEveryBlock`, followed by the `renderedBlocks` structure itself.
 *
 * @param renderedBlocks Pointer to the RenderedBlocks structure to be freed.
 */
void free_blocks(RenderedBlocks *renderedBlocks);

/**
 * @brief Creates a new Page structure and associates it with RenderedBlocks.
 *
 * Allocates memory for a Page structure and assigns the name and RenderedBlocks.
 * Ensures that the RenderedBlocks memory is allocated before proceeding.
 *
 * @param name The name of the page.
 * @param renderedBlocks Pointer to the associated RenderedBlocks structure.
 * @return A pointer to the allocated Page structure, or NULL if allocation fails.
 */
Page *create_page(char *name, RenderedBlocks *renderedBlocks);

/**
 * @brief Frees memory allocated for a Page structure.
 *
 * Frees the memory allocated for the `renderedBlocks` structure and then frees the `page` itself.
 *
 * @param page Pointer to the Page structure to be freed.
 */
void free_page(Page *page);

/**
 * @brief Renders a single RenderedBlock to the terminal.
 *
 * Iterates over the rows of the block and prints each row with left padding.
 * Future enhancements may allow additional formatting such as centered alignment.
 *
 * @param block Pointer to the RenderedBlock structure to be displayed.
 */
void render_block(RenderedBlock *block);

/**
 * @brief Renders all blocks in a RenderedBlocks structure.
 *
 * Ensures that each block is printed at its correct row position.
 * Inserts empty lines when necessary to maintain proper positioning.
 *
 * @param renderedBlocks Pointer to the RenderedBlocks structure to be displayed.
 */
void render_blocks(RenderedBlocks *renderedBlocks);

/**
 * @brief Clears the screen before rendering a page.
 *
 * Calls `render_blocks` to display the page's blocks.
 * Automatically frees the page after rendering to prevent memory leaks.
 *
 * @param page Pointer to the Page structure to be displayed.
 */
void render_page(Page *page);

/**
 * @brief Clears the terminal screen.
 *
 * Uses system calls to clear the screen based on the operating system.
 * Uses `cls` for Windows and `clear` for Linux/macOS.
 */
void clear_screen(void);

/**
 * @brief Calculates the actual width of a string when displayed.
 *
 * Converts a UTF-8 string to a wide-character string and determines the correct display width.
 * Ensures accurate spacing for rendering in terminal environments.
 *
 * @param str The UTF-8 encoded string.
 * @return The total display width of the string in terminal columns.
 */
int get_display_width(const char *str);

#endif
