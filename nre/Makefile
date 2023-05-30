# Makefile
.PHONY: all build run

all: build run

run: main
	./main test.nar

main: main.c
	gcc -W -Wall -std=c11 -g -pedantic main.c -o main

build: createNarFile
	./createNarFile

createNarFile: createNarFile.c
	gcc -W -Wall -std=c11 -g -pedantic createNarFile.c -o createNarFile