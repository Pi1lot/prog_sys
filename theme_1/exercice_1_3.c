#include <stdio.h>

int main(void) {
    int c;
    int word = 0;
    int nb_mots = 0;

    printf("Saisir phrase (ctrl d pour stopper) :\n");

    while ((c = getchar()) != EOF) {

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (!word) {

                word = 1;
                nb_mots++;
            }
        } else {
            word = 0;
        }
    }

    printf("Nombre de mots : %d\n", nb_mots);

    return 0;
}
