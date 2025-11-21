#include <stdio.h>
#include <string.h>

struct mois {
    char nom[9 + 1];
    int jours;
};

const struct mois tabMois[12] = {
    {"janvier",   31},
    {"fevrier",   28},
    {"mars",      31},
    {"avril",     30},
    {"mai",       31},
    {"juin",      30},
    {"juillet",   31},
    {"aout",      31},
    {"septembre", 30},
    {"octobre",   31},
    {"novembre",  30},
    {"decembre",  31}
};

int main(void) {
    char *ligne = NULL;
    size_t taille = 0;

    printf("Entrer un mois (Ex: janvier) : ");
    getline(&ligne, &taille, stdin);

    for (int i = 0; ligne[i] != '\0'; i++) {
        if (ligne[i] == '\n') {
            ligne[i] = '\0';
            break;
        }
    }

    int trouve = 0;
    for (int i = 0; i < 12; i++) {
        if (strcmp(ligne, tabMois[i].nom) == 0) {
            printf("Mois numéro : %d\n", i + 1);
            printf("Nombre de jours : %d\n", tabMois[i].jours);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        puts("mois invalide");
    }

    free(ligne);
    return 0;
}
