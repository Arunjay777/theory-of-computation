/*
 * EXPERIMENT 10
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to find epsilon-closure for all the states 
 *   in a Non-Deterministic Finite Automata (NFA) with epsilon-moves.
 * 
 * THEORY:
 *   The epsilon-closure of a state q, denoted as eps-closure(q), is defined as 
 *   the set of states that can be reached from q by following zero or more 
 *   epsilon-transitions (empty transitions):
 *     1. q belongs to eps-closure(q) (reflexive property)
 *     2. If p belongs to eps-closure(q) and delta(p, eps) contains r, 
 *        then r belongs to eps-closure(q).
 * 
 * ALGORITHM:
 *   Uses Depth-First Search (DFS) / Transitive Closure traversal on the directed 
 *   graph formed exclusively by epsilon-transitions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 50

int num_states;
int num_transitions;
bool eps_matrix[MAX_STATES][MAX_STATES];
bool visited[MAX_STATES];
bool eps_closure[MAX_STATES][MAX_STATES];

/* DFS to find all states reachable via epsilon transitions */
void dfs_epsilon(int current_state, int start_state) {
    visited[current_state] = true;
    eps_closure[start_state][current_state] = true;

    for (int next = 0; next < num_states; next++) {
        if (eps_matrix[current_state][next] && !visited[next]) {
            dfs_epsilon(next, start_state);
        }
    }
}

void computeEpsilonClosures(void) {
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_states; j++) {
            visited[j] = false;
        }
        dfs_epsilon(i, i);
    }
}

void displayEpsilonClosures(void) {
    printf("\n=========================================\n");
    printf("         EPSILON-CLOSURE TABLE           \n");
    printf("=========================================\n");
    for (int i = 0; i < num_states; i++) {
        printf("eps-closure(q%d) = { ", i);
        bool first = true;
        for (int j = 0; j < num_states; j++) {
            if (eps_closure[i][j]) {
                if (!first) printf(", ");
                printf("q%d", j);
                first = false;
            }
        }
        printf(" }\n");
    }
    printf("=========================================\n");
}

void runBuiltinDemo(void) {
    num_states = 4;
    memset(eps_matrix, false, sizeof(eps_matrix));
    memset(eps_closure, false, sizeof(eps_closure));

    /* Demo epsilon transitions:
     * q0 --eps--> q1
     * q1 --eps--> q2
     * q2 --eps--> q3
     */
    eps_matrix[0][1] = true;
    eps_matrix[1][2] = true;
    eps_matrix[2][3] = true;

    printf("\n--- Running Built-in Demonstration NFA ---\n");
    printf("States: { q0, q1, q2, q3 }\n");
    printf("Epsilon Transitions:\n");
    printf("  q0 --eps--> q1\n");
    printf("  q1 --eps--> q2\n");
    printf("  q2 --eps--> q3\n");

    computeEpsilonClosures();
    displayEpsilonClosures();
}

void runCustomInput(void) {
    memset(eps_matrix, false, sizeof(eps_matrix));
    memset(eps_closure, false, sizeof(eps_closure));

    printf("\nEnter total number of states (e.g., 3 for q0, q1, q2): ");
    if (scanf("%d", &num_states) != 1 || num_states <= 0 || num_states > MAX_STATES) {
        printf("Invalid state count.\n");
        return;
    }

    printf("Enter total number of transitions: ");
    if (scanf("%d", &num_transitions) != 1 || num_transitions < 0) {
        printf("Invalid transition count.\n");
        return;
    }

    printf("\nEnter each transition in format: <from_state_int> <symbol> <to_state_int>\n");
    printf("(Use 'e' or 'E' for epsilon transitions; other symbols are ignored for closure)\n");
    printf("Example: 0 e 1  (means q0 --eps--> q1)\n\n");

    for (int i = 0; i < num_transitions; i++) {
        int u, v;
        char sym[10];
        printf("Transition %d: ", i + 1);
        if (scanf("%d %s %d", &u, sym, &v) != 3) {
            printf("Error reading transition.\n");
            return;
        }

        if (u >= 0 && u < num_states && v >= 0 && v < num_states) {
            if (strcmp(sym, "e") == 0 || strcmp(sym, "E") == 0 || strcmp(sym, "eps") == 0) {
                eps_matrix[u][v] = true;
            }
        } else {
            printf("Warning: Transition indices (%d -> %d) out of range [0, %d). Skipped.\n", u, v, num_states);
        }
    }

    computeEpsilonClosures();
    displayEpsilonClosures();
}

int main(void) {
    int choice;

    printf("=================================================================\n");
    printf(" Experiment 10: Find Epsilon-Closure for All States in an eps-NFA\n");
    printf("=================================================================\n");

    while (1) {
        printf("\nMenu:\n");
        printf("  1. Run Built-in Demonstration NFA\n");
        printf("  2. Enter Custom NFA with Epsilon Moves\n");
        printf("  3. Exit\n");
        printf("Enter your choice (1-3): ");

        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            runBuiltinDemo();
        } else if (choice == 2) {
            runCustomInput();
        } else if (choice == 3) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}
