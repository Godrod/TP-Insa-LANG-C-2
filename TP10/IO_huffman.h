/*!
* \file IO_huffman.h
* \brief File defining the function to read an image and estimate the probability
*/
#ifndef IO_HUFFMAN_H
#define IO_HUFFMAN_H

#include "image.h"
int readProbaFromFile(char* name, float pb[NBVALUES]);

#endif
