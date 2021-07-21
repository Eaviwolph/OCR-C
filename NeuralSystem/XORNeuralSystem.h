#ifndef XORNEURALSYSTEM_H
#define XORNEURALSYSTEM_h

#define XORINPUTS 2
#define XORHIDDEN 5
#define XOROUTPUT 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

struct XORNeuralNetwork
{
    //Weights of each neurons
    double WeightItoH[XORINPUTS*XORHIDDEN];
    double dWeightItoH[XORINPUTS*XORHIDDEN];
    double WeightHtoO[XORHIDDEN];
    double dWeightHtoO[XORHIDDEN];
    //Biases of each neurons
    double BiasH[XORHIDDEN];
    double BiasO;
    //activations of each neurons and delta to apply
    double ActH[XORHIDDEN];
    double delta[XORHIDDEN];
    double ActO;
    double deltaO;
    //learning rate
    double eta;
    //XORINPUTS and desired Outputs
    double Inputs[XORINPUTS*XORINPUTS*XORINPUTS];
    double Out[XORINPUTS*XORINPUTS];
};


void XORTrain();
double Random();
double Sigmoid(double z);
double Sigmoid_prime(double z);

#endif
