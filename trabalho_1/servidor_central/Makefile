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
	bin/prog $(ip) $(porta_1) $(porta_2) $(porta_3) $(porta_4)
.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*
roda: 
	make clean 
	make all 
	clear
	make run  ip=127.0.0.1 porta_1=10161 porta_2=10165 porta_3=10167 porta_4=10169
