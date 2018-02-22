
CC=gcc
CPPFLAGS = -MMD -D_XOPEN_SOURCE=500 `pkg-config --cflags gtk+-3.0 pkg-config --cflags sdl`

CFLAGS= -Wall -Wextra -g -std=c99
LDFLAGS = -lm
LDLIBS= `pkg-config --libs sdl pkg-config --libs gtk+-3.0` -lSDL_image -lm -export-dynamic -lSDL_ttf


SRC = Ignite.c 
OBJ = Ignite.o

DEP= ${SRC.c=.d}

all: Ignite

-include ${DEP}

Ignite: ${OBJ}
clean:
	rm -f ${DEP} ${OBJ} mm *~ *.d Ignite
