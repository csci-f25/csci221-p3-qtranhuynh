CC = g++
CFLAGS = -Wall -std=c++11
TARGET = BST
OBJ = BST.o

.PHONY: all run clean rebuild

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): BST.cpp
	$(CC) $(CFLAGS) -c BST.cpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all
