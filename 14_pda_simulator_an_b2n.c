#include <stdio.h>

int main() {
    char s[100], stack[200];
    int top = -1, i = 0;

    printf("Enter string: ");
    scanf("%s", s);

    while (s[i] == 'a') {
        stack[++top] = 'a';
        stack[++top] = 'a';
        i++;
    }

    if (i == 0) {
        printf("Rejected\n");
        return 0;
    }

    while (s[i] == 'b') {
        if (top < 0) {
            printf("Rejected\n");
            return 0;
        }
        top--;
        i++;
    }

    if (s[i] == '\0' && top == -1) printf("Accepted\n");
    else printf("Rejected\n");
    return 0;
}
