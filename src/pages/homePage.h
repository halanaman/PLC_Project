#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "../util/page.h"
#include "../fsm.h"
#include "../util/input.h"

typedef enum {
    SHOW_HOMEPAGE,
    EXIT_HOMEPAGE
} HomePageState;

/**
 * @brief Parses user input from the home page menu and updates the input state accordingly.
 *
 * This function processes user input and determines the next state of the application.
 * Depending on the user's input, it transitions to different application states such as 
 * the Pokédex, Adventure mode, or Save & Exit. If the input is invalid, the function sets 
 * an error state and remains on the home page.
 *
 * @param inputState Pointer to the InputState structure that manages user input state.
 * @param input User input string, expected to be a single-character selection.
 *
 * - "1" -> Moves to the Pokédex page.
 * - "2" -> Moves to the Adventure page.
 * - "3" -> Moves to the Save & Exit page.
 * - Any other input -> Marks input as invalid, remains on the home page with an error state.
 *
 * @note This function calls `update_input_state()` to modify the state accordingly.
 */
void home_page_menu_parser(InputState *inputState, char *input);

/**
 * @brief Creates and initializes the home page with rendered blocks.
 *
 * This function allocates memory and sets up the home page structure, including its rendered blocks.
 * It defines a block of text for display, representing the home page menu options.
 * 
 * The function follows these steps:
 * - Defines a `DisplayStrings` block containing the home page title and menu options.
 * - Allocates memory for `RenderedBlocks` to hold the blocks for the page.
 * - Adds a block (menu UI) to the `RenderedBlocks` structure.
 * - Initializes a `Page` structure with the home page name and associated blocks.
 * - If memory allocation fails at any point, it returns NULL and properly frees allocated memory.
 *
 * @return Pointer to the initialized `Page` structure if successful, or NULL on failure.
 *
 * @note The caller is responsible for freeing the allocated `Page` structure.
 *       You can do so by either using `free_page()`, or rendering the page using `render_page()`, 
 *       which also calls `free_page()` internally.
 */
Page *create_home_page(void);

/**
 * @brief Runs the home page state machine and processes user input.
 *
 * This function manages the home page's finite state machine (FSM), rendering the page and handling user interactions.
 * It follows these steps:
 * - Initializes an `InputState` structure to track user input and errors.
 * - Copies the starting state from `appStateStruct->nextStateNextAppState` to determine where to begin.
 * - Enters a loop where it processes different states of the home page sub-FSM.
 * - In the `SHOW_HOMEPAGE` state:
 *   - Creates and renders the home page.
 *   - If creation fails, transitions to `EXIT_HOMEPAGE` and updates the application state to `STATE_SAVE`.
 *   - Waits for user input and updates `homePageState` accordingly.
 *   - Updates `appStateStruct` before exiting `homePageState`.
 * - Exits when `homePageState` transitions to `EXIT_HOMEPAGE`.
 *
 * @param appStateStruct Pointer to `AppStateStruct` that tracks the application's current and next states.
 *
 */
void run_home_page(AppStateStruct *appStateStruct);

#endif
