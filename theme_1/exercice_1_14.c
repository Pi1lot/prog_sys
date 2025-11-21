#include <stdio.h>
#include <stdlib.h>

unsigned int lire_16(void) {
    char *ligne = NULL;
    size_t taille = 0;
    unsigned int res = 0;

    printf("hexadécimal value: ");
    getline(&ligne, &taille, stdin);

    for (int i = 0; ligne[i] != '\0' && ligne[i] != '\n'; i++) {
        char c = ligne[i];
        unsigned int val = 0;

        if (c >= '0' && c <= '9') {
            val = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            val = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            val = c - 'a' + 10;
        } else {
            printf("Invalid char: %c\n", c);
            free(ligne);
            return 0;
        }

        //Décalage de 4bits
        res = (res << 4) + val;
    }

    free(ligne);
    return res;
}

int main(void) {
    unsigned int n = lire_16();
    printf("Decimal value: %u\n", n);
    return 0;
}

