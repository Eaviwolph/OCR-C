#include "OCRNeuralSystem.h"

//Initialisation of the NeuralNetwork
struct NeuralNetwork *InitNewNetwork()
{
  srand(time(NULL));
  struct NeuralNetwork *nn = NULL;
  nn = malloc(sizeof(struct NeuralNetwork));
  (*nn).eta = 1;
  //InitValues
  InitInOut(nn, OUTPUT);
  InitWeightItoH(nn, HIDDEN, INPUTS);
  InitWeightHtoO(nn, OUTPUT, HIDDEN);
  InitBiasH(nn, HIDDEN);
  InitBiasO(nn, OUTPUT);

  return nn;
}

//Process all activations and so the output
static void Feedforward(struct NeuralNetwork* nn)
{
  double Sum = 0;
  for (int j = 0; j < HIDDEN; j++) // For each Hiddens
    {
      Sum = 0;
      for (int i = 0; i < INPUTS; i++) // For each Inputs
        {
	  Sum += (*nn).WeightItoH[i][j] * (*nn).Input[i];
        }
      (*nn).ActH[j] = Sigmoid(Sum + (*nn).BiasH[j]);
    }

  Sum = 0.0;
  for (int j = 0; j < OUTPUT; j++) // For each Outputs
    {
      Sum = 0;
      for (int i = 0; i < HIDDEN; i++) // For each Inputs
        {
	  Sum += (*nn).WeightHtoO[i][j] * (*nn).ActH[i];
        }
      (*nn).ActO[j] = Sigmoid(Sum + (*nn).BiasO[j]);
    }
}

//Update Weights and Biases
static void UpdateBW(struct NeuralNetwork* nn)
{
  for (int j = 0; j < HIDDEN; j++)
    {
      (*nn).BiasH[j] += (*nn).eta * (*nn).deltaH[j];
      for (int i = 0; i < INPUTS; i++)
        {

	  (*nn).dWeightItoH[i][j] = (*nn).eta *
	    (*nn).Input[i] * (*nn).deltaH[j];
	  (*nn).WeightItoH[i][j] += (*nn).dWeightItoH[i][j];
        }
    }

  for (int j = 0; j < OUTPUT; j++)
    {
      (*nn).BiasO[j] += (*nn).eta * (*nn).deltaO[j];
      for (int i = 0; i < HIDDEN; i++)
        {
	  (*nn).dWeightHtoO[i][j] = (*nn).eta * (*nn).ActH[i] * (*nn).deltaO[j];
	  (*nn).WeightHtoO[i][j] += (*nn).dWeightHtoO[i][j];
        }
    }
}
//Process all delta to apply on updates
static void Delta(struct NeuralNetwork* nn)
{
  for (int j = 0; j < OUTPUT; j++)
    {
      (*nn).deltaO[j] = ((*nn).DesOut[j] - (*nn).ActO[j]) * 
	Sigmoid_prime((*nn).ActO[j]);
    }

  double Sum = 0;
  for (int j = 0; j < HIDDEN; j++)
    {
      Sum = 0;
      for (int i = 0; i < OUTPUT; i++)
        {
	  Sum += (*nn).WeightHtoO[i][j] * (*nn).deltaO[j];
        }
      (*nn).deltaH[j] = Sum * Sigmoid_prime((*nn).ActH[j]);
    }
}


//Backpropagation
static void backprop(struct NeuralNetwork* nn)
{
  Feedforward(nn);

  Delta(nn);

  UpdateBW(nn);
}

void PrintOutput(struct NeuralNetwork* nn)
{
  printf("------------------------\n");
  for (int i = 0; i < OUTPUT; i++)
    {
      printf("DesOut = %f and Got = %f\n",(*nn).DesOut[i], (*nn).ActO[i]);
    }
  printf("------------------------\n");
}

char OCR(struct NeuralNetwork* nn)
{
  Feedforward(nn);
  return MaxChar(nn, OUTPUT);
}

//Start the training
char OCRTrain(struct NeuralNetwork* nn, char c)
{
  InitInOut(nn, OUTPUT);
  (*nn).DesOut[(int)CharToPlace(c)] = 1;
  backprop(nn);
  //PrintOutput(nn);
  return MaxChar(nn, OUTPUT);
}
