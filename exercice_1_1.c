// Afficher les valeurs de 2**i en utilisant printf
#include <stdio.h>
#include <math.h>
int main() {
    int i;
    int exponent;

    for (i = 0; i < 11; i++) {
        printf("2 exposant %d donne %d\n",
               i,
               exponent,
               pow( 2, exponent)
        );
        exponent += 1;

    }
    return(0);
}
