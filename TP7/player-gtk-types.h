#ifndef PLAYER_GTK_TYPES_INC_H
#define PLAYER_GTK_TYPES_INC_H

#include <gtk/gtk.h>

#include "managerMO.h"

/*To be declared if the histogram of grey level has to be displayed*/
//#define DRAW_HISTO


enum
{
   NAME_COLUMN,
   TYPE_COLUMN,
   FILE_COLUMN,
   N_COLUMNS
};


typedef struct {
    int * data;
    int nb;
}MyIntArray;


typedef struct {
    unsigned char * data;
    int nb;
}MyGreyLevelImage;


typedef struct {
    GtkListStore * store;
    ManagerMO * manager;
}updateEditedName_cb_parameter;


typedef struct {
    GtkWidget * pImage;
    ManagerMO * manager;
#ifdef DRAW_HISTO
    MyIntArray * pHisto;
    MyGreyLevelImage * pImageGrey;
    GtkWidget * pHistoDraw;
#endif
}objectListSelectionChanged_cb_parameter;


#endif /* PLAYER_GTK_TYPES_INC_H*/
