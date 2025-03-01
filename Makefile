CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic
TARGET = program
SRC = src/main.c

all: $(TARGET)
	./$(TARGET)  # Runs the compiled program automatically

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
