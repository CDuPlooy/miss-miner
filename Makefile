CC=clang
STD=c11
FLAGS=-Wall -Werror

compile: custom_io
	$(CC) --std=$(STD) $(FLAGS)  src/miss-miner.c build/custom_io.o -o build/a.out

custom_io:
	$(CC) --std=$(STD) $(FLAGS) -c src/custom_io.c -o build/custom_io.o



## END ##

run:
	build/a.out
