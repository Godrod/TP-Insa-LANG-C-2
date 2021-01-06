
#include "callback-functions-managerMO.h"
#include "player-gtk-types.h"
#include "IOFileManagerMO.h"
#include "managerMO.h"
#include <stdlib.h>
#include <string.h>


void delete_from_click_cb( GtkWidget *widget, gpointer   user_data )
{
    GtkWidget *toplevel = user_data;
    g_signal_emit_by_name(G_OBJECT(toplevel),"delete_event");
}


gint delete_cb( GtkWidget *widget, GdkEvent  *event, gpointer   user_data )
{
    ManagerMO * manager = user_data;
    GtkWidget *toplevel = gtk_widget_get_toplevel (widget);

    if(gtk_widget_is_toplevel (toplevel) && (isModified(manager) == MYTRUE ))
    {

        /* Change TRUE to FALSE and the main window will be destroyed with
         * a "delete_event". */
        GtkWidget * pDialog = NULL;
        GtkWidget* pVBox = NULL;
        GtkWidget * pLabel = NULL;

        /*Initialisation de la boîte de dialogue avec texte et boutons*/
        pDialog = gtk_dialog_new_with_buttons("Attention!",GTK_WINDOW(toplevel), GTK_DIALOG_MODAL,
                                                                  "Yes", GTK_RESPONSE_YES,
                                                                  "No", GTK_RESPONSE_NO,
                                                                  NULL);
        pVBox = gtk_dialog_get_content_area(GTK_DIALOG(pDialog));
        pLabel = gtk_label_new("\n The set of multimedia objects has been modified. \n Do  you want to save it in the file save-by-player.txt?\n");
        gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, TRUE, 0);
        gtk_widget_show_all (pVBox);

        /* On lance la boite de dialogue et on récupére la réponse */
        switch (gtk_dialog_run(GTK_DIALOG(pDialog)))
        {
            /* on sauvegarde */
            case GTK_RESPONSE_YES:
                saveManagerMO("data/save-by-player.txt",manager);
                break;

            /* on ne sauvegarde pas et on quitte l'appli */
            case GTK_RESPONSE_NO:
                    break;

            /* on ne sauvegarde pas et on ne quitte pas l'appli */
            default:
                /* Destruction de la boite de dialogue */
                gtk_widget_destroy(pDialog);
                return TRUE;
        }

            g_signal_emit_by_name(G_OBJECT(toplevel),"destroy"); /*nécessaire pour appeler destroy_cb si on est passé par le bouton "Quitter"*/
        return FALSE;

    }
    else
    {
        if (gtk_widget_is_toplevel (toplevel))
          {
           g_signal_emit_by_name(G_OBJECT(toplevel),"destroy");/*nécessaire pour appeler destroy_cb si on est passé par le bouton "Quitter"*/
          }
        return FALSE;
    }
}

void destroy_cb( GtkWidget *widget, gpointer   user_data )
{
    /*desallocation mémoire*/
    ManagerMO * manager = user_data;
    clearManagerMO(manager);
    gtk_widget_destroy(widget);

}

#ifdef DRAW_HISTO
void drawHisto_cb(GtkWidget *drawing_area, cairo_t *cr2, gpointer user_data)
{
    cairo_t * cr = NULL;
    GdkWindow *DefaultWindow = gtk_widget_get_window(GTK_WIDGET(drawing_area));

    MyIntArray * pHisto  = NULL;

    cr = gdk_cairo_create (DefaultWindow);
    cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
    cairo_set_line_width (cr, 1.0);

    pHisto = user_data;
    if(pHisto == NULL || pHisto-> nb <= 0 || pHisto->data == NULL)
    {
        /*on ne dessine rien*/
    }
    else
    {
        /*on dessine l'histogramme*/
        guint width, height;
        int i;
        int ymax, ymin;
        float rect_width;

        width = gtk_widget_get_allocated_width (drawing_area);
        height = gtk_widget_get_allocated_height (drawing_area);
        rect_width = width/(pHisto->nb+1);
        ymax = ymin = pHisto->data[0];
        for ( i=1 ; i < pHisto->nb ; i++ )
        {
            ymax = (ymax < pHisto->data[i])? pHisto->data[i]: ymax;
            ymin = (ymin > pHisto->data[i])? pHisto->data[i]: ymin;
        }
        if(ymax > 0)
        {
            /*printf("width %d, heigth %d et rect_width %f \n",width,height,rect_width);*/
            for ( i=0 ; i < pHisto->nb ; i++ )
            {
                cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 1);
                cairo_rectangle (cr,  (i+1)*rect_width, height - height*pHisto->data[i]/ymax, 1,  height*pHisto->data[i]/ymax);
                cairo_fill(cr);
                cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 1.0);
                cairo_stroke(cr);
             }
        }
    }
    cairo_stroke(cr);
    cairo_destroy(cr);
}
#endif
void updateEditedName_cb(GtkCellRendererText *renderer, gchar *path, gchar *new_text, gpointer user_data)
{
    //int i;
    GtkTreeIter iter;
    updateEditedName_cb_parameter *pParamUpdate = user_data;
    ManagerMO *manager = pParamUpdate->manager;
    GtkListStore * store = pParamUpdate->store;
    GValue new_val = G_VALUE_INIT;
    g_value_init(&new_val, G_TYPE_STRING);
    g_value_set_string (&new_val,new_text);


    //i = path[0]-'0';
    gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL (store),&iter,path);
    gtk_list_store_set_value(store,&iter,NAME_COLUMN,&new_val);

    //changeName(manager,i,new_text);
    changeNameCurrentMO(manager,new_text);

}



