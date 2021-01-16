//
// Created by cfleury on 18/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int readProbaFromFile(char* filename, float pb[NBVALUES])
{
    FILE *f;
    int val = 0;
    int total = 0;
    int i;

    if((f = fopen(filename, "rb")) == NULL)
    {
        printf("The file %s could not be opened.", filename);
        return 0;
    }

    while (feof(f) == 0)// Tant quue l'on est pas a la fin du fichier
    {
        fread(&val, 1, 2, f); // Les nombres sont stocker sur deux octets
        pb[val]++;
        total++;
    }

    for(i = 0; i < NBVALUES; i++)
    {
        pb[i]  = pb[i]/total;
    }

    fclose(f);
    return 1;
}