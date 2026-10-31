#include <stdio.h>
#include <string.h>

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    int len = strlen(s);
    int c1 = 0, c2 = 0, c3 = 0;

    while (s[c1] == '0') c1++;
    while (s[c1 + c2] == '1') c2++;
    while (s[c1 + c2 + c3] == '0') c3++;

    if (c1 + c2 + c3 == len && c1 == c3) printf("Accepted\n");
    else printf("Rejected\n");
    return 0;
}
