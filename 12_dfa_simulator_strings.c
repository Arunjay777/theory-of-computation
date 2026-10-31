#include <stdio.h>

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    int state = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (state == 0) state = (c == 'a') ? 1 : (c == 'b') ? 2 : 6;
        else if (state == 1) state = (c == 'c') ? 3 : 6;
        else if (state == 2) state = (c == 'a') ? 4 : 6;
        else if (state == 4) state = (c == 'c') ? 5 : 6;
        else state = 6;
    }

    if (state == 1 || state == 3 || state == 5) printf("Accepted\n");
    else printf("Rejected\n");
    return 0;
}
