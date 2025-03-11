#include <stdio.h>
#include "input.h"

/*
    while (1) {
        printf("\nEnter a command (or type 'exit' to quit): ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("\nExiting home page...\n");
            break;
        }

        printf("You entered: %s\n", input);
    }
        */

/**
 * 
 * should we use fget instead?
 */
int get_user_input(void) {
    int choice;
    while (1) {
        if (scanf("%d", &choice) == 1) break;
        while (getchar() != '\n');  /* Clear input buffer*/
        printf("Invalid input, try again: ");
    }
    return choice;
}
