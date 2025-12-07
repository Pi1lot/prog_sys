#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_int(FILE *f, unsigned int n)
{
    unsigned char b[4];
    b[0] = (n >> 24) & 0xFF;
    b[1] = (n >> 16) & 0xFF;
    b[2] = (n >> 8)  & 0xFF;
    b[3] = n & 0xFF;
    fwrite(b, 1, 4, f);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage : %s archive f1 f2 ... fn\n", argv[0]);
        return 1;
    }

    FILE *out = fopen(argv[1], "wb");
    if (!out) { perror("archive"); return 1; }

    for (int i = 2; i < argc; i++) {
        char *fname = argv[i];
        FILE *in = fopen(fname, "rb");
        if (!in) {
            perror(fname);
            continue;
        }

        // Find size
        fseek(in, 0, SEEK_END);
        unsigned int size = ftell(in);
        fseek(in, 0, SEEK_SET);

        // write name
        fwrite(fname, 1, strlen(fname) + 1, out);

        // write size
        write_int(out, size);

        // copy content
        char buffer[1024];
        unsigned int r;
        while ((r = fread(buffer, 1, sizeof(buffer), in)) > 0)
            fwrite(buffer, 1, r, out);

        fclose(in);
    }

    fclose(out);
    return 0;
}
