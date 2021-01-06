#ifndef MANAGERMOSDDLIST_H
#define MANAGERMOSDDLIST_H

#include "commun.h"
#include "listMO.h"
typedef struct{
    List data; /*!The list of multimedia objects<*/
    MyBoolean modified; /*!< a flag to knows if the data was modifies since it was loaded*/
}ManagerMO;

#endif // MANAGERMOSDDLIST_H
