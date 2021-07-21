#include "OCRNeuralSystem.h"

#define CHARLC 0
#define CHARHC 26
#define OTHER 52

double Random()
{
  return (double)rand() / ((double)RAND_MAX/2)-1;
}
double Sigmoid(double z)
{
  return(1.0 / (1.0 + exp(-z)));
}
double Sigmoid_prime(double z)
{
  return((z) * (1 - (z)));
}
char CharToPlace(char c)
{
  char p = 0;
  if (c >= 'a' && c <= 'z')
    {
      p = CHARLC + c - 'a';
    }
  else if (c >= 'A' && c <= 'Z')
    {
      p = CHARHC + c - 'A';
    }
  else
    {
      p = OTHER;
    }
  return p;
}
char PlaceToChar(char p)
{
  char c = 'a';
  if (p >= CHARLC && p < CHARHC)
    {
      c = p - CHARLC + 'a';
    }
  else if (p >= CHARHC && p < OTHER)
    {
      c = p - CHARHC + 'A';
    }

  return c;
}
char MaxChar(struct NeuralNetwork* nn, int output)
{
  int max = 0;
  for (int i = 1; i < output; i++)
    {
      if ((*nn).ActO[max] < (*nn).ActO[i])
	{
	  max = i;
	}
    }
  return PlaceToChar((char)max);
}
void SaveNeuralSystem(struct NeuralNetwork* nn, int output, int hidden, int input)
{
  FILE* FileWeightItoH = fopen("WeightItoH", "w");
  for (int i = 0; i < input; ++i)
    {
      for (int j = 0; j < hidden; j++)
	{
	  fprintf(FileWeightItoH, "%f\n", (*nn).WeightItoH[i][j]);
	}
    }
  fclose(FileWeightItoH);
  FILE* FileBiasH = fopen("BiasH", "w");
  for (int i = 0; i < hidden; i++)
    {
      fprintf(FileBiasH, "%f\n", (*nn).BiasH[i]);
    }
  fclose(FileBiasH);
  
  FILE* FileWeightHtoO = fopen("WeightHtoO", "w");
  for (int i = 0; i < hidden; i++)
    {
      for (int j = 0; j < output; j++)
	{
	  fprintf(FileWeightHtoO, "%f\n", (*nn).WeightHtoO[i][j]);
	}
    }
  fclose(FileWeightHtoO);
  FILE* FileBiasO = fopen("BiasO", "w");
  for (int i = 0; i < output; i++)
    {
      fprintf(FileBiasO, "%f\n", (*nn).BiasO[i]);
    }
    fclose(FileBiasO);

  
}
void InitInOut(struct NeuralNetwork* nn, int output)
{
  for (int i = 0; i < output; i++)
    {
      (*nn).DesOut[i] = 0;
    }
}
void InitWeightItoH(struct NeuralNetwork* nn, int hidden, int input)
{
  FILE* FileWeightItoH = fopen("WeightItoH", "r");
  if (FileWeightItoH == NULL)
    {
      for (int i = 0; i < input; i++)
	{
	  for (int j = 0; j < hidden; j++)
	    {
	      (*nn).WeightItoH[i][j] = Random();
	    }
	}
    }
  else
    {
      char line[16];
      for (int i = 0; i < input; i++)
	{
	  for (int j = 0; j < hidden; j++)
	    {
	      fgets(line, 16, FileWeightItoH);
	      (*nn).WeightItoH[i][j] = atof(strtok(line, "\n"));
	    }
	}
      fclose(FileWeightItoH);
    }
}
void InitWeightHtoO(struct NeuralNetwork* nn, int output, int hidden)
{
  FILE* FileWeightHtoO = fopen("WeightHtoO", "r");
  if (FileWeightHtoO == NULL)
    {
      for (int i = 0; i < hidden; i++)
	{
	  for (int j = 0; j < output; j++)
	    {
	      (*nn).WeightHtoO[i][j] = Random();
	    }
	}
    }
  else
    {
      char line[16];
      for (int i = 0; i < hidden; i++)
	{
	  for (int j = 0; j < output; j++)
	    {
	      fgets(line, 16, FileWeightHtoO);
	      (*nn).WeightHtoO[i][j] = atof(strtok(line, "\n"));
	    }
	}
      fclose(FileWeightHtoO);
    }
}
void InitBiasH(struct NeuralNetwork* nn, int hidden)
{
  FILE* FileBiasH = fopen("BiasH", "r");
  if (FileBiasH == NULL)
    {
      for (int i = 0; i < hidden; i++)
	{
	  (*nn).BiasH[i] = Random();
	}
    }
  else
    {
      char line[16];
      for (int i = 0; i < hidden; i++)
	{
	  fgets(line, 16, FileBiasH);
	  (*nn).BiasH[i] = atof(strtok(line, "\n"));
	}
      fclose(FileBiasH);
    }
}
void InitBiasO(struct NeuralNetwork* nn, int output)
{
  FILE* FileBiasO = fopen("BiasO", "r");
  if (FileBiasO == NULL)
    {
      for (int i = 0; i < output; i++)
	{
	  (*nn).BiasO[i] = Random();
	}
    }
  else
    {
      char line[16];
      for (int i = 0; i < output; i++)
	{
	  fgets(line, 16, FileBiasO);
	  (*nn).BiasO[i] = atof(strtok(line, "\n"));
	}
      fclose(FileBiasO);
    }
}
void Tabcopy(struct NeuralNetwork* nn, int tab[28][28])
{
  int line = 28;
  for (int i = 0; i < line; i++)
    {
      for (int j = 0; j < line; j++)
	{
	  (*nn).Input[i*line + j] = tab[i][j];
	}
    }
}
