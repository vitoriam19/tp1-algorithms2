CC := g++ --std=c++11
SRC_DIR := src
INC_DIR := includes
CFLAGS  := -Wall -Werror
all: tp.out

tp.out:	$(SRC_DIR)/suffixTree.o $(SRC_DIR)/match.o
	$(CC) $(CFLAGS) main.cpp $(SRC_DIR)/suffixTree.o $(SRC_DIR)/match.o -o tp.out -lm

$(SRC_DIR)/suffixTree.o: $(SRC_DIR)/suffixTree.cpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/suffixTree.cpp -o $(SRC_DIR)/suffixTree.o

$(SRC_DIR)/match.o: $(SRC_DIR)/match.cpp 
	$(CC) $(CFLAGS) -c $(SRC_DIR)/match.cpp -o $(SRC_DIR)/match.o

run:
	./tp.out

clean:
	rm $(SRC_DIR)/suffixTree.o
	rm $(SRC_DIR)/match.o
	rm ./tp.out