#include <stdio.h>
#include <stdlib.h>

#include "image.h"

#include "BMPFile.h"


/*!\def MY_FILENAME_MAX
* Taille maximum du nom d'un fichier
*/
#define MY_FILENAME_MAX 64

int main()
{
    /*D'apres l'implementation de ma fonction readBMPFile, le code ne peut fonctionner que pour des images ayant une resolution
     * horizontal et verticale correspondant à la valeur 2800 (voir code createDibHeader)*/
    Image* img = readBMPFile("cross.bmp", 1);

    writeBMPFile("cross2.bmp", img);
    return 0;
}
