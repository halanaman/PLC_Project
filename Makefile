# Compiler
CC = gcc
CFLAGS = -Wall -Werror -I./src/homePage -I./src/util/page
CFLAGS_ANSI = -ansi -pedantic $(CFLAGS)  # CFLAGS with -ansi (default)
# CFLAGS_ANSI = $(CFLAGS)  # CFLAGS with -ansi (default)

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC = src/main.c \
      src/fsm.c \
      src/pages/homePage.c \
      src/pages/pokedexPage.c \
      src/util/page.c \
      src/util/input.c \
      src/util/constants.c \
      src/util/db.c \
      src/util/pokedex.c

# Object files (convert .c to .o inside obj/)
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# Executable file
TARGET = pokedex.exe

# Default rule: Build everything with -ansi
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS_ANSI) $(OBJ) -o $(TARGET)

# Rule to compile each source file into object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/src/pages $(OBJ_DIR)/src/util  # Ensure obj directories exist
	$(CC) $(CFLAGS_ANSI) -c $< -o $@

# Clean-up rule
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run:
	./$(TARGET)  # Runs the compiled program

all: $(TARGET) run clean
