#include "IOFileManagerMO.h"
#include "fichier.h"

int processLinesFileManagerMO(FILE *f, ManagerMO *g, int (*ptFonction)(ManagerMO *,char *))
{
  int cpt=0;         /* Compteur du nombre de lignes */
  char tampon[TMAX]; /* Tampon de lecture d’une ligne */

  rewind(f);         /* Remise en début du fichier */

    /* Boucle de lecture des lignes */
  while (lireLigneFichier(f,tampon,TMAX)){
    cpt++;
    if (ptFonction!=NULL)
      (*ptFonction)(g,tampon); /* Application d’un traitement à chaque ligne */
    else printf("%s",tampon);/* Traitement par défaut */
  }

  //printf("nombre de lignes: %d\n",cpt); /* Affichage du nombre de lignes */
  return cpt;
}


int readOMFromString (ManagerMO * g, char *s)
{
    char reste[TMAX];
    char name[MY_NAME_MAX];
    char path[MY_PATH_MAX];
    Date date;
    TypeMultimediaObject type;

    int retour ;

    retour = sscanf(s,"%[^;];%[^;];%d/%d/%d;%d%[ \r\n]",
               name, path, &date.day, &date.month, &date.year, (int *)&type,reste);
    if(retour != 7)
        return 0;

    addMO(g,name,path,date.day,date.month,date.year,type);

    return 1;
}


int fillManagerMO(char *name, ManagerMO *g )
{
    FILE * f = NULL;


    initManagerMO(g);
    f = ouvrirFichier(name, "r",ARRET);
    if(f==NULL)
        return 0;

    processLinesFileManagerMO(f,g,readOMFromString);

    g->modified = MYFALSE;
    fermerFichier(f);
    return 1;
}

int closeManagerMO(ManagerMO *g )
{
    int code_retour =1;
    if(g->modified == MYTRUE)
    {
        char sauver ='\0';
        printf("La liste des objets multimédia a été modifiée.\n");
        do{
            printf("Souhaitez-vous la sauvegarder?(o/n)\n");
            scanf("%c",&sauver);
        }while(sauver!='o'&& sauver!= 'n');
        if(sauver == 'o')
        {
            char name[MY_NAME_MAX];
            printf("Donnez le name du fichier de sauvegarde\n");
            scanf("%s",name);
            code_retour = saveManagerMO(name,g);
            if(code_retour !=1)
            {
                fprintf(stderr,"Probleme lors de la sauvegarde du gestionnaire d'objets multimedia -> abandon\n");
                return code_retour;
            }
        }
    }
    clearManagerMO(g);
    return code_retour;
}


int saveManagerMO(char * name, ManagerMO * g)
{
    FILE * f ;
    f = ouvrirFichier(name,"w",ARRET);
    if(f==NULL)
        return 0;
    for(start(g);!end(g);next(g))
    {
        fprintf(f,"%s;%s;%d/%d/%d;%d\n",
               getNameCurrentMO(g), getPathCurrentMO(g),
              getDateCurrentMO(g).day, getDateCurrentMO(g).month, getDateCurrentMO(g).year,
               getTypeCurrentMO(g));
    }
    fermerFichier(f);
    return 1;
}
