CC=clang
STD=c11
FLAGS=-Wall -Werror -O0 -ggdb

compile: custom_io inject map vVector
	$(CC) --std=$(STD) $(FLAGS)  src/miss-miner.c build/vVector.o build/map.o build/custom_io.o build/inject.o -o build/a.out

custom_io:
	$(CC) --std=$(STD) $(FLAGS) -c src/custom_io.c -o build/custom_io.o

inject:
	$(CC) --std=$(STD) $(FLAGS) -c src/inject.c -o build/inject.o

map:
	$(CC) --std=$(STD) $(FLAGS) -c src/map.c -o build/map.o

vVector:
	$(CC) --std=$(STD) $(FLAGS) -c src/vVector.c -o build/vVector.o

## END ##

run:
	build/a.out
