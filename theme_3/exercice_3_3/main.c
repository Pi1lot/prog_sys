#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    char **tab = NULL;
    int size = 0;

    while ((nread = getline(&line, &len, stdin)) != -1) {
        //remove final newline
        if (line[nread - 1] == '\n') line[nread - 1] = '\0';

        //reallocate array
        tab = realloc(tab, (size + 1) * sizeof(char*));
        char *s = strdup(line);

        //insert s in sorted order
        int i = size - 1;
        while (i >= 0 && strcmp(tab[i], s) > 0) {
            tab[i + 1] = tab[i];
            i--;
        }
        tab[i + 1] = s;

        size++;
    }

    for (int i = 0; i < size; i++) {
        printf("%s\n", tab[i]);
        free(tab[i]);
    }

    free(tab);
    free(line);

    return 0;
}
