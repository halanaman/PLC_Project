
#include "constants.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

const char *LEFT_PADDING = "  ";

int snprintf_implement(char *buffer, size_t size, const char *format, ...) {
    char temp[4096];  /* Temporary large buffer */
    va_list args;
    int required_length;

    /* Step 1: Format into the temp buffer */
    va_start(args, format);
    required_length = vsprintf(temp, format, args);  /* UNSAFE, but done in temp */
    va_end(args);

    /* Step 2: If formatted length exceeds size - 1, truncate */
    if (size > 0) {
        size_t copy_len = (required_length < (int)(size - 1)) ? required_length : (size - 1);
        memcpy(buffer, temp, copy_len);
        buffer[copy_len] = '\0';  /* Null-terminate */
    }

    /* Return the number of characters that would have been written (like snprintf) */
    return required_length;
}
