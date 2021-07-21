#ifndef CharBlockDetector_H
#define CharBlockDetector_h

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../NeuralSystem/OCRNeuralSystem.h"
int CharDetector(int lines, int columns, int image[lines][columns], char* torecognize, char* buffer);
#endif
