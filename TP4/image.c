//
// Created by cfleury on 19/11/2020.
//

#include <stdlib.h>
#include "image.h"

Image* allocateImage(int l, int h)
{
    int number_of_pixels, size;
    Image* img = NULL;

    number_of_pixels = l * h;
    if((img = (Image*) malloc(sizeof(Image))) == NULL)
    {
        fprintf(stderr, "The image struct could not be allocated");
        exit(0);
    }
    img->height = h;
    img->width = l;

    /* The size of raw_data is the number of pixels multiplied
     * by the number of bytes necessary to encode a pixel -> 3 bytes*/
    if((img->raw_data = malloc(l * h * sizeof(Pixel))) == NULL)
    {
        fprintf(stderr, "The pixel array struct could not be allocated");
        free(img);
        exit(0);
    }

    return img;

}

void setPixelxy(Image *image, int x, int y , Pixel p)
{
    image->raw_data[x + y*image->width] = p;
}

Pixel getPixelxy(Image *image, int x, int y)
{
    Pixel p = image->raw_data[x + y*image->width];
    return p;
}
void modifyImage(Image* image, Pixel pix_initial, Pixel pix_final)
{
    int x, y;
    Pixel current;

    for (y = 0; y < image->height; y++)
    {
        for(x = 0; x < image->width; x++)
        {
            current = getPixelxy(image, x, y);
            if(current.red == pix_initial.red &&
               current.green == pix_initial.green &&
               current.blue == pix_initial.blue)
            {
                setPixelxy(image, x, y, pix_final);
            }
        }
    }
}

void createCross(Image* image, Pixel cross, Pixel back)
{
    int x, y, offset_x;
    offset_x = 0;

    for (y = 0; y < image->height; y++)
    {
        for(x = 0; x < image->width; x++)
        {
            if ((x == offset_x) || (x == image->width-1-offset_x))
                setPixelxy(image, x, y, cross);
            else
                setPixelxy(image, x, y, back);
        }
        offset_x++;
    }
}

void freeImage(Image* i)
{
    free(i->raw_data);
    free(i);
}
