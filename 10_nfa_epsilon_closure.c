#include <stdio.h>

int n, t, adj[20][20], closure[20][20], visited[20];

void dfs(int cur, int start) {
    visited[cur] = 1;
    closure[start][cur] = 1;
    for (int i = 0; i < n; i++) {
        if (adj[cur][i] && !visited[i]) dfs(i, start);
    }
}

int main() {
    printf("Enter number of states and transitions: ");
    if (scanf("%d %d", &n, &t) != 2) return 0;

    printf("Enter transitions (u v for eps-move u->v):\n");
    for (int i = 0; i < t; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u < n && v < n) adj[u][v] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) visited[j] = 0;
        dfs(i, i);
    }

    printf("\nEpsilon Closures:\n");
    for (int i = 0; i < n; i++) {
        printf("e-closure(q%d) = { ", i);
        for (int j = 0; j < n; j++) {
            if (closure[i][j]) printf("q%d ", j);
        }
        printf("}\n");
    }
    return 0;
}
