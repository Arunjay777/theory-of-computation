#include <stdio.h>

int main() {
    char tape[100];
    printf("Enter string: ");
    scanf("%s", tape);

    int head = 0, state = 0;
    while (1) {
        if (state == 0) {
            if (tape[head] == 'a') { tape[head] = 'X'; head++; state = 1; }
            else if (tape[head] == 'Y') { head++; state = 4; }
            else break;
        } else if (state == 1) {
            if (tape[head] == 'a' || tape[head] == 'Y') head++;
            else if (tape[head] == 'b') { tape[head] = 'Y'; head++; state = 2; }
            else break;
        } else if (state == 2) {
            if (tape[head] == 'Y') head++;
            else if (tape[head] == 'b') { tape[head] = 'Y'; head--; state = 3; }
            else break;
        } else if (state == 3) {
            if (tape[head] == 'a' || tape[head] == 'Y') head--;
            else if (tape[head] == 'X') { head++; state = 0; }
            else break;
        } else if (state == 4) {
            if (tape[head] == 'Y') head++;
            else if (tape[head] == '\0') { state = 5; break; }
            else break;
        }
    }

    if (state == 5) printf("Accepted\n");
    else printf("Rejected\n");
    return 0;
}
