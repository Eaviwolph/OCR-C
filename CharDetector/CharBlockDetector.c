#include "CharBlockDetector.h"


void cutLine(int lines, int columns, int image[lines][columns], int* l1, int* l2)
{
    if (*l2 != 0) //si c'est au moins le 2 eme appel de la fonction
    {
        *l1 = *l2 + 2; //car premi�re ligne de zeros a deja ete test�e
    }
    int i = *l1; //on commence l'index � partir de la premi�re ligne qu'in veut �tudier
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
    //construit le tableau avec les lignes contenant les cases noires, donn�es par CutLIne
    //variables
    //arrCutLi : le tableau qui contiendra les ligne qui viennent d'�tre trouv�es par CutLine
    //l1 : numero de la premiere ligne � copier
    //l2 : numero de la derni�re ligne � copier
    //c : nombre de colonnes dans l'image initiale
    //l : nombre de lignes dans l'image initiale
    //M : la matrice de base, l'image � analyser

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
        *c1 = *c2 + 2; //car premi�re colonnes de zeros a deja ete test�e
    }
    int j = *c1; //on commence l'index � partir de la premi�re ligne qu'in veut �tudier
    int i = 0;

    while (j < columns && image[i][*c1] == 0) //on cherche l1:
    {
        i = 0;
        while (i < lines && image[i][j] == 0)
            i++;
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
    //construit le tableau avec les lignes contenant les cases noires, donn�es par CutLIne
    //variables
    //arrCutLi : le tableau qui contiendra les ligne qui viennent d'�tre trouv�es par CutLine
    //l1 : numero de la premiere ligne � copier
    //l2 : numero de la derni�re ligne � copier
    //c : nombre de colonnes dans l'image initiale
    //l : nombre de lignes dans l'image initiale
    //M : la matrice de base, l'image � analyser
    for (int i = 0; i < l; i++) //l2-l1+1 = nb de lignes totales que doit contenir TabDecLig
    {
        for (int j = 0; j < c2 - c1 + 1; j++)
        {
            arrCutCol[i][j] = M[i][c1 + j];
        }
    }
}



int CharDetector(void)   //fct void qui retourne rien
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
    int l1 = 0; //premi�re ligne de 1
    int l2 = 0; //derni�re -----------
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

            //printf("\nl1= %i should be : 1 puis 5\n", l1);
            //printf("l2= %i shoulb be : 3 puis 9\n", l2);


            



            //a partir d'ici l2 et l1 remis a 0 je sais pas pourquoi donc on utilise firstLine et lastLine

            arrayLine(l1, l2, lines, columns, arrCutLi, tableau);

            printTableau(l2 - l1 + 1, columns, arrCutLi);

            while (c2 < columns)
            {



                cutColumn(l2 - l1 + 1, columns, arrCutLi, &c1, &c2); // avant 3 -> l2-l1+1

                if (c2 < columns)
                {
                    printf("\nDecoupage des colonnes \n");

                    //printf("c1= %i ;should be : 0 puis 0\n", c1);
                    //printf("c2= %i ;should be : 4 puis 3\n", c2);


                    

                    arrayCol(c1, c2, l2 - l1 + 1, 5, arrCutCol, arrCutLi);

                    //-------------affichage de la lettre trouv�e---------------------
                    printTableau(l2 - l1 + 1, c2 - c1 + 1, arrCutCol); //avant : l2-l1+1 et c2-c1+1
                }

            }
        }


    }



    //-------------affichage de la lettre trouv�e---------------


    //-------------------------------------------------------
    //--------------on d�coupe des colonnes-----------------------------------------
    //-------------------------------------------------------


    return 0;
}
