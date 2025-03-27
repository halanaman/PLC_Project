#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SCREEN_HEIGHT 20
#define SCREEN_LENGTH 30 /* not used yet*/
#define MAX_BLOCK_HEIGHT (SCREEN_HEIGHT - 2) /* inputs and error msgs takes up the last 2 rows */
#define SCREEN_LENGTH_BYTES 120
#define BLOCK_SIZE_BYTES (MAX_BLOCK_HEIGHT * SCREEN_LENGTH_BYTES) /* not used yet*/
#define MAX_MENU_INPUT_LENGTH 10

extern const char *LEFT_PADDING;

#endif
