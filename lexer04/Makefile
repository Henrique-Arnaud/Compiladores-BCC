# Makefile
.PHONY: all build run

all: build run

run: main
	./main teste.prg

build: main

main: main.c
	gcc -W -Wall -std=c11 -g -pedantic main.c -o main
