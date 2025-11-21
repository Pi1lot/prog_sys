// Afficher les valeurs de 2**i en utilisant printf
#include <stdio.h>
int main() {
    int value = 1;

    for (int i = 0; i < 10; i++) {
        printf("2 exposant %d ,%d\n", i, value);
        value *= 2;

    }
    return(0);
}
