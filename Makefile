# Compiler
CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -I./src/homePage -I./src/util/page

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC = src/main.c \
	  src/fsm.c \
      src/pages/homePage.c \
      src/util/page.c \
	  src/util/input.c \
	  src/util/constants.c

# Object files (convert .c to .o inside obj/)
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# Executable file
TARGET = pokedex.exe

# Default rule: Build everything
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Rule to compile each source file into object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/src/pages $(OBJ_DIR)/src/util  # Ensure obj directories exist
	$(CC) $(CFLAGS) -c $< -o $@

# Clean-up rule
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
