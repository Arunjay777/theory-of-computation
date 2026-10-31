#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    int n = strlen(s);
    if (n < 2 || s[0] != '0' || s[n - 1] != '1') {
        printf("Rejected\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (s[i] != '0' && s[i] != '1') {
            printf("Rejected\n");
            return 0;
        }
    }

    printf("Accepted\n");
    return 0;
}
