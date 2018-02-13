# Makefile
 
# CC=clang -fsanitize=address
# CC=gcc -fsanitize=address
CC=gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -O0 -g3
LDFLAGS=
LDLIBS= -lrt -lm

OBJ = primes.o rsa.o
DEP = ${OBJ:.o=.d}
 
all: rsa

rsa: ${OBJ}
 
clean:
	${RM} ${OBJ} ${DEP} rsa
	rm -f *~

# END
