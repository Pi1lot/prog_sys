#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *entree = NULL;
    size_t taille = 0;

    printf("Entrer une chaîne:\n");
    getline(&entree, &taille, stdin);

    char sortie[4096];
    int k = 0;

    for (int i = 0; entree[i] != '\0'; i++) {
        unsigned char c = entree[i];

        switch (c) {
            case '\n':
                sortie[k++] = '\\';
                sortie[k++] = 'n';
                break;

            case '\t':
                sortie[k++] = '\\';
                sortie[k++] = 't';
                break;

            case '\r':
                sortie[k++] = '\\';
                sortie[k++] = 'r';
                break;

            case '\b':
                sortie[k++] = '\\';
                sortie[k++] = 'b';
                break;

            case '\\':
                sortie[k++] = '\\';
                sortie[k++] = '\\';
                break;

            case '\"':
                sortie[k++] = '\\';
                sortie[k++] = '\"';
                break;

            case '\'':
                sortie[k++] = '\\';
                sortie[k++] = '\'';
                break;

            default:
                if (c >= 32 && c <= 126) {
                    sortie[k++] = c;
                } else {
                    sortie[k++] = '\\';
                    sortie[k++] = (char)('0' + ((c >> 6) & 7));
                    sortie[k++] = (char)('0' + ((c >> 3) & 7));
                    sortie[k++] = (char)('0' + (c & 7));
                }
        }
    }

    sortie[k] = '\0';

    printf("C:\n%s\n", sortie);

    free(entree);
    return 0;
}
