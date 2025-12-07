#include "carnet.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2)
        return 0;

    int index = atoi(argv[1]);
    FILE *f = fopen("carnet.bin", "rb");
    if (!f) return 0;

    fiche p;
    if (lire_fiche(f, index, &p) && p.occupe) {
        printf("Fiche %d :\nNom : %s\nTelephone : %s\n",
               index, p.nom, p.telephone);
    }

    fclose(f);
    return 0;
}
