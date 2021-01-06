#include "managerMO.h"
#include "listMO.h"
void initManagerMO(ManagerMO* g)
{
    initList(&g->data);
}
void clearManagerMO(ManagerMO* g)
{
    start(g);
    freeList(&g->data);
    g->modified = MYTRUE;
}
int addMO(ManagerMO* g,char * name, char * path, int day, int month, int year, TypeMultimediaObject type)
{
    g->modified = MYTRUE;
    return insertFirst(&g->data, name, path, day, month, year, type);
}
int removeMO(ManagerMO* g,char * name)
{
    g->modified = MYTRUE;
    return deleteValue(&g->data, name);
}

MyBoolean isModified(ManagerMO* g)
{
    return g->modified;
}

int nbObject(ManagerMO* g)
{
    return nbElement(&g->data);
}

void start(ManagerMO *g)
{
    setOnFirst(&g->data);
}
MyBoolean end(ManagerMO *g)
{
    if (isOutOfList(&g->data))
        return MYTRUE;
    else
        return MYFALSE;
}
void next(ManagerMO *g)
{
    setOnNext(&g->data);
}

char * getNameCurrentMO(ManagerMO *g)
{
    return getCurrentPath(&g->data);
}

MyBoolean isPhotoCurrentMO(ManagerMO *g)
{
    if(getCurrentType(&g->data) == PHOTO)
        return MYTRUE;
    else
        return MYFALSE;
}

char * getPathCurrentMO(ManagerMO *g)
{
    return getCurrentPath(&g->data);
}

Date getDateCurrentMO(ManagerMO *g)
{
    return getCurrentDate(&g->data);
}
TypeMultimediaObject getTypeCurrentMO(ManagerMO *g)
{
    return getCurrentType(&g->data);
}
void changeNameCurrentMO(ManagerMO *g, char * name)
{
    changeNameMO(&g->data.current->value, name);
}

MyBoolean findMO(ManagerMO *g, char * name)
{
    if(find(&g->data, name) == 1)
        return MYTRUE;
    else
        return MYFALSE;
}
