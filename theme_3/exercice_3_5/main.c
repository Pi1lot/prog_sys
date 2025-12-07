#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[256];
    char str2[256];

    // Reading both strings
    printf("First chain : ");
    fgets(str1, sizeof(str1), stdin);
    if (str1[strlen(str1)-1] == '\n') str1[strlen(str1)-1] = '\0';

    printf("Second chain : ");
    fgets(str2, sizeof(str2), stdin);
    if (str2[strlen(str2)-1] == '\n') str2[strlen(str2)-1] = '\0';

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    int found = 0;

    if (len2 > len1) {
        found = 0;
    } else {
        for (size_t i = 0; i <= len1 - len2; i++) {
            if (strncmp(&str1[i], str2, len2) == 0) {
                found = 1;
                break;
            }
        }
    }

    if (found)
        printf("Second string found inside the first\n");
    else
        printf("Second string not found in first\n");

    return 0;
}
