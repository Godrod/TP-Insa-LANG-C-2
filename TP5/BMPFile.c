//
// Created by cfleury on 20/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BMPFile.h"

DIBHeader createDibHeader(uint32_t height, uint32_t width)
{
    DIBHeader header;

    header.size_DIBHeader = 40; /* According to TP file*/
    header.image_width = width;
    header.image_height = height;
    header.nbColorPlanes = 1;
    header.nbBitPerPixel = 24;
    header.typeCompression = 0;
    header.size_raw_image = header.image_width * header.image_height * header.nbBitPerPixel/8;
    header.hResolution = 2800;
    header.vResolution = 2800;
    header.nbUsedColours = 0;
    header.nbImportantColours = 0;

    return header;
}

FileHeader createFileHeader(DIBHeader d, char padding)
{
    FileHeader f;

    sprintf(&f.identity, "BM");
    f.file_size = sizeof(FileHeader) + d.size_DIBHeader + d.size_raw_image + padding * d.image_height;
    memset(f.application_id, 0, 4);
    f.raster_address = sizeof(FileHeader) + d.size_DIBHeader;

    return f;
}

void writeBMPFile(char* filename, Image* image)
{
    FILE* f = fopen(filename, "wb+");
    FileHeader f_header;
    DIBHeader  d_header;
    char padding;
    int i;
    char padding_value[3] = {0};

    if(f == NULL)
    {
        fprintf(stderr, "The file %s could not be opened", filename);
        exit(1);
    }

    d_header = createDibHeader(image->height, image->width);

    if (((image->width * d_header.nbBitPerPixel/8) % 4) != 0)
        padding = 4 - ((image->width * d_header.nbBitPerPixel/8) % 4);
    else
        padding = 0;

    f_header = createFileHeader(d_header, padding);

    fwrite(&f_header, sizeof(FileHeader), 1, f);
    fwrite(&d_header, d_header.size_DIBHeader, 1, f);

    for (i = 0; i < d_header.image_height; i++)
    {

        fwrite(image->raw_data + i*d_header.image_height,
               d_header.nbBitPerPixel/8, d_header.image_width, f);
        if(padding != 0)
            fwrite(&padding_value, 1, padding, f);
    }
    fclose(f);
}

void readFileHeader(FILE* fp, FileHeader* eFichier)
{
    int size;
    //Check if fp is a null pointer. Just in case
    if(fp == NULL)
    {
        fprintf(stderr, "The file pointer passed in parameter is null");
        exit(1);
    }

    size = fread(eFichier, sizeof(FileHeader), 1, fp);
    //fread return the number of element successfully read. Since here, an element is FileHeader, only 1 file header is read hence (size != 1)
    if(size != 1)
    {
        fprintf(stderr, "The file header size read is wrong: %d", size);
        exit(1);
    }
}

void readDIBHeader(FILE* fp, DIBHeader* eImage)
{
    int size;
    //Check if fp is a null pointer. Just in case
    if(fp == NULL)
    {
        fprintf(stderr, "The file pointer passed in parameter is null");
        exit(1);
    }

    size = fread(eImage, sizeof(DIBHeader), 1, fp);
    //fread return the number of element successfully read. Since here, an element is FileHeader, only 1 file header is read hence (size != 1)
    if(size != 1)
    {
        fprintf(stderr, "The file header size read is wrong: %d", size);
        exit(1);
    }
}

Image* readRawImage(FILE* fp, unsigned int address, int l, int h)
{
    Image* img = NULL;
    int height = 0, padding = 0;
    if(fp == NULL)
    {
        fprintf(stderr, "The file pointer passed in parameter is null");
        exit(1);
    }
    if((img = (Image*)malloc(sizeof(Image))) == NULL)
    {
        fprintf(stderr, "The image structure could not be allocated");
        exit(2);
    }

    if((img->raw_data = (Pixel*)malloc(l*h*3)) == NULL)//Hauteur*largeur(nb de pixel)*taille en octets d'un pixel=3
    {
        fprintf(stderr, "The raw_data array could not be allocated");
        free(img);
        exit(3);
    }

    img->height = h;
    img->width = l;
    //Calcul du padding
    if (((l * 3) % 4) != 0)
        padding = 4 - ((l * 3) % 4);
    else
        padding = 0;

    fseek(fp, address, SEEK_SET); // On se place a l'offset address
    for (height = 0; height < h; height++)
    {
        fread(img->raw_data + height*l, 3, l, fp);
        if(height != (h-1)) // Evite d'avancer de 'padding' octets quand on est à la dernière ligne
            if(padding != 0)
                fseek(fp, padding, SEEK_CUR);
    }
    return img;
}

Image* readBMPFile(char* filename, int verbose)
{
    Image* img = NULL;
    FileHeader f_header;
    DIBHeader d_header;
    FILE* fp;

    if((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "The file %s could not be opened", filename);
        exit(1);
    }

    readFileHeader(fp, &f_header);
    readDIBHeader(fp, &d_header);
    if(verbose == 1)
    {
        displayFileHeader(&f_header);
        displayDIBHeader(&d_header);
    }
    img = readRawImage(fp, f_header.raster_address, d_header.image_width, d_header.image_height);
    fclose(fp);
    return img;
}

