#include <stdio.h>

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    int state = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (state == 0) state = (c == '0') ? 1 : 3;
        else if (state == 1) state = (c == '0') ? 1 : (c == '1') ? 2 : 3;
        else if (state == 2) state = (c == '0') ? 1 : (c == '1') ? 2 : 3;
        else state = 3;
    }

    if (state == 2) printf("Accepted\n");
    else printf("Rejected\n");
    return 0;
}
