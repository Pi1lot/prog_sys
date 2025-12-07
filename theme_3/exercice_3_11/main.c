#include <stdio.h>
#include <stdlib.h>

/* read doubles from stdin into a dynamically allocated array */
/* *array will point to the allocated array, nb_elem stores the number of elements */
/* returns 0 on success, -1 on error */
int read_array(double **array, int *nb_elem)
{
    int n = 100;  // initial allocation
    double *tab = calloc(n, sizeof(double));
    if (tab == NULL) return -1;

    int count = 0;
    double x;

    while (scanf("%lf", &x) == 1) {
        if (count == n) {
            int new_n = 2 * n;
            double *new_tab = calloc(new_n, sizeof(double));
            if (new_tab == NULL) {
                free(tab);
                return -1;
            }
            // copy old values
            for (int i = 0; i < n; i++) {
                new_tab[i] = tab[i];
            }
            free(tab);
            tab = new_tab;
            n = new_n;
        }
        tab[count] = x;
        count++;
    }

    if (count == 0 && !feof(stdin)) {
        free(tab);
        return -1;
    }

    *array = tab;
    *nb_elem = count;
    return 0;
}

/* simple bubble sort */
void sort_array(double *array, int nb_elem)
{
    for (int i = 0; i < nb_elem - 1; i++) {
        for (int j = 0; j < nb_elem - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                double temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

/* print nb_elem doubles */
void print_array(double *array, int nb_elem)
{
    for (int i = 0; i < nb_elem; i++) {
        printf("%f\n", array[i]);
    }
}

int main(void)
{
    double *tab = NULL;
    int nb;

    if (read_array(&tab, &nb) != 0) {
        fprintf(stderr, "Error reading numbers\n");
        return 1;
    }

    sort_array(tab, nb);
    print_array(tab, nb);

    free(tab);
    return 0;
}
