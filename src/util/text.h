#ifndef TEXT_H
#define TEXT_H

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
 * Function: printBorder
 * ---------------------
 * Prints a styled horizontal border based on the given type and width.
 * 
 * Parameters:
 * - text: A string that specifies the border type.
 *         Accepts "top", "middle", or "bottom".
 * - width: The total width of the border to be printed.
 * 
 * Notes:
 * - "top" prints a solid underscore line.
 * - "middle" prints a dashed line enclosed in pipes (|----|).
 * - "bottom" prints a solid underscore line enclosed in pipes (|____|).
 */
void printBorder(const char *text, int width);

#endif

