# Makefile
 
CC=gcc -fsanitize=address
CPPFLAGs=
CFLAGS= -Wall -Wextra -std=c99 -O2 -g -pthread
LDFLAGS=
LDLIBS= -lrt -lm
 
OBJ = server_v2.0.o ../RSA_version_2.0/primes.o ../RSA_version_2.0/rsa.o ../RSA_version_2.0/lnb.o
DEP = ${OBJ:.o=.d}


all: server_v2.0


server_v2.0: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} server_v2.0
	rm -f *~


# END