void objectListSelectionChanged_cb (GtkTreeSelection *selection, gpointer user_data)
{
        GtkTreeIter iter;
        GtkTreeModel *model = NULL;
        gchar *name = NULL;
        gchar *filename = NULL;
        gboolean type;
        objectListSelectionChanged_cb_parameter * pParam;
        ManagerMO * manager = NULL;
#ifdef DRAW_HISTO
        MyIntArray * pHisto = NULL;
        GtkWidget * drawing_area = NULL;
        int width_h,height_h;
        int i;
#endif

        if (gtk_tree_selection_get_selected (selection, &model, &iter))
        {

            GtkWidget * pImage = NULL;

            gtk_tree_model_get (model, &iter, NAME_COLUMN, &name, -1);
            gtk_tree_model_get (model, &iter, TYPE_COLUMN, &type, -1);
            gtk_tree_model_get (model, &iter, FILE_COLUMN, &filename, -1);


            /*g_print ("You selected the object %s located at %s\n", name,filename);*/

            pParam = user_data;
            /*On récupère le manager pour changer l'élément courant (nécessaire pour une édition du nom éventuelle par la suite*/
            manager = pParam->manager;
            if(manager != NULL)
                findMO(manager,name);

#ifdef DRAW_HISTO
            /* On récupère le pointeur vers l'histo passé en paramètre*/
            /*Si image pas trouvée ou si objet pas de type photo, histo mis à 0*/
            pHisto = pParam->pHisto;
#endif
            /* On récupère le pointeur vers l'image passée en paramètre*/
            pImage = pParam->pImage;
            if (!GTK_IMAGE(pImage))
                         fprintf(stderr,"Dans tree_selection_changed_cb(...): le widget spécifié n'est pas un GtkImage !\n\n");
            else
            {
                /*Si c'est une photo, on va l'afficher dans la fenêtre à droite*/
                if(type == MYTRUE)
                {
#ifdef DRAW_HISTO
                    GdkPixbuf * pPixbuf = NULL;
#endif
                    /* Chargement de la nouvelle image*/
                    gtk_image_set_from_file(GTK_IMAGE(pImage), filename);

#ifdef DRAW_HISTO
                    /*Calcul niveaux de gris*/
                    pPixbuf = gtk_image_get_pixbuf (GTK_IMAGE(pImage));

                    if(pPixbuf!=NULL)
                    {
                        int width,height;
                        int x,y;
                        guchar red,blue,green;
                        MyGreyLevelImage * pImageGrey = NULL;

                        width = gdk_pixbuf_get_width (pPixbuf);
                        height = gdk_pixbuf_get_height (pPixbuf);


                         pImageGrey = pParam->pImageGrey;
                        pImageGrey->nb = width*height;
                        pImageGrey->data =(unsigned char*)realloc(pImageGrey->data,sizeof(unsigned char)*pImageGrey->nb);

                        i=0;
                        for(x=0 ; x<width ; x++)
                            for(y=0 ; y<height ; y++)
                            {
                                gdkpixbuf_get_colors_by_coordinates(pPixbuf,x,y,&red,&green,&blue);
                                pImageGrey->data[i] = getGreyValueFromRGB(red,green,blue);
                                i++;
                            }
                        /*Calcul de l'histogramme*/
                        histoUC(pImageGrey->data,pImageGrey->nb, pHisto->data, pHisto->nb);
                    }
                    else
                    {

                        /*Vidage de l'histogramme*/
                        for(i=0; i<pHisto->nb ;i++)
                        {
                            pHisto->data[i] = 0;
                        }
                    }
#endif
                }
                else
                {
                    char cmd[512];

                    /*Sinon, chargement d'une image d'avertissement dans la fenêtre à droite+ lancement d'une appli externe*/
                    gtk_image_set_from_file(GTK_IMAGE(pImage), "not-a-photo.jpg");

                    sprintf(cmd,"totem %s",filename);

                    system(cmd);

#ifdef DRAW_HISTO
                    /*Vidage de l'histogramme*/
                    for(i=0; i<pHisto->nb ;i++)
                    {
                        pHisto->data[i] = 0;
                    }
#endif
                }

#ifdef DRAW_HISTO
                /*Affichage de l'histo*/
                drawing_area = pParam->pHistoDraw;
                width_h = gtk_widget_get_allocated_width (drawing_area);
                height_h = gtk_widget_get_allocated_height (drawing_area);
                gtk_widget_queue_draw_area(drawing_area,0,0,width_h,height_h);
#endif

            }

            g_free (name);
            g_free (filename);
        }
}

gboolean gdkpixbuf_get_colors_by_coordinates(GdkPixbuf *pixbuf, gint x, gint y, guchar *red, guchar *green, guchar *blue)
{
  guchar *pixel=NULL;
  gint channel=0;
  gint width=0;

  if (!pixbuf) return FALSE;
  if (x<0 || y<0) return FALSE;
  if (x>gdk_pixbuf_get_width(pixbuf)) return FALSE;
  if (y>gdk_pixbuf_get_height(pixbuf)) return FALSE;

  pixel=gdk_pixbuf_get_pixels(pixbuf);
  channel=gdk_pixbuf_get_n_channels(pixbuf);
  width=gdk_pixbuf_get_width(pixbuf);

  *red   = pixel[(x*channel)+(y*width*channel)];
  *green = pixel[(x*channel)+(y*width*channel)+1];
  *blue  = pixel[(x*channel)+(y*width*channel)+2];

  return MYTRUE;
}


unsigned char getGreyValueFromRGB(guchar R, guchar G, guchar B)
{return (unsigned char) (R*0.299 + G*0.587 + B*0.114);}
