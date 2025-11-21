#include <stdio.h>
#include <ctype.h>

int main(void) {
    int c;
    int freq[26];
    int i;

    for (i = 0; i < 26; i++) {
        freq[i] = 0;
    }

    printf("Entrez du texte (Ctrl+D pour terminer) :\n");

    while ((c = getchar()) != '\n') {

        c = tolower(c);

        if (c >= 'a' && c <= 'z') {
            freq[c - 'a']++;
        }
    }

    printf("\nOccurrences :\n");
    for (i = 0; i < 26; i++) {
        printf("%c : %d\n", 'a' + i, freq[i]);
    }

    return 0;
}
