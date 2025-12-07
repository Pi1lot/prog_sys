#include <stdio.h>

// return pointer to first occurrence of car in chaine, or NULL if not found
char *mon_strchr(char *chaine, int car)
{
    while (*chaine != '\0') {
        if (*chaine == car)
            return chaine;
        chaine++;
    }
    if (car == '\0')  // End of string case
        return chaine;
    return NULL;
}

// test programm
int main(void)
{
    char str[256];
    int c;

    printf("Enter string : ");
    fgets(str, sizeof(str), stdin);
    if (str[0] == '\0') return 0;

    printf("Enter a char to search for : ");
    c = getchar();

    char *res = mon_strchr(str, c);
    if (res)
        printf("Character found at position %ld\n", res - str + 1);
    else
        printf("Character not found\n");

    return 0;
}
