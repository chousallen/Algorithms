CC = g++
OPTFLAGS = -O3 -std=c++11
OBJ = ./binary_heap.o

all: ./bin/cb
	@echo -n ""

./bin/cb: ./bin/$(OBJ)
	$(CC) $(OPTFLAGS) ./src/main.cpp ./bin/$(OBJ) -o ./bin/cb
	rm -rf ./bin/*.o

./bin/%.o: ./src/%.cpp
	$(CC) $(OPTFLAGS) $< -c -o $@

clean:
	rm -rf *.o bin/*