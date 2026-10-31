#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '0' && s[i] != '1') {
            printf("Rejected\n");
            return 0;
        }
    }

    if (strstr(s, "101") != NULL) printf("Accepted\n");
    else printf("Rejected\n");
    return 0;
}
