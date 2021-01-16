//
// Created by cfleury on 18/12/2020.
//

#include <stdio.h>
#include "image.h"
#include "huffman.h"
#include "huffman_method.h"
#include "list.h"

int main(int argc, char* argv[])
{
    //float pb1[NBVALUES] = {0}, pb2[NBVALUES] = {0};
    float pb[NBVALUES] = {0};
    int i;
    Binary_tree t;
    list *l;

    readProbaFromFile("IM1.IM", pb);
    for(i = 0; i < NBVALUES; i++)
    {
        printf("Valeur %d: %f (frequencies)\n", i, pb[i]);
    }

    initList(l);
    fillList(l, pb);
    t = buildHuffmanTree(l);

    printTree(t);
    printCodewords(t);

    /*readProbaFromFile("IM2.IM", pb2);
    printf("\n\n");
    for(i = 0; i < NBVALUES; i++)
    {
        printf("Valeur %d: %f (frequencies)\n", i, pb2[i]);
    }*/

    deleteBinaryTree(t);
    deleteList(l);
    return 0;
}