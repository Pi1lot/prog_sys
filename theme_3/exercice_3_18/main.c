#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generic quicksort for array of void* */
void quicksort(void *tab[], int debut, int fin, int (*comp)(void*, void*)) {
    if (debut >= fin) return;
    void *pivot = tab[fin];
    int i = debut - 1;
    for (int j = debut; j < fin; j++) {
        if (comp(tab[j], pivot) <= 0) {
            i++;
            void *tmp = tab[i];
            tab[i] = tab[j];
            tab[j] = tmp;
        }
    }
    void *tmp = tab[i+1];
    tab[i+1] = tab[fin];
    tab[fin] = tmp;
    quicksort(tab, debut, i, comp);
    quicksort(tab, i+2, fin, comp);
}

/* Compare doubles */
int comp_double(void *a, void *b) {
    double da = *(double*)a;
    double db = *(double*)b;
    return (da < db) ? -1 : (da > db) ? 1 : 0;
}

/* Compare strings */
int comp_string(void *a, void *b) {
    return strcmp((char*)a, (char*)b);
}

int main(void) {
    int choice;
    printf("Choose type to sort (1 = doubles, 2 = strings): ");
    if (scanf("%d", &choice) != 1) return 1;
    getchar(); // consume newline

    void *tab[10000]; // array of pointers for sorting
    int n = 0;

    if (choice == 1) {
        double doubles[10000];
        double x;
        printf("Enter doubles (one per line, Ctrl+D to end):\n");
        while (n < 10000 && scanf("%lf", &x) == 1) {
            doubles[n] = x;
            tab[n] = &doubles[n]; // store pointer to double
            n++;
        }

        quicksort(tab, 0, n-1, comp_double);

        printf("Sorted doubles:\n");
        for (int i = 0; i < n; i++)
            printf("%f\n", *(double*)tab[i]);

    } else if (choice == 2) {
        char buffer[1000];
        printf("Enter strings (one per line, Ctrl+D to end):\n");
        while (n < 10000 && fgets(buffer, sizeof(buffer), stdin)) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
            if (strlen(buffer) == 0) continue; // skip empty lines

            char *str = strdup(buffer); // allocate string
            if (!str) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            tab[n] = str; // store pointer
            n++;
        }

        quicksort(tab, 0, n-1, comp_string);

        printf("Sorted strings:\n");
        for (int i = 0; i < n; i++) {
            printf("%s\n", (char*)tab[i]);
            free(tab[i]); // free allocated string
        }

    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    return 0;
}
