#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* fileToRead;
    FILE* fileToCreate;
    int c;
    
    fileToRead = fopen("toto", "r");
    fileToCreate = fopen("titi", "w");

    while ((c = getc(fileToRead)) != EOF) {
        putc(c, fileToCreate);
    }

    fclose(fileToRead);
    fclose(fileToCreate);

    return 0;
}
