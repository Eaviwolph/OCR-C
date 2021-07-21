#include "XORNeuralSystem.h"

struct NeuralNetwork InitalizeNetwork()
{
    struct NeuralNetwork nn;

    nn.eta = 3;
    nn.alpha = 1.0/nn.eta;

    //InitValues

    for (int i = 0; i < INPUTS; i++)
    {
        for (int j = 0; j < HIDDEN; j++)
        {
            nn.WeightItoH[i * HIDDEN + j] = Random();
            nn.dWeightItoH[i * HIDDEN + j] = 0.0;
        }
    }

    for (int i = 0; i < HIDDEN; i++)
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


void feedforward(struct NeuralNetwork* nn, int x)
{
    double Sum = 0.0;
    for (int j = 0; j < HIDDEN; j++) // For each Hidden
    {
        Sum = 0;
        for (int i = 0; i < INPUTS; i++) // For each Inputs
        {
            Sum += (*nn).WeightItoH[j + i * HIDDEN] *
                (*nn).Inputs[x * INPUTS + i];
        }
        (*nn).ActH[j] = sigmoid(Sum + (*nn).BiasH[j]);
    }
    Sum = 0.0;
    for (int j = 0; j < HIDDEN; j++)
    {
        Sum += (*nn).WeightHtoO[j] * (*nn).ActH[j];
    }
    (*nn).ActO = sigmoid(Sum + (*nn).BiasO);

}

// Backward Inputs to Hiddens
void updateBW(struct NeuralNetwork* nn, int x)
{
    (*nn).BiasO += (*nn).eta * (*nn).deltaO;
    for (int j = 0; j < HIDDEN; j++)
    {
        (*nn).BiasH[j] += (*nn).eta * (*nn).delta[j];
        for (int i = 0; i < INPUTS; i++)
        {
            (*nn).dWeightItoH[j + i * HIDDEN] = (*nn).eta *
                (*nn).Inputs[i + x * INPUTS] *
                (*nn).delta[j] + (*nn).alpha *
                (*nn).dWeightItoH[j + i * HIDDEN];

            (*nn).WeightItoH[j + i * HIDDEN] +=
                (*nn).dWeightItoH[j + i * HIDDEN];
        }
        (*nn).dWeightHtoO[j] = (*nn).eta * (*nn).ActH[j] *
            (*nn).deltaO + (*nn).alpha * (*nn).dWeightHtoO[j];
        (*nn).WeightHtoO[j] += (*nn).dWeightHtoO[j];
    }
}

void delta(struct NeuralNetwork* nn, int x)
{
    (*nn).deltaO = ((*nn).Out[x] - (*nn).ActO) *
        (*nn).ActO * (1.0 - (*nn).ActO);

    for (int j = 0; j < HIDDEN; j++)
    {
        (*nn).delta[j] = (*nn).WeightHtoO[j] * (*nn).deltaO *
            sigmoid_prime((*nn).ActH[j]);
    }
}



void backprop(struct NeuralNetwork* nn, int x)
{
    feedforward(nn, x);

    delta(nn, x);

    updateBW(nn, x);

}

void XORTrain()
{
    srand(time(NULL));

    int NbEpoch = 100000;

    struct NeuralNetwork nn = InitalizeNetwork();

    int totalInputs = INPUTS * INPUTS;

    for (int epoch = 0; epoch <= NbEpoch; epoch++)
    {
        if (epoch % 100 == 0)
        {
            printf("Epoch = %i======================================\n",epoch);
        }
        for (int x = 0; x < totalInputs; x++)
        {
            backprop(&nn, x);
            if (epoch % 100 == 0)
            {
                printf("I = %f XOR %f -> %f \n", (nn).Inputs[x * 2]
                       , (nn).Inputs[x * 2 + 1], (nn).ActO);
            }
        }
    }
}
