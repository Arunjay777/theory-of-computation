#include <stdio.h>
#include <string.h>

int main() {
    char tape[100];
    printf("Enter string: ");
    scanf("%s", tape);

    int l = 0, r = strlen(tape) - 1, ok = 1;
    while (l < r) {
        if (tape[l] != tape[r]) {
            ok = 0;
            break;
        }
        tape[l] = 'X';
        tape[r] = 'X';
        l++;
        r--;
    }

    if (ok) printf("Accepted\n");
    else printf("Rejected\n");
    return 0;
}
