
/*!
* \file memoryList.c
* \brief File with the functions required to manage the list of allocated blocks as studied in lab 7
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoryList.h"


/*!
* \brief Free memory stored in a  MemoryBlock
* \param[in] b the address of the block structure to be freed.
*/
static void freeMemoryBlock(MemoryBlock *b)
{
    if(b->file != NULL)
        free((void*) b->file);
    if(b->function != NULL)
        free((void*) b->function);

    b->file = b->function = NULL;
}



/*!
* \brief Initialize data for a memory block
* \param[in] b the address of the block structure to be initialized. 
* \param[in] f the filename
* \param[in] fn the function name
* \param[in] l the line number
* \param[in] a the address of the allocated block
* \return MemoryBlock* the address of the initialised structure
*/
static MemoryBlock * initMemoryBlock(MemoryBlock *b, const char *f, const char *fn, int l, void *a)
{
    b->file = (char *)malloc(strlen(f)+1);
    b->function = (char *)malloc(strlen(fn)+1);
    if(b->file != NULL && b->function !=NULL)
    {
        strcpy(b->file,f);
        strcpy(b->function,fn);
        b->line = l;
        b->address = a;
    }
    else
	{
        freeMemoryBlock(b);
	}
       	    
    return b;
}


/*!
* \file list.c
* \brief File with the functions required to manage the list as studied in labs 5 and 6
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*!
* \brief Allocate memory for the data element and initialize the structure members
* \param[in] f the name of the file
* \param[in] fn the name of the function
* \param[in] l the line in the file
* \param[in] address the  address allocated
* \param[in] n the next NodeList in the list
* \param[in] p the previous NodeList in the list
* \return NodeList* the address of the new data element
*/
static NodeList * newNodeList (const char *f, const char *fn , int l, void *a, NodeList *n , NodeList *p)
{
    NodeList *newNL = (NodeList *) malloc(sizeof(NodeList));
    if(newNL != NULL)
    {
        initMemoryBlock(&(newNL->b), f, fn, l, a);
        newNL->previous = p;
        newNL->next = n;
    }
    else
        fprintf(stderr,"Erreur d'allocation memoire dans newNodeList()\n");
    return newNL;
}


/*!
* \brief Desallocate memory associated to a node
* \param[in] n the address of the  data element to be freed
*/
static void freeNodeList(NodeList *n)
{
    freeMemoryBlock(&(n->b));
    free((void *)n);
}

void initList(List* l)
{
    l->sentinel_begin.next= &l->sentinel_end;
    l->sentinel_begin.previous = NULL;
    l->current = NULL;
    l->sentinel_end.next = NULL;
    l->sentinel_end.previous= &l->sentinel_begin;
}

int isEmpty(List * l)
{
    return l->sentinel_begin.next == &(l->sentinel_end) && l->sentinel_end.previous == &(l->sentinel_begin);
}

int isOutOfList(List* l)
{
    return l->current == NULL || l->current == &(l->sentinel_end) || l->current == &(l->sentinel_begin);
}

void* getCurrentAddress (List * l)
{
    return l->current->b.address;
}


void printList(List* l)
{
    setOnFirst(l);
    if(!isEmpty(l))
    {
        while(!isOutOfList(l))
        {
            printf("NODE:\n\tFile: %s\n\tFunction name: %s\n\tLine: %d\n\tAddress: %p\n",
                   l->current->b.file, l->current->b.function, l->current->b.line, l->current->b.address);
            setOnNext(l);
        }
        setOnFirst(l);
    }
    else
    {
        printf("Your list is empty\n");
    }
}

void setOnFirst(List* l)
{
    l->current = l->sentinel_begin.next;
}

void setOnLast(List* l)
{
    l->current = l->sentinel_end.previous;
}
void setOnNext(List* l)
{
    l->current = l->current->next;
}
void setOnPrevious(List *l)
{
    l->current = l->current->previous;
}
int isLast(List* l)
{
    return l->current == l->sentinel_end.previous;
}

int isFirst(List* l)
{
    return l->current == l->sentinel_begin.next;
}

int find(List* l, void* a)
{
    if(!isEmpty(l))
    {
        while (!isOutOfList(l))
        {
            if(l->current->b.address == a) // Si on trouve un noeud avec cette adresse
            {
                setOnFirst(l);
                return 1;
            }
            else
                l->current = l->current->next;
        }
        setOnFirst(l);
        return 0;
    }
    else
    {
        return 0;
    }
}

int countElement(List *l)
{
    int count = 0;
    setOnFirst(l);
    while (!isOutOfList(l))
    {
        setOnNext(l);
        count++;
    }
    setOnFirst(l);
    return count;
}

