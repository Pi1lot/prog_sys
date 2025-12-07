#include <stdio.h>

/* read at most max_elem integers from stdin into array, store count in nb_elem */
/* returns 0 on success, -1 on error */
int read_array(int *array, int max_elem, int *nb_elem)
{
    int i = 0;
    int x;
    while (i < max_elem && scanf("%d", &x) == 1) {
        *(array + i) = x;  // store value without using []
        i++;
    }

    if (i == 0 && !feof(stdin)) return -1;

    *nb_elem = i;
    return 0;
}

/* simple bubble sort using pointer arithmetic */
void sort_array(int *array, int nb_elem)
{
    int i, j;
    for (i = 0; i < nb_elem - 1; i++) {
        for (j = 0; j < nb_elem - i - 1; j++) {
            if (*(array + j) > *(array + j + 1)) {
                int temp = *(array + j);
                *(array + j) = *(array + j + 1);
                *(array + j + 1) = temp;
            }
        }
    }
}

/* print nb_elem integers using pointer arithmetic */
void print_array(int *array, int nb_elem)
{
    int i;
    for (i = 0; i < nb_elem; i++) {
        printf("%d\n", *(array + i));
    }
}

int main(void)
{
    int tab[100];
    int nb;

    if (read_array(tab, 100, &nb) != 0) {
        fprintf(stderr, "Error reading numbers\n");
        return 1;
    }

    sort_array(tab, nb);
    print_array(tab, nb);

    return 0;
}
