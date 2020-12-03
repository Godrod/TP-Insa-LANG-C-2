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
    char filename[MY_FILENAME_MAX];
    Image* f = allocateImage(100, 100);
    Pixel cross_color = {
            .red = 0,
            .green = 0,
            .blue = 255
    };
    Pixel back_color = {
            .red = 255,
            .green = 0,
            .blue = 0
    };

    createCross(f, cross_color, back_color);
    writeBMPFile_teacher("cross.bmp" , f,0);
    freeImage(f);
    return 0;
}
