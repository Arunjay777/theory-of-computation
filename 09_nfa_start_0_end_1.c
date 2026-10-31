#include <stdio.h>

int main() {
    char s[100];
    printf("Enter string: ");
    scanf("%s", s);

    int q[3] = {1, 0, 0};
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        int next[3] = {0, 0, 0};

        if (q[0] && c == '0') next[1] = 1;
        if (q[1]) {
            if (c == '0') next[1] = 1;
            if (c == '1') { next[1] = 1; next[2] = 1; }
        }

        for (int j = 0; j < 3; j++) q[j] = next[j];
    }

    if (q[2]) printf("Accepted\n");
    else printf("Rejected\n");
    return 0;
}
