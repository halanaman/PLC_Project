#ifndef TEXT_H
#define TEXT_H

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

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

/**
 * Function: printCenteredTextToFile
 * --------------------------------
 * Prints text aligned to the center of the given width and writes it to a file.
 * 
 * Parameters:
 * - out: The file pointer where the text will be written.
 * - text: The string to be printed.
 * - width: The width to align the text within.
 */
void printCenteredTextToFile(FILE *out, const char *text, int width);

/**
 * Function: printWrappedTextToFile
 * -------------------------------
 * Prints wrapped text within the given width and writes it to a file.
 * 
 * Parameters:
 * - out: The file pointer where the text will be written.
 * - text: The string to be printed.
 * - width: The width constraint for wrapping.
 */
void printWrappedTextToFile(FILE *out, const char *text, int width);

/**
 * Function: printPokemonAsciiToFile
 * --------------------------------
 * Prints ASCII art of a Pokémon and writes it to a file.
 * 
 * Parameters:
 * - out: The file pointer where the ASCII art will be written.
 * - name: The name of the Pokémon.
 * - width: The display width for text alignment.
 */
void printPokemonAsciiToFile(FILE *out, const char *name, int width);

/**
 * Function: printBorderToFile
 * --------------------------
 * Prints a styled horizontal border to a file based on the given type and width.
 * 
 * Parameters:
 * - out: The file pointer where the border will be written.
 * - text: A string that specifies the border type.
 *         Accepts "top", "middle", or "bottom".
 * - width: The total width of the border to be printed.
 */
void printBorderToFile(FILE *out, const char *text, int width);

#endif

