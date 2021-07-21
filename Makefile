# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS = -lm `sdl2-config --cflags --libs` -lSDL_image

OBJ = CharDetector/CharBlockDetector.o IMGtreatment/LoadIm.o NeuralSystem/NeuralTools.o NeuralSystem/XORNeuralSystem.o main.o
DEP = ${OBJ:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} main

-include ${DEP}

# END
