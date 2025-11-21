#include <stdio.h>

void ecrire_2(unsigned int n) {
    int start = 0;

    for (int i = sizeof(unsigned int) * 8 - 1; i >= 0; i--) {
        if (n & (1u << i)) {
            putchar('1');
            start = 1;
        } else {
            if (start) putchar('0');
        }
    }
    if (!start) putchar('0');

    putchar('\n');
}

int main(void) {
    unsigned int x = 37;
    ecrire_2(x);         
}
