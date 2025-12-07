#include "carnet.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2)
        return 0;

    char *nom = argv[1];
    FILE *f = fopen("carnet.bin", "rb");
    if (!f) return 0;

    fiche p;
    long n = nb_fiches(f);

    for (long i = 0; i < n; i++) {
        lire_fiche(f, i, &p);
        if (p.occupe && strcmp(p.nom, nom) == 0) {
            printf("%ld\n", i);
            break;
        }
    }

    fclose(f);
    return 0;
}
