# miss-miner
A hobbyist tool for injecting code into PE files.
Reinventing the wheel is fun! :D

# Usage:
Inside the build directory try the following.

````shell
./a.out -inject -target test.bin -output test.injected.bin -shellcode test.shell
````

Miss-miner can also recalculate the checksum of portable executables.

````shell
./a.out -recheck -target test.injected.bin
````
