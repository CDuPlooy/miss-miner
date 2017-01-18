CC=clang
STD=c11
FLAGS=-Wall -Werror

compile:
	$(CC) --std=$(STD) $(FLAGS) src/miss-miner.c src/custom_io.c -o build/a.out
