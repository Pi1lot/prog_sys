#include <stdio.h>
#include <stdlib.h>

/* define a structure containing:
   - a char pointer
   - an array of 10 integers
   - a pointer to the same structure type */
typedef struct my_struct {
    char *cptr;
    int ints[10];
    struct my_struct *self_ptr;
} MyStruct;

int main(void)
{
    /* declare an array of 50 pointers to MyStruct */
    MyStruct *array[50];

    /* initialize all pointers to NULL */
    for (int i = 0; i < 50; i++) {
        array[i] = NULL;
    }

    /* example of allocating the first element */
    array[0] = malloc(sizeof(MyStruct));
    if (array[0] != NULL) {
        array[0]->cptr = "Hello";
        for (int j = 0; j < 10; j++) {
            array[0]->ints[j] = j;
        }
        array[0]->self_ptr = array[0];
    }

    /* print example */
    if (array[0] != NULL) {
        printf("cptr: %s\n", array[0]->cptr);
        printf("ints: ");
        for (int j = 0; j < 10; j++) {
            printf("%d ", array[0]->ints[j]);
        }
        printf("\n");
        printf("self_ptr points to same address as array[0]: %s\n",
               array[0]->self_ptr == array[0] ? "yes" : "no");
    }

    // free allocated memory
    free(array[0]);

    return 0;
}
