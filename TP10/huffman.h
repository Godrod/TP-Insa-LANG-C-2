//
// Created by cfleury on 18/12/2020.
//

#ifndef TP10_HUFFMAN_H
#define TP10_HUFFMAN_H
#define CODEMAX 15

typedef struct nodeTree{
    float proba;
    struct nodeTree* left;
    struct nodeTree* right;
}nodeTree;

typedef nodeTree * Binary_tree;

nodeTree* newNodeTree(float p, nodeTree* l, nodeTree* r);
void deleteNodeTree(nodeTree* n);
void deleteBinaryTree(Binary_tree t);
nodeTree* buildParentNode(nodeTree* p1, nodeTree* p2);
void printTree(Binary_tree t);
void printCodewords(Binary_tree t);

#endif //TP10_HUFFMAN_H
