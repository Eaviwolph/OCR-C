#include "XORNeuralSystem.h"
//Initialisation of the XORNeuralNetwork
struct XORNeuralNetwork InitalizeNetwork()
{
    struct XORNeuralNetwork nn;
    nn.eta = 3;
    //InitValues
    for (int i = 0; i < XORINPUTS; i++)
    {
        for (int j = 0; j < XORHIDDEN; j++)
        {
            nn.WeightItoH[j + i*XORHIDDEN] = Random();
            nn.dWeightItoH[j + i*XORHIDDEN] = 0.0;
        }
    }
    for (int i = 0; i < XORHIDDEN; i++)
    {
        nn.WeightHtoO[i] = Random(); // Weights of the Hiddens are ramdomized
        nn.dWeightHtoO[i] = 0.0;
        nn.BiasH[i] = Random(); // Bias of the Hiddens are randomized
    }
    // Set Inputs and Outputs
    nn.Inputs[0] = 0; nn.Inputs[1] = 0; nn.Out[0] = 0;
    nn.Inputs[2] = 0; nn.Inputs[3] = 1; nn.Out[1] = 1;
    nn.Inputs[4] = 1; nn.Inputs[5] = 0; nn.Out[2] = 1;
    nn.Inputs[6] = 1; nn.Inputs[7] = 1; nn.Out[3] = 0;
    return(nn);
}

//Process all activations and so the output
static void feedforward(struct XORNeuralNetwork* nn, int x)
{
    double Sum = 0.0;
    for (int j = 0; j < XORHIDDEN; j++) // For each Hidden
    {
        Sum = 0;
        for (int i = 0; i < XORINPUTS; i++) // For each Inputs
        {
            Sum += (*nn).WeightItoH[j + i*XORHIDDEN] * (*nn).Inputs[i + x*XORINPUTS];
        }
        (*nn).ActH[j] = Sigmoid(Sum + (*nn).BiasH[j]);
    }
    Sum = 0.0;
    for (int j = 0; j < XORHIDDEN; j++)
    {
        Sum += (*nn).WeightHtoO[j] * (*nn).ActH[j];
    }
    (*nn).ActO = Sigmoid(Sum + (*nn).BiasO);
}

//Update Weights and Biases
static void updateBW(struct XORNeuralNetwork* nn, int x)
{
    (*nn).BiasO += (*nn).eta * (*nn).deltaO;
    for (int j = 0; j < XORHIDDEN; j++)
    {
        (*nn).BiasH[j] += (*nn).eta * (*nn).delta[j];
        for (int i = 0; i < XORINPUTS; i++)
        {
            (*nn).dWeightItoH[j + i * XORHIDDEN] = (*nn).eta *
                (*nn).Inputs[i + x * XORINPUTS] * (*nn).delta[j];

            (*nn).WeightItoH[j + i*XORHIDDEN] += (*nn).dWeightItoH[j + i*XORHIDDEN];
        }
        (*nn).dWeightHtoO[j] = (*nn).eta * (*nn).ActH[j] * (*nn).deltaO;
        (*nn).WeightHtoO[j] += (*nn).dWeightHtoO[j];
    }
}
//Process all delta to apply on updates
static void delta(struct XORNeuralNetwork* nn, int x)
{
    (*nn).deltaO = ((*nn).Out[x] - (*nn).ActO) * Sigmoid_prime((*nn).ActO);

    for (int j = 0; j < XORHIDDEN; j++)
    {
        (*nn).delta[j] = (*nn).WeightHtoO[j] * (*nn).deltaO *
            Sigmoid_prime((*nn).ActH[j]);
    }
}


//Backpropagation
static void backprop(struct XORNeuralNetwork* nn, int x)
{
    feedforward(nn, x);

    delta(nn, x);

    updateBW(nn, x);

}

//Start the training
void XORTrain()
{
    srand(time(NULL));
    int epoch = 100000;
    struct XORNeuralNetwork nn = InitalizeNetwork();
    int totalInputs = XORINPUTS * XORINPUTS;
    for (int e = 0; e <= epoch; e++)
    {
        if (e % 100 == 0)
        {
            printf("Epoch = %i======================================\n",e);
        }
        for (int x = 0; x < totalInputs; x++)
        {
            backprop(&nn, x);
            if (e % 100 == 0)
            {
                printf("I = %f XOR %f -> %f \n", (nn).Inputs[x * 2]
                       , (nn).Inputs[x * 2 + 1], (nn).ActO);
            }
        }
    }
}
