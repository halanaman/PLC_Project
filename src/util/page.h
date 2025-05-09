#ifndef PAGE_H
#define PAGE_H

#include "pokedex.h"

#define POKEMON_ROW 10      /** Number of Pokemon rows per page */
#define POKEMON_PER_PAGE 20 /** Number of Pokemon displayed per page */
#define PAGE_WIDTH 50
#define CARD_WIDTH 100

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
 * - numOptions: Number of available options.
 * - width: Display width for text alignment.
 */
typedef struct {
    PageState currentState; /** Current Page State */
    const char *options[6]; /** List of options (up to 6) */
    int numOptions;        /** Number of Available Options */
    int width;              /** Display width for text alignment */
} PageOptions;

/**
 * Function: clearScreen
 * ----------------------
 * Clears the console screen based on the operating system.
 */
void clearScreen(void);

/**
 * Function: printOptions
 * -----------------------
 * Prints the available menu options for the given page.
 * 
 * Parameters:
 * - state: The current page state to determine available options.
 */
void printOptions(PageState state);

/**
 * Function: printMenuPage
 * -----------------------
 * Displays the welcome menu screen.
 */
void printMenuPage(void);

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
 * Function: printCardViewPage
 * -----------------------
 * Displays a detailed card view of a Pokémon with its status and ASCII art.
 * 
 * Parameters:
 * - pokemon: Pointer to the Pokémon to be displayed.
 * - pokemonSeen: Pointer to an item that determines if the Pokémon has been seen.
 */
void printCardViewPage(Pokemon *pokemon, PokedexListItem *pokemonSeen);

/**
 * Function: saveCardViewPage
 * ---------------------------
 * Saves the card view of a Pokémon to a file.
 * This includes the Pokémon's name, type, stats, description,
 * and ASCII art (if available). The output is formatted to look like a 
 * Pokémon card.
 *
 * Parameters:
 * - out: The file pointer where the card view will be saved.
 * - pokemon: Pointer to the Pokémon to be saved.
 */
void saveCardViewPage(FILE *out, Pokemon *pokemon);

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
 * Function: updatePageState
 * ---------------------------
 * Handles user input to change the PageState and update the display accordingly.
 * 
 * Parameters:
 * - page: Pointer to the Page structure managing the game's current page.
 * - pokedex: Pointer to the Pokedex structure for displaying Pokémon.
 * - input: User input string that determines the next action.
 */
void updatePageState(Page *page, Pokedex *pokedex, char *input);

#endif


