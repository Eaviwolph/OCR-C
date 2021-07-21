#include "CharBlockDetector.h"

void cutLine(int lines, int columns, int image[lines][columns], int* l1, int* l2)
{
  if (*l2 != 0) //si c'est au moins le 2 eme appel de la fonction
    {
      *l1 = *l2 + 2; //car première ligne de zeros a deja ete testée
    }
  int i = *l1; //on commence l'index à partir de la première ligne qu'in veut étudier
  int j = 0;

  while (i < lines && image[*l1][j] == 0) //on cherche l1:
    {
      j = 0;
      while (j < columns && image[i][j] == 0)
	j++;
      *l1 = i;
      i++;
    }
  j = 0; *l2 = *l1;
  while (i < lines && j < columns)  //on cherche l2:
    {
      j = 0;
      while (j < columns && image[i][j] == 0)
	j++;
      *l2 = i - 1;
      i++;
    }
  if (i == lines && j < columns)
    *l2 = *l2 + 1;
}

void arrayLine(int l1, int l2, int l, int c, int arrCutLi[l2 - l1 + 1][c], int M[l][c])
{
  //construit le tableau avec les lignes contenant les cases noires, données par CutLIne
  //variables
  //arrCutLi : le tableau qui contiendra les ligne qui viennent d'être trouvées par CutLine
  //l1 : numero de la premiere ligne à copier
  //l2 : numero de la dernière ligne à copier
  //c : nombre de colonnes dans l'image initiale
  //l : nombre de lignes dans l'image initiale
  //M : la matrice de base, l'image à analyser

  for (int i = 0; i < (l2 - l1 + 1); i++) //l2-l1+1 = nb de lignes totales que doit contenir TabDecLig
    {
      for (int j = 0; j < c; j++)
        {
	  arrCutLi[i][j] = M[l1 + i][j];
        }
    }

}

void printTableau(int lignes, int colonnes, int tableau[lignes][colonnes]) //lignes = l2-l1+1
{
  for (int t = 0; t < lignes; t++)
    {
      for (int w = 0; w < colonnes; w++)
        {
	  printf("%i", tableau[t][w]);
        }
      printf("\n");
    }
}

void cutColumn(int lines, int columns, int image[lines][columns], int* c1, int* c2)
{
  if (*c2 != 0) //si c'est au moins le 2 eme appel de la fonction
    {
      *c1 = *c2 + 2; //car première colonnes de zeros a deja ete testée
    }
  int j = *c1; //on commence l'index à partir de la première ligne qu'in veut étudier
  int i = lines;
  while (j < columns && i == lines) //on cherche l1:
    {
      i = 0;
      while (i < lines && image[i][j] == 0)
	{
	  i++;
	}
      *c1 = j;
      j++;
    }
  i = 0; *c2 = *c1;
  while (j < columns && i < lines)  //on cherche l2:
    {
      i = 0;
      while (i < lines && image[i][j] == 0)
	i++;

      *c2 = j - 1;
      j++;
      //printf("c2 APRES: %i \n", *c2);
    }
  if (i < lines && j == columns)
    *c2 = *c2 + 1;
    

}

void arrayCol(int c1, int c2, int l, int c, int arrCutCol[l][c2 - c1 + 1], int M[l][c])
{
  //construit le tableau avec les lignes contenant les cases noires, données par CutLIne
  //variables
  //arrCutLi : le tableau qui contiendra les ligne qui viennent d'être trouvées par CutLine
  //l1 : numero de la premiere ligne à copier
  //l2 : numero de la dernière ligne à copier
  //c : nombre de colonnes dans l'image initiale
  //l : nombre de lignes dans l'image initiale
  //M : la matrice de base, l'image à analyser
  for (int i = 0; i < l; i++) //l2-l1+1 = nb de lignes totales que doit contenir TabDecLig
    {
      for (int j = 0; j < c2 - c1 + 1; j++)
        {
	  arrCutCol[i][j] = M[i][c1 + j];
        }
    }
}

void resize(int Fsize, int columns, int lines, int Mfinal[Fsize][Fsize], int Mbegin[lines][columns])
{
  //redimensionne la lettre trouvée pour pouvoir corresspondre avec la taille 
  //prise en compte par le réseau de neurones
  //variables :
  //Fsize : la taille prise en compte par le réseau de neurones
  //columns : nombre de colonnes dans la matrice initiale (celle de la lettre découpée)
  //lines : nombre de lignes dans la matrice initiale (celle de la lettre découpée)
  //Mfinal : matrice final, la lettre redimensionnée, MATRICE CARRE
  //Mbegin : matrice initiale, la lettre découpée
  int ni; //new line
  int nj; //new colonne
  for (int i = 0; i < Fsize; i++)
    {
      for (int j = 0; j < Fsize; j++)
        {
	  ni = (int)(i * ((float)lines / (float)Fsize));
	  nj = (int)(j * ((float)columns / (float)Fsize));
	  Mfinal[i][j] = Mbegin[ni][nj];
        }
    }
}
void rotate(int lignes, int colonnes, int tableau[lignes][colonnes], int result[colonnes][lignes]) //lignes = l2-l1+1
{
  for (int t = 0; t < colonnes; t++)
    {
      for (int w = 0; w < lignes; w++)
        {
	  result[t][w] = tableau[w][t];
        }
    }
}


