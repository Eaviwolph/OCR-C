#ifndef OCRNEURALSYSTEM_H
#define OCRNEURALSYSTEM_h

#define INPUTS 784
#define HIDDEN 52
#define OUTPUT 52

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "XORNeuralSystem.h"

struct NeuralNetwork
{
    //Weights of each neurons
    double WeightItoH[INPUTS][HIDDEN];
    double dWeightItoH[INPUTS][HIDDEN];
    double WeightHtoO[HIDDEN][OUTPUT];
    double dWeightHtoO[HIDDEN][OUTPUT];
    //Biases of each neurons
    double BiasH[HIDDEN];
    double BiasO[OUTPUT];
    //activations of each neurons and delta to apply
    double ActH[HIDDEN];
    double deltaH[HIDDEN];
    double ActO[OUTPUT];
    double deltaO[OUTPUT];
    //learning rate
    double eta;
    //Inputs and desired Outputs
    double Input[INPUTS];
    double DesOut[OUTPUT];
};

char OCRTrain(struct NeuralNetwork* nn, char c);
char OCR(struct NeuralNetwork* nn);
struct NeuralNetwork *InitNewNetwork();

char CharToPlace(char c);
char PlaceToChar(char p);
char MaxChar(struct NeuralNetwork* nn, int output);

void SaveNeuralSystem(struct NeuralNetwork* nn, int output, int hidden, int input);
void InitInOut(struct NeuralNetwork* nn, int output);
void InitWeightItoH(struct NeuralNetwork* nn, int hidden, int input);
void InitWeightHtoO(struct NeuralNetwork* nn, int output, int hidden);
void InitBiasH(struct NeuralNetwork* nn, int hidden);
void InitBiasO(struct NeuralNetwork* nn, int output);
void Tabcopy(struct NeuralNetwork* nn, int tab[28][28]);

#endif
