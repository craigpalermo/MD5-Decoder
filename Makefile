CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -g

all: permute.x

permute.x: permute.o md5.o
	$(CC) permute.o md5.o -o permute.x

permute.o: permute.c md5.c
	$(CC) $(CFLAGS) -c permute.c

md5.o: md5.c
	$(CC) $(CFLAGS) -c md5.c

clean:
	rm permute.x permute.o md5.o