int ancienCharDetector(void)   //fct void qui retourne rien
{


  printf("bon courage mon gars \n");

  int tableau[10][5] = { {0,0,1,0,0},
			 {0,0,1,0,0},
			 {0,1,1,1,0},
			 {1,0,0,0,1},
			 {0,0,0,0,0},
			 {0,1,1,1,0},
			 {0,0,0,1,0},
			 {0,0,1,1,0},
			 {0,0,0,1,0},
			 {0,1,1,1,0} };
  int l1 = 0; //première ligne de 1
  int l2 = 0; //dernière -----------
  int c1 = 0;
  int c2 = 0;
  int lines = 10;
  int columns = 5;
  int arrCutLi[lines][columns];
  int arrCutCol[lines][columns];
  while (l2 < lines)
    {
      c2 = 0;
      c1 = 0;
      cutLine(lines, columns, tableau, &l1, &l2);

      if (l2 < lines)
        {
	  printf("\n Decoupage d'une ligne\n");
	  //a partir d'ici l2 et l1 remis a 0 je sais pas pourquoi donc on utilise firstLine et lastLine
	  arrayLine(l1, l2, lines, columns, arrCutLi, tableau);
	  printTableau(l2 - l1 + 1, columns, arrCutLi);
	  while (c2 < columns)
            {
	      cutColumn(l2 - l1 + 1, columns, arrCutLi, &c1, &c2); // avant 3 -> l2-l1+1
	      if (c2 < columns)
                {
		  printf("\nDecoupage des colonnes \n");
		  arrayCol(c1, c2, l2 - l1 + 1, 5, arrCutCol, arrCutLi);
		  //-------------affichage de la lettre trouvée---------------------
		  printTableau(l2 - l1 + 1, c2 - c1 + 1, arrCutCol); //avant : l2-l1+1 et c2-c1+1
                }
            }
        }
    }
  return 0;
}

int CharDetector(int lines, int columns, int image[lines][columns], char* torecognize, char* buffer)
{
  int len = strlen(torecognize); int bufferlen = strlen(buffer);
  int result[columns][lines];
  rotate(lines, columns, image, result);
  int t = lines; lines = columns; columns = t;
  int Fsize = 28;//la taille à envoyer au réseau de neurones
  int Mresize[Fsize][Fsize];//la matrice resizée
  struct NeuralNetwork *nn = InitNewNetwork();
  int epoch = 5000;
  int i; int j;
  if(len == 0)
      epoch = 0;
  for (int e = 0; e <= epoch; e++)
    {

      j = 0; i = 0; int l1 = 0; int l2 = 0;
      int c1 = 0; int c2 = 0; int f1 = 0; int f2 = 0;
      while (l2 < lines && (len == 0 || (j < len && i < bufferlen)))
	{
	  c2 = 0;
	  c1 = 0;
	  cutLine(lines, columns, result, &l1, &l2);
	  if (l2 < lines)
	    {
	      int arrCutLi[l2 - l1 + 1][columns];
	      arrayLine(l1, l2, lines, columns, arrCutLi, result);
	      while (c2 < columns && (len == 0 || (j < len && i < bufferlen)))
		{
		  f2 = 0;
		  f1 = 0;
		  cutColumn(l2 - l1 + 1, columns, arrCutLi, &c1, &c2);
		  if (c2 < columns)
		    {
		      int arrCutCol[l2 - l1 + 1][c2 - c1 + 1];
		      arrayCol(c1, c2, l2 - l1 + 1, columns, arrCutCol, arrCutLi);

		      cutLine(l2 - l1 + 1, c2 - c1 + 1, arrCutCol, &f1, &f2);
		      int arrCutFi[f2 - f1 + 1][c2 - c1 + 1];
		      arrayLine(f1, f2, l2 - l1 + 1, c2 - c1 + 1, arrCutFi, arrCutCol);

		      resize(Fsize, c2 - c1 + 1, f2 - f1 + 1, Mresize, arrCutFi);
		      //c2-c1+1 : nb de colonnes de arraycol
		      //l2-l1+1 : nb de lignes de arraycol
		      Tabcopy(nn, Mresize);
		      if(len == 0)
			{
			  buffer[i] = OCR(nn);
			}
		      else
			{
			  buffer[i] = OCRTrain(nn, torecognize[j]);
			  //on donne la lettre au reseau de neurones
			}
		      if (e % 1000 == 0 && len > 0)
			{
			  if(torecognize[j] != MaxChar(nn, OUTPUT))
			    {
			      printTableau(Fsize, Fsize, Mresize); //avant : l2-l1+1 et c2-c1+1
			    }
			  printf("Epoch = %i======================================\n", e);
			  printf("Was %c and Guess %c \n", torecognize[j], MaxChar(nn, OUTPUT));
			}
		      i++;
		      j++;
		    }
		}
	    }
	  buffer[i] = '\n';
	  i++;
	}
    }
  buffer[i] = '\0';
  SaveNeuralSystem(nn, OUTPUT, HIDDEN, INPUTS);
  free(nn);
  return 0;
}
