#include <stdio.h>
#include <stdlib.h>

#include "myDoubleTree.h"

int main()
{
    DTree t;
    double data_sorted []= {1.0, 2.1, 3.5, 4.6, 5.1};
    double data2_unsorted []= {2.1, 1.0,  3.5, 4.6, 5.1};
    int nb,nb2;
    int i ;


    initTree(&t);

    nb = sizeof(data_sorted)/sizeof(data_sorted[0]);
    t = buildBalancedTreeFromSortedArray(data_sorted, nb);
    printTree(t);


    printf("hauteur : %d (should be 3)\n",getHeight(t));
    printf("hauteur : %d (should be 2)\n",getHeight(t->left));


    printf("max : %f (should be 5.1)\n",findMax(t));
    printf("max : %f (should be 2.1)\n",findMax(t->left));

    printf("isUnbalancedTree: %d (should be 0)", isUnbalancedTree(t));

/*
    t = addDouble(t,6);
    t = addDouble(t,5.5);
    t = addDouble(t,7);
    t = addDouble(t,8);
    t = addDouble(t,9);
    printTree(t);

    t = rightRotation(t);
    printTree(t);
    t = leftRotation(t);
    printTree(t);

    printTree(reBalance(t));
    freeTree(t);
*/
/*
    initTree(&t);

    nb = sizeof(data_unsorted)/sizeof(data_unsorted[0]);
    t = buildBalancedTreeFromSortedArray(data_unsorted, nb);
    printTree(t);
    freeTree(t);
*/
/*
    initTree(&t);
    t = readDTreeFromFile("data.bin");
    printTree(t);
*/
    freeTree(t);

    return 0;
}


