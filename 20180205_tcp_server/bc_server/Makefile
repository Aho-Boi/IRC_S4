# Makefile 

CC=gcc

CFLAGS= -Wall -Wextra -Werror -std=c99 -g

SRC1= bc_server.c
OBJ1= ${SRC1:.c=.o}

all: bc_server

test: ${OBJ1}

clean:
	rm -f *~ *.o
	rm -f echo_server
#END
