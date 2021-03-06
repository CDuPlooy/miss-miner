CC=clang
STD=c11
FLAGS=-Wall -Werror -O0 -ggdb

compile: custom_io inject map vVector PE
	$(CC) --std=$(STD) $(FLAGS)  src/miss-miner.c build/PE.o build/vVector.o build/map.o build/custom_io.o build/inject.o -o build/a.out

custom_io:
	$(CC) --std=$(STD) $(FLAGS) -c src/custom_io.c -o build/custom_io.o

inject:
	$(CC) --std=$(STD) $(FLAGS) -c src/inject.c -o build/inject.o

map:
	$(CC) --std=$(STD) $(FLAGS) -c src/map.c -o build/map.o

vVector:
	$(CC) --std=$(STD) $(FLAGS) -c src/vVector.c -o build/vVector.o

PE:
	$(CC) --std=$(STD) $(FLAGS) -c src/PE.c -o build/PE.o

## END ##

run:
	@cd build && valgrind ./a.out -inject -target test.bin -output test.injected.bin -shellcode test.shell
