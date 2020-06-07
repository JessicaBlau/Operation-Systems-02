
CC = gcc
FLAGS = -Wall -g

all:ipc.out

ipc.out:ipc.c ipc.h
	$(CC) $(FLAGS) -o ipc.out ipc.c ipc.h && ./ipc.out

clean:
	rm -f *.o ipc.out

