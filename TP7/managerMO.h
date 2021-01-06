#ifndef MANAGERMO_INC_H
#define MANAGERMO_INC_H


#ifdef MY_USE_LIST
#include "managerMO-SDD-list.h"
#endif
#ifdef MY_USE_ARRAY
#include "managerMO-SDD-array.h"
#endif

void initManagerMO(ManagerMO* g);
void clearManagerMO(ManagerMO* g);
int addMO(ManagerMO* g,char * name, char * path, int day, int month, int year, TypeMultimediaObject type);
int removeMO(ManagerMO* g,char * name);


MyBoolean isModified(ManagerMO *g);
int nbObject(ManagerMO* g);


void start(ManagerMO *g);
MyBoolean end(ManagerMO *g);
void next(ManagerMO *g);

char * getNameCurrentMO(ManagerMO *g);
MyBoolean isPhotoCurrentMO(ManagerMO *g);
char * getPathCurrentMO(ManagerMO *g);
Date getDateCurrentMO(ManagerMO *g);
TypeMultimediaObject getTypeCurrentMO(ManagerMO *g);
void changeNameCurrentMO(ManagerMO *g, char * name);

MyBoolean findMO(ManagerMO *g, char * name);


#endif /* MULTIMEDIAOBJECTS_H*/
