
/*!
* \file list.c
* \brief File with the functions required to manage the list as studied in labs 5 and 6
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listMO.h"


/*!
* \brief Allocate memory for the data element and initialize the structure members
* \param[in] name the name of the multimedia object
* \param[in] path the path of the multimedia object
* \param[in] day the day of creation of the multimedia object
* \param[in] month the  month of creation  of the multimedia object
* \param[in] year the  year of creation  of the multimedia object
* \param[in] type the type of the multimedia object
* \param[in] n the address of the setOnNext data element
* \return NodeList* the address of the new data element
*/
static NodeList *newNodeList(char * name, char * path, int day, int month, int year, TypeMultimediaObject type, NodeList * n)
{
    NodeList *newNL = (NodeList *) malloc(sizeof(NodeList));
    if(newNL != NULL)
    {
        fillMO(&(newNL->value), name, path, day, month, year, type);
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
    free((void *)n);
}

void initList(List* l)
{
    l->first = NULL;
    l->current = NULL;
    l->last = NULL;
}

int isEmpty(List * l)
{
    return l->first == NULL && l->current == NULL && l->last == NULL;
}

int isOutOfList(List* l)
{
    return l->current == NULL;
}

char* getCurrentName(List* l)
{
    return l->current->value.name;
}

void printList(List* l)
{
    setOnFirst(l);
    if(!isEmpty(l))
    {
        while(!isOutOfList(l))
        {
            printf("NODE:\n\tName: %s\n\tPath: %s\n\tDate: %d/%d/%d\n\tType: ",
                   l->current->value.name, l->current->value.path, l->current->value.date.day,
                   l->current->value.date.month, l->current->value.date.year);
            if(l->current->value.type == PHOTO)
                printf("PHOTO\n\n");
            else if (l->current->value.type == VIDEO)
                printf("VIDEO\n\n");
            else
                printf("UNDEFINED\n\n");
            l->current = l->current->next;
        }
        setOnFirst(l);
    }
    else
    {
        printf("Your list is empty\n");
    }
}

int insertFirst(List * l, char * name, char * path, int day, int month, int year, TypeMultimediaObject type)
{
    NodeList* node = newNodeList(name, path, day, month, year, type, l->first);
    if(node != NULL)
    {
        if(isEmpty(l))
        {
            l->last = node;
        }
        l->first = node;
        setOnFirst(l);
        return 1;
    }
    else
    {
        return 0;
    }

}
void setOnFirst(List* l)
{
    l->current = l->first;
}

void setOnLast(List* l)
{
    l->current = l->last;
}
void setOnNext(List* l)
{
    l->current = l->current->next;
}
int isLast(List* l)
{
    return l->current == l->last;
}

int isFirst(List* l)
{
    return l->current == l->first;
}

int find(List* l, char* name)
{
    if(!isEmpty(l))
    {
        while (!isOutOfList(l))
        {
            if(!strncmp(l->current->value.name, name, 512)) // Si on trouve un noeud avec ce nom
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

void deleteFirst(List* l)
{
    if(isLast(l))
    {
        l->last = NULL;
    }
    NodeList* tmp = l->current;
    l->current = l->current->next;
    l->first  = l->current;
    freeNodeList(tmp);
}

void deleteCurrent(List* l, NodeList* prev)
{
    NodeList* tmp = l->current;
    if(isLast(l))
    {
        prev->next = l->current->next;
        l->current = prev; //On se replace juste avant la valeur trouvé
        l->last = l->current;
    }
    else
    {
        prev->next = l->current->next;
        l->current = prev; //On se replace juste avant la valeur trouvé
    }
    freeNodeList(tmp);
}

int deleteValue(List *l, char * name)
{
    NodeList* prev = NULL;
    if(find(l, name))
    {
        setOnFirst(l);
        while (!isOutOfList(l))
        {
            if(!strncmp(l->current->value.name, name, 512))
            {
                if(isFirst(l))
                {
                    deleteFirst(l);
                }
                else
                {
                    deleteCurrent(l, prev);
                }
                return 1;
            }
            prev = l->current;
            l->current = l->current->next;
        }
    }
    else
    {
        return 0;
    }
}

void freeList(List* l)
{
    while(!isEmpty(l))
    {
        deleteFirst(l);
    }
}

char * getCurrentPath (List * l)
{
    return l->current->value.path;
}
Date getCurrentDate (List * l)
{
    return l->current->value.date;
}
TypeMultimediaObject getCurrentType (List * l)
{
    return l->current->value.type;
}

int nbElement(List * l)
{
    int nb = 0;
    while (!isOutOfList(l))
    {
        setOnNext(l);
        nb++;
    }
    setOnFirst(l);
    return nb;
}

#include "test.h"
/*!
* \brief  Unit testing of the functions provided in the list.c file
*/
void test_list()
{
    List l1;
    int ret1;
    printf("Unit tests on teh list module\n");

    /*group 1*/
    initList(&l1);
    display_test_int("Test isEmpty() on an empty list",1,isEmpty(&l1));
    display_test_int("Test isOutOfList() when the list is empty",1,isOutOfList(&l1));
    display_test_string("Test getCurrentName() when the list is empty",NULL,getCurrentName(&l1));
    display_test_check_by_user("Test printList on an isEmpty list");
    printList(&l1);

    ret1 = insertFirst(&l1,"WEI","data/fish.jpg",10,10,2014,PHOTO);
    display_test_int("Test insertFirst() on an empty list",1,ret1);

    ret1 = insertFirst(&l1,"WEI2","data/fishAndTree.jpg",11,10,2014,PHOTO);
    display_test_int("Test insertFirst() on a not-empty list",1,ret1);
    display_test_check_by_user("Test insertFirst : (list should be with WEI2 and WEI)");
    printList(&l1);
    display_test_int("Test isEmpty() on an non-empty list",0,isEmpty(&l1));

    setOnLast(&l1);
    display_test_int("Test isLast() when  setOnLast",1,isLast(&l1));
    display_test_int("Test isFirst() when not on first",0,isFirst(&l1));
    display_test_int("Test isOutOfList() when  in the list",0,isOutOfList(&l1));
    display_test_string("Test getCurrentName() when in the list","WEI",getCurrentName(&l1));

    setOnNext(&l1);
    display_test_int("Test isOutOfList() when out of the non-empty list",1,isOutOfList(&l1));
    display_test_string("Test getCurrentName() when out of a non-empty list",NULL,getCurrentName(&l1));

    setOnFirst(&l1);
    display_test_int("Test isFirst() when setOnFirst ",1,isFirst(&l1));
    display_test_int("Test isLast() when  not on last",0,isLast(&l1));
    display_test_string("Test getCurrentName() when in the list","WEI2",getCurrentName(&l1));

    setOnNext(&l1);
    display_test_int("Test setOnNext()",1,isLast(&l1));

    /*group 2*/
    setOnFirst(&l1);
    display_test_int("Test find WEI", 1, find(&l1, "WEI"));

    /*group 3*/
    display_test_int("Test delete WEI", 1, deleteValue(&l1, "WEI"));
    display_test_int("Find WEI after it has benn deleted", 0, find(&l1, "WEI"));
    printList(&l1);

    /*group 4*/
    freeList(&l1);
    display_test_int("Test free list", 1, isEmpty(&l1));
    printList(&l1);
    /*group 5*/
}
