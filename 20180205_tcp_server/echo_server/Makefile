# Makefile 

CC=gcc

CFLAGS= -Wall -Wextra -Werror -std=c99 -g

SRC1= echo_server.c
OBJ1= ${SRC1:.c=.o}

all: echo_server

test: ${OBJ1}

clean:
	rm -f *~ *.o
	rm -f echo_server
#END
