#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    int *tab = NULL;
    int size = 0;

    while ((nread = getline(&line, &len, stdin)) != -1) {
        int x = atoi(line);

        // resize array
        tab = realloc(tab, (size + 1) * sizeof(int));

        // insert x in sorted order
        int i = size - 1;
        while (i >= 0 && tab[i] > x) {
            tab[i + 1] = tab[i];
            i--;
        }
        tab[i + 1] = x;

        size++;
    }

    for (int i = 0; i < size; i++) {
        printf("%d\n", tab[i]);
    }

    free(tab);
    free(line);

    return 0;
}
