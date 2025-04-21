#Compiler
CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic
CFLAGS_ANSI = -ansi -pedantic $(CFLAGS)

# Directories
SRC_DIR = src
UTIL_DIR = utils
OBJ_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(UTIL_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h) $(wildcard $(UTIL_DIR)/*.h)

# Object files (inside build folder)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/$(SRC_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c)) \
       $(patsubst $(UTIL_DIR)/%.c,$(OBJ_DIR)/$(UTIL_DIR)/%.o,$(wildcard $(UTIL_DIR)/*.c))

# Executable name
TARGET = main

# Default target
all: $(TARGET)

# Default rule: Build everything with ansi
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS_ANSI) -o $(TARGET) $(OBJS)

# Compile src/ files
$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS_ANSI) -c $< -o $@

# Compile utils/ files
$(OBJ_DIR)/$(UTIL_DIR)/%.o: $(UTIL_DIR)/%.c $(HEADERS) | $(OBJ_DIR)/$(UTIL_DIR)
	$(CC) $(CFLAGS_ANSI) -c $< -o $@

# Create build directories
$(OBJ_DIR)/$(SRC_DIR) $(OBJ_DIR)/$(UTIL_DIR):
	mkdir -p $@

# Run the compiled program
run:
	./$(TARGET)

# Clean target to remove compiled files
clean:
	rm -f $(OBJS) $(TARGET)
-include $(OBJS:.o=.d)

# Phony targets (not actual files)
.PHONY: all run clean
