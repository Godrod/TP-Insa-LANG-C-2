#include "multimedia-object.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static Date createDate(int j, int m, int a)
{
    Date d;
    d.year = a;
    d.day = j;
    d. month = m;
    return d;
}

void fillMO (MultimediaObject * o, char * name, char * path, int day, int month, int year, TypeMultimediaObject type)
{
    if(o !=NULL)
    {
        o->date.day = day;
        o->date.month= month;
        o->date.year = year;
        changeNameMO(o, name);
        snprintf(o->path, 512, path);
        o->type = type;
    }
    else
    {
        fprintf(stderr, "The object given in parameter is NULL");
        exit(1);
    }
}

void changeNameMO(MultimediaObject* o, char* new_name)
{
    snprintf(o->name, 512, new_name);
}

#include "test.h"
/*!
* \brief  Unit testing of the functions provided in the multimedia-object.c file
*/
void test_MO()
{
	printf("Tests unitaires du module multimedia-object :\n");
	MultimediaObject o;

    fillMO(&o, "test_object", "/home/cfleury/test_file", 27, 11, 2020, PHOTO);

    display_test_int("Test object day", 27, o.date.day);
    display_test_int("Test object month", 11, o.date.month);
    display_test_int("Test object year", 2020, o.date.year);
    display_test_string("Test object name", "test_object", o.name);
    display_test_string("Test object path", "/home/cfleury/test_file", o.path);
    display_test_check_by_user("Test object type. Should return 1 ");
    printf("%d\n", (o.type == PHOTO) ? 1 : 0);

    changeNameMO(&o, "new_name");
    display_test_string("Test changeNameMO: ", "new_name", o.name);

}

