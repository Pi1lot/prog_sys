#include "carnet.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3)
        return 0;

    char *nom = argv[1];
    char *tel = argv[2];

    FILE *f = fopen("carnet.bin", "r+b");
    if (!f) f = fopen("carnet.bin", "w+b");
    if (!f) return 1;

    fiche p;
    long n = nb_fiches(f);

    for (long i = 0; i < n; i++) {
        lire_fiche(f, i, &p);
        if (!p.occupe) {
            p.occupe = 1;
            strncpy(p.nom, nom, MAXNOM);
            strncpy(p.telephone, tel, MAXTEL);
            ecrire_fiche(f, i, &p);
            fclose(f);
            return 0;
        }
    }

    p.occupe = 1;
    strncpy(p.nom, nom, MAXNOM);
    strncpy(p.telephone, tel, MAXTEL);

    ecrire_fiche(f, n, &p);

    fclose(f);
    return 0;
}
