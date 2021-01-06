#ifndef CALLBACK_FUNCTIONS_MANAGERMO_INC_H
#define CALLBACK_FUNCTIONS_MANAGERMO_INC_H

#include <gtk/gtk.h>

gint delete_cb( GtkWidget *widget, GdkEvent  *event, gpointer   user_data );
void delete_from_click_cb( GtkWidget *widget, gpointer   user_data );

void destroy_cb( GtkWidget *widget, gpointer   user_data );

void drawHisto_cb(GtkWidget *drawing_area, cairo_t *cr, gpointer user_data);

void updateEditedName_cb(GtkCellRendererText *renderer, gchar *path, gchar *new_text, gpointer user_data);

void objectListSelectionChanged_cb (GtkTreeSelection *selection, gpointer user_data);

gboolean gdkpixbuf_get_colors_by_coordinates(GdkPixbuf *pixbuf, gint x, gint y, guchar *red, guchar *green, guchar *blue);


unsigned char getGreyValueFromRGB(guchar R, guchar G, guchar B);

#endif /* CALLBACK_FUNCTIONS_MANAGERMO_INC_H*/
