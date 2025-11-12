CC = g++
CFLAGS = -Wall -std=c++11
TARGET = BST
OBJ = BST.o

.PHONY: all run leak clean rebuild

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): BST.cpp
	$(CC) $(CFLAGS) -c BST.cpp

run: $(TARGET)
	./$(TARGET)

leak: $(TARGET)
	valgrind --leak-check=full --show-reachable=yes ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all
