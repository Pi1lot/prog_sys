#include <stdio.h>
#include <stdlib.h>

unsigned int read_int(FILE *f)
{
    unsigned char b[4];
    fread(b, 1, 4, f);
    return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage : %s archive\n", argv[0]);
        return 1;
    }

    FILE *arc = fopen(argv[1], "rb");
    if (!arc) { perror("archive"); return 1; }

    while (1) {
        // read name, end with \0
        char name[256];
        int c, i = 0;

        while ((c = fgetc(arc)) != EOF && c != 0) {
            if (i < 255) name[i++] = c;
        }

        if (c == EOF) break;  // Archiving complete

        name[i] = '\0';

        // read size
        unsigned int size = read_int(arc);

        // create file
        FILE *out = fopen(name, "wb");
        if (!out) { perror(name); fseek(arc, size, SEEK_CUR); continue; }

        // copy file content
        char buffer[1024];
        unsigned int remaining = size;
        while (remaining > 0) {
            unsigned int chunk = remaining < 1024 ? remaining : 1024;
            fread(buffer, 1, chunk, arc);
            fwrite(buffer, 1, chunk, out);
            remaining -= chunk;
        }

        fclose(out);
    }

    fclose(arc);
    return 0;
}
