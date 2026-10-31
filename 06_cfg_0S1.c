#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    int n = strlen(s);
    if (n % 2 != 0) {
        printf("Rejected\n");
        return 0;
    }

    int half = n / 2;
    for (int i = 0; i < half; i++) {
        if (s[i] != '0' || s[i + half] != '1') {
            printf("Rejected\n");
            return 0;
        }
    }

    printf("Accepted\n");
    return 0;
}
