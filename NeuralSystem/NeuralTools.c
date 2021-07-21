#include "XORNeuralSystem.h"

double Random()
{
    return (double)rand() / (double)RAND_MAX;
}

double sigmoid(double z)
{
    return(1.0 / (1.0 + exp(-z)));
}
double sigmoid_prime(double z)
{
    return((z)*(1-(z)));
}
