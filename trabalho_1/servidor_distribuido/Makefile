# Executable
BINFOLDER := bin/
# .hppz
INCFOLDER := inc/
# .c
SRCFOLDER := src/
# .o
OBJFOLDER := obj/
CC := gcc
CFLAGS := -W -Wall -ansi -lwiringPi -lpthread  -std=gnu11 -Wimplicit-function-declaration -Wunused-parameter -Wunused-variable -Wunused-parameter 
SRCFILES := $(wildcard src/*.c)
all: $(SRCFILES:src/%.c=obj/%.o)
	$(CC) $(CFLAGS) obj/*.o -o bin/prog
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I./inc
run:  bin/prog  
	bin/prog $(porta) $(ip)
.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*

roda: 
	make clean 
	make all 
	make run porta=10165 ip=127.0.0.1