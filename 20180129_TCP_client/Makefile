# EPITA Practical Programming S3 - 2016/2017
#  Makefile
#  Marwan Burelle
 
#   Compilers and options
CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O2
LDFLAGS=
LDLIBS=
 
SRC = get_page.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
	 
all: get_page
	 
main: ${OBJ}
	 
-include ${DEP}
	  
clean:
	rm -f ${OBJ} ${DEP}
	rm -f get_page
			 
# END
