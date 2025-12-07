#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* split a string by ':' into an array of strings */
/* returns number of elements, *count stores the number of strings */
char **split_path(const char *path, int *count)
{
    if (!path) {
        *count = 0;
        return NULL;
    }

    /* count number of ':' to estimate array size */
    int n = 1;
    for (const char *p = path; *p; p++) {
        if (*p == ':') n++;
    }

    char **array = malloc(n * sizeof(char *));
    if (!array) {
        *count = 0;
        return NULL;
    }

    char *copy = strdup(path);
    if (!copy) {
        free(array);
        *count = 0;
        return NULL;
    }

    int idx = 0;
    char *token = strtok(copy, ":");
    while (token) {
        array[idx++] = strdup(token);
        token = strtok(NULL, ":");
    }

    *count = idx;
    free(copy);
    return array;
}

/* free the array of strings */
void free_split(char **array, int count)
{
    for (int i = 0; i < count; i++) {
        free(array[i]);
    }
    free(array);
}

int main(void)
{
    char *path_env = getenv("PATH");
    if (!path_env) {
        fprintf(stderr, "PATH variable not found.\n");
        return 1;
    }

    int count;
    char **paths = split_path(path_env, &count);
    if (!paths) {
        fprintf(stderr, "Failed to split PATH.\n");
        return 1;
    }

    printf("PATH components:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", paths[i]);
    }

    free_split(paths, count);
    return 0;
}
