#ifndef CARNET_H
#define CARNET_H

#include <stdio.h>

#define MAXNOM 50
#define MAXTEL 10

typedef struct fiche {
    int occupe;
    char nom[MAXNOM];
    char telephone[MAXTEL];
} fiche;

int lire_fiche(FILE *f, int index, fiche *p);
int ecrire_fiche(FILE *f, int index, fiche *p);
long nb_fiches(FILE *f);

#endif
