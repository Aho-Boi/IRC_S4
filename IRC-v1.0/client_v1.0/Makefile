# Makefile
 
CC=gcc -fsanitize=address
CPPFLAGs=
CFLAGS= -Wall -Wextra -std=c99 -O2 -g -pthread
LDFLAGS=
LDLIBS= -lrt -lm

OBJ = Client_Retarded_IRC.o ../RSA_version_2.0/primes.o ../RSA_version_2.0/rsa.o ../RSA_version_2.0/lnb.o
DEP = ${OBJ:.o=.d}


all: Client_Retarded_IRC
 
Client_Retarded_IRC: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} Client_Retarded_IRC
	rm -f *~
 
# END
