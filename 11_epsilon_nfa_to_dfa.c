#include <stdio.h>

int n = 3;
int adj[10][10] = {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}};
int dfa[10][2] = {{0, 1}, {0, 2}, {0, 1}};

int main() {
    printf("Epsilon Closures:\n");
    for (int i = 0; i < n; i++) {
        printf("e-closure(q%d) = { q%d", i, i);
        for (int j = 0; j < n; j++) {
            if (adj[i][j]) printf(", q%d", j);
        }
        printf(" }\n");
    }

    printf("\nEquivalent DFA Transition Table:\n");
    printf("State\t0\t1\n");
    for (int i = 0; i < 3; i++) {
        printf("q%d%s\tq%d\tq%d\n", i, (i == 2 ? "*" : ""), dfa[i][0], dfa[i][1]);
    }
    return 0;
}
