compiler    = gcc
flags       = -Wall -Werror -pedantic -std=c99 -O3
sources     = ./src/alcom.c
target_name = alcom

all: clean build

build: clean
	@mkdir -p ./build
	@${compiler} ${flags} ${sources} -o ./build/${target_name}

install: build 
	@sudo mv ./build/${target_name} /usr/bin

test: clean
	@mkdir -p ./build/tests
	@${compiler} ${flags} -DALCOM__TEST ${sources} ./tests/main.c -o ./build/tests/${target_name}
	@./build/tests/${target_name}

clean:
	@rm -rf ./build