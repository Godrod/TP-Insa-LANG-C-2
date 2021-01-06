
#include "myDoubleTree.h"
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


/*!
* \brief Allocate memory for the node element and initialize the structure members
* \param[in] v the double for the value member
* \param[in] l the address of the left child
* \param[in] r the address of the right child
* \return DNode* the address of the new tree element
*/
DNode * initNode(double v, DNode * l, DNode * r)
{
    DNode * new = (DNode*) malloc(sizeof(DNode));
    if(new == NULL)
        return NULL;
    new->value = v;
    new->left = l;
    new->right = r;
    return new;
}

/*!
* \brief Desallocate memory associated to a node
* \param[in] n the address of the  data element to be freed
*/
static void freeNode(DNode * n)
{
    free((void*) n);
}


/*!
* \brief Suppress all elements from a tree
* \param[in] t the tree to be emptied
*/
void freeTree(DTree t)
{
    if(t!=NULL)
    {
        if(t->right != NULL)
            freeTree(t->right);

        if(t->left != NULL)
            freeTree(t->left);

        freeNode(t);
    }
}


/*!
* \brief Initialize an empty tree
* \param[out] t the tree to be initialized
*/
void initTree(DTree * t)
{
    *t = NULL;
}


/*!
* \brief Tests if it is an empty tree
* \param[in] t the tree to be tested
* \return int 1 if empty, 0 otherwise
*/
int isEmpty(DTree t)
{
    return t == NULL;
}

/*!
* \brief Tests if it is a leaf
* \param[in] t the tree to be tested
* \return int 1 if it is a leaf, 0 otherwise
*/
int isLeaf(DTree t)
{
    return t->left == NULL && t->right == NULL ;
}

/*!
* \brief Return the height of a tree
* \param[in,out] t the tree
* \return return height
*/
int getHeight(DTree t)
{
    int left = 0, right = 0;
    if (isLeaf(t))
        return 1;
    else
    {
        if(!isEmpty(t->left))
        {
            left = 1 + getHeight(t->left); /*Each node counts itself, thus the 1 + */
        }
        if(!isEmpty(t->right))
        {
            right = 1 + getHeight(t->right); /*Each node counts itself, thus the 1 + */
        }

        if(right > left)
            return right;
        else
            return left;
    }
}

double findMax(DTree t)
{
    double max = 0.0;
    if(isLeaf(t) || isEmpty(t->right))
        return t->value;
    else
    {
        max = findMax(t->right); //If the tree is sorted well, the max value is at the bottom right of the tree
        return max;
    }
}

int isUnbalancedTree(DTree t)
{
    return getHeight(t->left) != getHeight(t->right);
}

DTree rightRotation(DTree t)
{
    if(!isEmpty(t->left))
    {
        DTree rotated = t->left;
        DTree saved_right_child = rotated->right;

        rotated->right = t;
        t->left = saved_right_child;

        return rotated;
    }
    else
    {
        return t;
    }
}

DTree leftRotation(DTree t)
{
    if(!isEmpty(t->left))
    {
        DTree rotated = t->right;
        DTree saved_right_child = rotated->left;

        rotated->left = t;
        t->right = saved_right_child;

        return rotated;
    }
    else
    {
        return t;
    }
}

DTree reBalance(DTree t)
{
    DTree balanced = t;
    if (!isEmpty(t))
    {
        int diff = 0;
        while(abs(diff = getHeight(balanced->left) - getHeight(balanced->right)) > 1) // s'arrête quand abs(diff) <= 1, d'après le sujet de TP
        {
            if(diff > 0)
            {
                balanced = rightRotation(balanced);
            }
            else
            {
                 balanced = leftRotation(balanced);
            }
        }
    }
    return balanced;
}


/*!
* \brief Insert a new element containing the double value given as a parameter to get a sorted tree
* \param[in,out] t the tree
* \param[in] v the value to be inserted
* \return int 1 if everything was OK, 0 otherwise
*/
DTree addDouble(DTree  t, double v)
{
    if(isEmpty(t))
        t = initNode(v,NULL,NULL);
    else
    {
        double current_val = t->value;
        if(current_val == v)
            return t; /*already in the tree*/
        else
            if(current_val > v)
                t->left = addDouble(t->left,v);
            else
                t->right = addDouble(t->right,v);
    }
    return t;
}

/*!
* \brief Build a sorted tree from a sorted array
* \param[in] a the array of sorted values
* \param[in] n the number of values in the array
* \return DTree the new tree
*/
DTree buildBalancedTreeFromSortedArray(double * a, int n)
{
    if(n!=0)
        return initNode(a[n/2],buildBalancedTreeFromSortedArray(a,n/2),buildBalancedTreeFromSortedArray(a + n/2 + 1,(n-1)/2));
    return NULL;
}


/*!
* \brief Print the content of the current node of the tree
* \param[in] t the node to be displayed
* \param[in] depth its depth in the tree
*/
static void printTreeRec(DTree t, int depth)
{
	if(!isEmpty(t))
	{
        int i;
        printTreeRec(t->left,depth+1);
        for(i = 0; i< depth ; i++)
            printf("\t");
        printf("%f\n",t->value);
        printTreeRec(t->right,depth+1);
	}
}

/*!
* \brief Print the content of the tree
* \param[in] t the tree to be displayed
*/
void printTree(DTree t)
{
	if(!isEmpty(t))
	{
        printf("--------- Printing tree : --------- \n");
        printTreeRec(t,0);
        printf("--------- End of printing tree --------- \n\n");
	}
	else
        printf("This tree is empty \n");
}