int insertSort(List *l, const char *f, const char *fn, int ln, void *a)
{
    if(isEmpty(l))
    {
        NodeList* node = newNodeList(f, fn, ln, a, &(l->sentinel_end), &(l->sentinel_begin));
        if(NULL == node)
            return 0;
        else
        {
            l->sentinel_begin.next = node;
            l->sentinel_end.previous = node;
            setOnFirst(l);
            return 1;
        }

    }
    while (!isOutOfList(l))
    {
        if(strncmp(f, l->current->b.file, strlen(f)) < 0) // If f is before b.file lexicographically
        {
            NodeList* node = newNodeList(f, fn, ln, a, l->current, l->current->previous);
            if(NULL == node)
                return 0;
            else
                return 1;
        }
        else if(strncmp(f, l->current->b.file, strlen(f)) == 0) //if the strings are equal
        {
            if(strncmp(fn, l->current->b.function, strlen(fn)) < 0) // If function name is before b.function
            {
                NodeList* node = newNodeList(f, fn, ln, a, l->current, l->current->previous);
                if(NULL == node)
                    return 0;
                else
                    return 1;
            }
            else if(strncmp(fn, l->current->b.function, strlen(fn)) == 0) //If function name and b.function are equal
            {
                if(ln < l->current->b.line)
                {
                    NodeList* node = newNodeList(f, fn, ln, a, l->current, l->current->previous);
                    if(NULL == node)
                        return 0;
                    else
                        return 1;
                }
                else //Place it after current val
                {
                    NodeList* node = newNodeList(f, fn, ln, a, l->current->next, l->current);
                    if(NULL == node)
                        return 0;
                    else
                    {
                        l->current = node;
                        l->current->previous->next = node;
                        l->current->next->previous = node;
                        if(isLast(l))
                        {
                            l->sentinel_end.previous = node;
                        }
                        return 1;
                    }

                }
            }
        }
        setOnNext(l);
    }
    //If is out of List, then we must insert the node just before the end sentinel
    NodeList* node = newNodeList(f, fn, ln, a, &(l->sentinel_end), l->sentinel_end.previous);
    if(NULL == node)
        return 0;
    else
    {
        l->sentinel_end.previous = node;
        return 1;
    }
}

void deleteFirst(List* l)
{
    int count;
    setOnFirst(l);
    NodeList* tmp = l->current;

    if(isFirst(l))
    {
        l->current->previous->next = l->current->next;
        l->current->next->previous = l->current->previous;
        l->current=NULL;
    }
    else
    {
        l->current->previous->next = l->current->next;
        l->current->next->previous = l->current->previous;
        setOnFirst(l);
    }

    freeNodeList(tmp);
}

void* deleteValue(List *l, void* a)
{
    if(find(l, a))
    {
        setOnFirst(l);
        while (!isOutOfList(l))
        {
            if(l->current->b.address == a)
            {
                NodeList* tmp = l->current->next->previous = l->current->previous;
                l->current->previous->next = l->current->next;
                freeNodeList(l->current);
                l->current = tmp; //Current is set to the previous value in the list
                return 0;
            }
            else
                setOnNext(l);
        }
    }
    else
    {
        return NULL;
    }
}

void freeList(List* l)
{
    while(!isEmpty(l))
    {
        deleteFirst(l);
    }
}

#include "test.h"
/*!
* \brief  Unit testing of the functions provided in the list.c file
*/
void test_list()
{
    List l1;
    int ret;
    printf("Unit tests on teh list module\n");

    initList(&l1);
    display_test_int("Test isEmpty() on an empty list",1,isEmpty(&l1));
    display_test_int("Test isOutOfList() when the list is empty",1,isOutOfList(&l1));
    printList(&l1);

    ret = insertSort(&l1, __FILE__, __FUNCTION__, __LINE__, 0x2541);
    display_test_int("Test first insertSort() on an empty list",1, ret);
    ret = insertSort(&l1, __FILE__, __FUNCTION__, __LINE__, 0x2542);
    display_test_int("Test second insertSort() on an empty list",1, ret);
    printList(&l1);

    setOnFirst(&l1);
    display_test_int("Test setOnFirst and getCurrentAddress at the same time", 0x2541, getCurrentAddress(&l1));
    setOnLast(&l1);
    display_test_int("Test setOnLast", 0x2542, getCurrentAddress(&l1));

    display_test_int("Test countElement()", 2, countElement(&l1));

    deleteValue(&l1, 0x2542);
    display_test_check_by_user("The printed list should only contain the first element");
    printList(&l1);

    deleteFirst(&l1);
    display_test_check_by_user("The list should now be empty");
    printList(&l1);

    ret = insertSort(&l1, __FILE__, __FUNCTION__ , __LINE__, 0x650);
    display_test_int("Test insertSort() having emptied the list", 1, ret);


    freeList(&l1);
}

