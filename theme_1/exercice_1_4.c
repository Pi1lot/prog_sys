#include <stdio.h>

int main(void) {
    int c;
    int dans_un_mot = 0;   /* 1 = on lit un mot, 0 = on est entre deux mots */

    while ((c = getchar()) != EOF) {

        /* Si c'est une lettre */
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            dans_un_mot = 1;
            putchar(c);      /* on affiche la lettre */
        } else {
            /* Si on sort d'un mot, on termine la ligne */
            if (dans_un_mot) {
                putchar('\n');
            }
            dans_un_mot = 0;
        }
    }

    /* Si le texte se termine au milieu d'un mot, on met quand même un \n */
    if (dans_un_mot) {
        putchar('\n');
    }

    return 0;
}
