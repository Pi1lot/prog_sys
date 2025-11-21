#include <stdio.h>

int main(void) {
    int c;
    int word = 0;

    while ((c = getchar()) != '\n') {

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            word = 1;
            putchar(c);
        } else {
            if (word) {
                putchar('\n');
            }
            word = 0;
        }
    }

    if (word) {
        putchar('\n');
    }

    return 0;
}
