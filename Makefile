# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -Wextra -std=c99 -O0 -g 
LDFLAGS =
LDLIBS = `pkg-config --libs gtk+-3.0` `sdl2-config --cflags --libs` -lSDL_image -lm

OBJ = CharDetector/CharBlockDetector.o UI/ui.o IMGtreatment/LoadIm.o NeuralSystem/NeuralTools.o NeuralSystem/XORNeuralSystem.o NeuralSystem/OCRNeuralSystem.o main.o
DEP = ${OBJ:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} main

-include ${DEP}

# END
