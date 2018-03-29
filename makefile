#macros
compile = g++
flags = -Wall -Werror -ansi -pedantic

all:
	mkdir -p ./bin
	$(compile) $(flag) ./src/*.cpp -o ./bin/rshell
	$(compile) $(flag) ./src/*.cpp -o ./rshell.out
clean:
	rm -rf ./bin