#include <stdio.h>

#define MAX_LINES 10
#define LINE_SIZE 1024   /* taille max d'une ligne */

int main(void) {
    char lines[MAX_LINES][LINE_SIZE];
    int size[MAX_LINES];
    int index = 0;
    int c;
    int pos = 0;


    for (int i = 0; i < MAX_LINES; i++) {
        size[i] = 0;
    }

    while ((c = getchar()) != EOF) {

        if (c == '\n') {
            
            lines[index][pos] = '\n';
            size[index] = pos + 1;  
            index = (index + 1) % MAX_LINES;  /* ligne suivante dans le buffer */
            pos = 0;
        } else {
        
            if (pos < LINE_SIZE - 1) {
                lines[index][pos] = c;
                pos++;
            }
        }
    }

    if (pos > 0) {
        lines[index][pos] = '\n';
        size[index] = pos + 1;
        index = (index + 1) % MAX_LINES;
    }

    for (int i = 0; i < MAX_LINES; i++) {
        int real_index = (index + i) % MAX_LINES;

        for (int j = 0; j < size[real_index]; j++) {
            putchar(lines[real_index][j]);
        }
    }

    return 0;
}
