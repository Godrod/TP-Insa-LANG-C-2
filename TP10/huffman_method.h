/*!
* \file huffman_method.h
* \brief File defining the functions to build a Huffman tree
*/

#ifndef HUFFMAN_METHOD_H
#define HUFFMAN_METHOD_H

#include "huffman.h"
#include "list.h"

int fillList(list * lp, float pb[NBVALUES]);
nodeTree * buildHuffmanTree(list *lp);

#endif
