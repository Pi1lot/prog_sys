#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int n = 10;   // valeur par défaut
    int opt;

    // Lecture option -n
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        if (opt == 'n')
            n = atoi(optarg);
    }

    // Nom du fichier
    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-n nb] fichier\n", argv[0]);
        return 1;
    }

    char *filename = argv[optind];

    // Ouvrir le fichier
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("open");
        return 1;
    }

    // Déterminer la taille du fichier
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    // Load file in memory
    char *buf = malloc(size + 1);
    if (!buf) {
        fprintf(stderr, "Mémoire insuffisante\n");
        fclose(f);
        return 1;
    }

    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);

    // Find last lines
    int count = 0;
    long i = size - 1;

    for (; i >= 0; i--) {
        if (buf[i] == '\n') {
            count++;
            if (count == n + 1) {
                i++;
                break;
            }
        }
    }

    if (i < 0) i = 0;

    // Print
    printf("%s", &buf[i]);

    free(buf);
    return 0;
}
