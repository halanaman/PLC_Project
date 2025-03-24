# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Werror -ansi -pedantic

# Executable name
TARGET = initialize

# Source files
SRCS = initialize.c file_io.c ../util/pokedex.c ../util/db.c
HEADERS = file_io.h ../util/pokedex.h ../util/pokemon.h ../util/db.h

# Object files (replace .c with .o)
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET) run clean

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)  # Runs the compiled program

# Clean target to remove compiled files
clean:
	rm -f $(OBJS) $(TARGET)
