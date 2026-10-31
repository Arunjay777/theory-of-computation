#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    int i = 0, j = strlen(s) - 1;
    while (i <= j) {
        if ((s[i] != '0' && s[i] != '1') || s[i] != s[j]) {
            printf("Rejected\n");
            return 0;
        }
        i++;
        j--;
    }

    printf("Accepted\n");
    return 0;
}
