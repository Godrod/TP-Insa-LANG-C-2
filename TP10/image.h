
/*!
* \file image.h
* \brief File defining the image characteristics
*/
#ifndef IMAGE_H
#define IMAGE_H

/*! \def NBVALUES
* \brief number of image values
*/
#define NBVALUES 8

/*! \def IMAGESIZE
* \brief Image size
*/
#define IMAGESIZE 64*64

int readProbaFromFile(char* filename, float pb[NBVALUES]);

#endif

