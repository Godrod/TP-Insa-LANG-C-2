//
// Created by cfleury on 18/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

nodeTree* newNodeTree(float p, nodeTree* l, nodeTree* r)
{
    nodeTree* node = malloc(sizeof(nodeTree));
    if(NULL == node)
    {
        printf("Failed to allocate memory for new NodeTree* ");
        return NULL;
    }
    node->right = r;
    node->left = l;
    node->proba = p;
    return node;
}

char isLeaf(nodeTree* t)
{
    return t->left == NULL && t->right == NULL;
}

void deleteNodeTree(nodeTree* n)
{
    free(n);
}

void deleteBinaryTree(Binary_tree t)
{
    if(!isLeaf(t))
    {
        if(t->left != NULL)
            deleteBinaryTree(t->left);
        if(t->right != NULL)
            deleteBinaryTree(t->right);
        deleteNodeTree(t);
    }
    else
    {
        deleteNodeTree(t);
    }

}

nodeTree* buildParentNode(nodeTree* p1, nodeTree* p2)
{
    nodeTree* parent;
    if(p1->proba <= p2->proba)
    {
        parent = newNodeTree(p1->proba + p2->proba, p1, p2);
    }
    else
    {
        parent = newNodeTree(p1->proba + p2->proba, p2, p1);
    }
    return parent;
}

void printTree(Binary_tree t)
{
    printf("Proba: %f\n", t->proba);
    if (!isLeaf(t))
    {
        if(t->left != NULL)
            printTree(t->left);
        if(t->right != NULL)
            printTree(t->right);
    }
}

static void printCode (char cod[CODEMAX], int size_code, float pb)
{
    int i;
    printf ("Codeword for probability %5.3f is: ", pb);
    for (i = 0; i < size_code; i++)
        printf ("%c" , cod[i]);
    printf ("\n");
}


void printCodewords(Binary_tree t)
{
    static int i = 0;
    static char code[CODEMAX] = {0};
    if(!isLeaf(t))
    {
        if(t->left !=NULL)
        {
            code[i] = '0';
            i++;
            printCodewords(t->left);
            i--;
            code[i] = 0;
        }
        if(t->right != NULL)
        {
            code[i] = '1';
            i++;
            printCodewords(t->right);
            i--;
            code[i] = 0;
        }
    }
    else {
        printCode(code, i, t->proba);
        code[i - 1] = 0;
    }
}
