
#include "fichier.h"

FILE *ouvrirFichier(char *name, char *mode, TypeRetour t){
  FILE * pFile=NULL; /* Descripteur du fichier */

  pFile = fopen (name,mode);
  if (pFile==NULL) {
    perror (name);
    /* Gestion de la fin de la fonction */
    if (t==ARRET)
      exit(EXIT_FAILURE);
  }
  return pFile;
}

void fermerFichier(FILE *f){
  fclose(f);
}

char *lireLigneFichier(FILE *f, char *tampon, int taille){
  return fgets(tampon,taille,f);
}

int traiterLignesFichier(FILE *f, int (*ptFonction)(char *)){
  int cpt=0;         /* Compteur du namebre de lignes */
  char tampon[TMAX]; /* Tampon de lecture d’une ligne */

  rewind(f);         /* Remise en début du fichier */

    /* Boucle de lecture des lignes */
  while (lireLigneFichier(f,tampon,TMAX)){
    cpt++;
    if (ptFonction!=NULL)
      (*ptFonction)(tampon); /* Application d’un traitement à chaque ligne */
    else printf("%s",tampon);/* Traitement par défaut */
  }

  printf("namebre de lignes: %d\n",cpt); /* Affichage du namebre de lignes */
  return cpt;
}
