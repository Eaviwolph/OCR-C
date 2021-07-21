#ifndef XORNEURALSYSTEM_H
#define XORNEURALSYSTEM_h

#define INPUTS 2
#define HIDDEN 5
#define OUTPUT 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct NeuralNetwork
{

    double WeightItoH[INPUTS*HIDDEN];
    double dWeightItoH[INPUTS*HIDDEN];
    double WeightHtoO[HIDDEN];
    double dWeightHtoO[HIDDEN];

    double BiasH[HIDDEN];
    double BiasO;

    double ActH[HIDDEN];
    double delta[HIDDEN];
    double ActO;
    double deltaO;

    double eta;
    double alpha;

    double Inputs[INPUTS*INPUTS*INPUTS];
    double Out[INPUTS*INPUTS];
};


void XORTrain();
double Random();
double sigmoid(double z);
double sigmoid_prime(double z);

#endif
