#ifndef FILE_MANAGERMO_INC_H
#define FILE_MANAGERMO_INC_H
#include "managerMO.h"
#include <stdio.h>

int fillManagerMO(char *name, ManagerMO *g );


int saveManagerMO (char * name, ManagerMO * g);


int processLinesFileManagerMO(FILE *f, ManagerMO *g, int (*ptFonction)(ManagerMO*, char *));
int readOMFromString (ManagerMO *g,char *s);
int closeManagerMO(ManagerMO *g );


#endif /* FILE_MANAGERMO_INC_H*/
