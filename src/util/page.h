#ifndef PAGE_H
#define PAGE_H

#include "pokedex.h"

#define POKEMON_ROW 10      /** Number of Pokemon rows per page */
#define POKEMON_PER_PAGE 20 /** Number of Pokemon displayed per page */

/**
 * Enum: PageState
 * ---------------
 * Represents the different pages/screens in the Pokédex game.
 */
typedef enum {
    MENU,               /** Main Menu Page */
    POKEDEX,            /** Pokedex List Page */
    CARDVIEW,           /** Individual Pokemon Card View */
    ADVENTURE,          /** Adventure Mode Page */
    ADVENTURE_SUCCESS,  /** Adventure Success Screen */
    ADVENTURE_FAIL,     /** Adventure Fail Screen */
    SAVE                /** Save Game Page */
} PageState;

/**
 * Struct: Page
 * ------------
 * Stores the current state of the game, including:
 * - currentState: The currently active page.
 * - pokedexPage: The current page number in the Pokédex view.
 * - cardViewIdx: The index of the selected Pokémon in CardView.
 */
typedef struct {
    PageState currentState; /** Current Page State */
    int pokedexPage;        /** Current Pokedex Page Number */
    int cardViewIdx;        /** Index of the selected Pokemon in CardView */
} Page;

/**
 * Struct: PageOptions
 * -------------------
 * Stores available options for a given page.
 * - currentState: The page this set of options belongs to.
 * - options: List of menu options as strings.
 * - num_options: Number of available options.
 * - width: Display width for text alignment.
 */
typedef struct {
    PageState currentState; /** Current Page State */
    const char *options[6]; /** List of options (up to 6) */
    int num_options;        /** Number of Available Options */
    int width;              /** Display width for text alignment */
} PageOptions;

/**
 * Function: clear_screen
 * ----------------------
 * Clears the console screen based on the operating system.
 */
void clear_screen();

/**
 * Function: printCenteredText
 * ---------------------------
 * Prints text aligned to the center of the given width.
 * 
 * Parameters:
 * - text: The string to be printed.
 * - width: The width to align the text within.
 */
void printCenteredText(const char *text, int width);

/**
 * Function: printLeftAlignedText
 * ------------------------------
 * Prints text aligned to the left within the given width.
 * 
 * Parameters:
 * - text: The string to be printed.
 * - width: The width to align the text within.
 */
void printLeftAlignedText(const char *text, int width);

/**
 * Function: printWrappedText
 * --------------------------
 * Prints text wrapped within the given width.
 * 
 * Parameters:
 * - text: The string to be printed.
 * - width: The width constraint for wrapping.
 */
void printWrappedText(const char *text, int width);

/**
 * Function: print_options
 * -----------------------
 * Prints the available menu options for the given page.
 * 
 * Parameters:
 * - state: The current page state to determine available options.
 */
void print_options(PageState state);

/**
 * Function: printMenuPage
 * -----------------------
 * Displays the welcome menu screen.
 */
void printMenuPage();

/**
 * Function: printPokedexPage
 * --------------------------
 * Displays the list of Pokémon, marking whether they have been seen.
 * 
 * Parameters:
 * - pokedex: Pointer to the Pokedex structure.
 * - page: The current page number of the Pokédex list.
 */
void printPokedexPage(Pokedex *pokedex, int page);

/**
 * Function: printPokemonAscii
 * ---------------------------
 * Prints ASCII art of a Pokémon.
 * 
 * Parameters:
 * - name: The name of the Pokémon.
 * - width: The display width for text alignment.
 */
void printPokemonAscii(const char *name, int width);

/**
 * Function: printCardView
 * -----------------------
 * Displays a detailed card view of a Pokémon with its status and ASCII art.
 * 
 * Parameters:
 * - pokemon: Pointer to the Pokémon to be displayed.
 * - pokemonSeen: Pointer to an item that determines if the Pokémon has been seen.
 */
void printCardView(Pokemon *pokemon, PokedexListItem *pokemonSeen);

/**
 * Function: printAdventurePage
 * ----------------------------
 * Displays the adventure page where the player embarks on a journey.
 * 
 * Parameters:
 * - page: Pointer to the Page structure managing the game's current page.
 * - pokedex: Pointer to the Pokedex structure for displaying Pokémon.
 */
void printAdventurePage(Page *page, Pokedex *pokedex);

/**
 * Function: update_page_state
 * ---------------------------
 * Handles user input to change the PageState and update the display accordingly.
 * 
 * Parameters:
 * - page: Pointer to the Page structure managing the game's current page.
 * - pokedex: Pointer to the Pokedex structure for displaying Pokémon.
 * - input: User input string that determines the next action.
 */
void update_page_state(Page *page, Pokedex *pokedex, char *input);

#endif


