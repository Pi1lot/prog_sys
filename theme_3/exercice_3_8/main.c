#include <stdio.h>

/* read at most max_elem doubles from stdin into array, store count in nb_elem */
/* returns 0 on success, -1 on error */
int read_array(double *array, int max_elem, int *nb_elem)
{
    int i = 0;
    double x;
    while (i < max_elem && scanf("%lf", &x) == 1) {
        array[i] = x;
        i++;
    }

    if (i == 0 && !feof(stdin)) return -1;

    *nb_elem = i;
    return 0;
}

// simple bubble sort
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

// print nb_elem doubles
void print_array(double *array, int nb_elem)
{
    for (int i = 0; i < nb_elem; i++) {
        printf("%f\n", array[i]);
    }
}

int main(void)
{
    double tab[100];
    int nb;

    if (read_array(tab, 100, &nb) != 0) {
        fprintf(stderr, "Error reading numbers\n");
        return 1;
    }

    sort_array(tab, nb);
    print_array(tab, nb);

    return 0;
}
