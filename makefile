compiler    = gcc
flags       = -Wall -Werror -pedantic -Weverything -std=c99 -O3
sources     = ./src/alcom.c
target_name = alcom

all: build

build:
	@mkdir -p ./build
	@${compiler} ${flags} ${sources} -o ./build/${target_name}

install: build
	@sudo mv ./build/${target_name} /usr/bin
