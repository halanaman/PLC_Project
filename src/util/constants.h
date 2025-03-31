#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string.h>


#define SCREEN_HEIGHT 20
#define SCREEN_LENGTH 41 /* last character for new line, so functional screen length is 40*/
#define MAX_BLOCK_HEIGHT (SCREEN_HEIGHT - 2) /* inputs and error msgs takes up the last 2 rows */
#define SCREEN_LENGTH_BYTES 120
#define BLOCK_SIZE_BYTES (MAX_BLOCK_HEIGHT * SCREEN_LENGTH_BYTES) /* not used yet*/
#define MAX_MENU_INPUT_LENGTH 10

extern const char *LEFT_PADDING;

int snprintf_implement(char *buffer, size_t size, const char *format, ...);

#endif
