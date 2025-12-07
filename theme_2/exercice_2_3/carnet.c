#include "carnet.h"
#include <stdlib.h>

int lire_fiche(FILE *f, int index, fiche *p) {
    fseek(f, index * sizeof(fiche), SEEK_SET);
    return fread(p, sizeof(fiche), 1, f) == 1;
}

int ecrire_fiche(FILE *f, int index, fiche *p) {
    fseek(f, index * sizeof(fiche), SEEK_SET);
    return fwrite(p, sizeof(fiche), 1, f) == 1;
}

long nb_fiches(FILE *f) {
    fseek(f, 0, SEEK_END);
    return ftell(f) / sizeof(fiche);
}
