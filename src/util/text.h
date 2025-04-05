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

#endif

