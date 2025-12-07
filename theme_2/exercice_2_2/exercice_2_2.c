#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int c;
    int count = 0;

    char target = '\n';

    if (argc > 1) {
        target = argv[1][0];
    }

    while ((c = getchar()) != '\n') {
        if (c == target) {
            count++;
        }
    }

    printf("Occurrences '%c' : %d\n", target, count);
    return 0;
}

