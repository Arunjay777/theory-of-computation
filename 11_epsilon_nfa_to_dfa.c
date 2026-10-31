/*
 * EXPERIMENT 11
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to find epsilon-closure for all the states in an NFA with 
 *   epsilon-moves and convert the epsilon-NFA to an equivalent DFA 
 *   using Subset Construction.
 * 
 * THEORY & ALGORITHM:
 *   1. Compute eps-closure for each individual state:
 *      eps-closure(q) = set of states reachable from q by eps-transitions.
 *   2. Start DFA state D0 = eps-closure(q0).
 *   3. For each unmarked DFA state D:
 *        For each input symbol 'a' in Alphabet:
 *          Move(D, a) = Union of delta(s, a) for all s in D.
 *          D_next = eps-closure(Move(D, a)) = Union of eps-closure(p) for all p in Move(D, a).
 *          If D_next is a new state, add it to DFA states.
 *          Set DFA_transition(D, a) = D_next.
 *   4. Any DFA state containing at least one NFA final state is marked as DFA final state.
 *   5. Simulate string acceptance on the resulting DFA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NFA_STATES 20
#define MAX_DFA_STATES 50
#define MAX_ALPHABET 2

int num_nfa_states;
int num_symbols = 2;
char alphabet[MAX_ALPHABET] = {'a', 'b'};
int nfa_final_state = 2;

/* Transition tables for NFA: delta_nfa[state][symbol_index][target_state] */
/* symbol_index: 0 = 'a', 1 = 'b', 2 = 'eps' */
bool delta_nfa[MAX_NFA_STATES][3][MAX_NFA_STATES];
bool eps_closure[MAX_NFA_STATES][MAX_NFA_STATES];

/* DFA representations */
int num_dfa_states = 0;
bool dfa_states[MAX_DFA_STATES][MAX_NFA_STATES]; /* set of NFA states in each DFA state */
int dfa_trans[MAX_DFA_STATES][MAX_ALPHABET];
bool dfa_is_final[MAX_DFA_STATES];

/* Compute eps-closure for each NFA state */
void dfs_eps(int curr, int start, bool visited[]) {
    visited[curr] = true;
    eps_closure[start][curr] = true;

    for (int next = 0; next < num_nfa_states; next++) {
        if (delta_nfa[curr][2][next] && !visited[next]) {
            dfs_eps(next, start, visited);
        }
    }
}

void computeAllEpsClosures(void) {
    for (int i = 0; i < num_nfa_states; i++) {
        bool visited[MAX_NFA_STATES] = {false};
        dfs_eps(i, i, visited);
    }
}

/* Set operations for DFA states */
bool setsEqual(const bool s1[MAX_NFA_STATES], const bool s2[MAX_NFA_STATES]) {
    for (int i = 0; i < num_nfa_states; i++) {
        if (s1[i] != s2[i]) return false;
    }
    return true;
}

int findDFAState(const bool state_set[MAX_NFA_STATES]) {
    for (int i = 0; i < num_dfa_states; i++) {
        if (setsEqual(dfa_states[i], state_set)) return i;
    }
    return -1;
}

void printStateSet(const bool state_set[MAX_NFA_STATES]) {
    printf("{ ");
    bool first = true;
    for (int i = 0; i < num_nfa_states; i++) {
        if (state_set[i]) {
            if (!first) printf(", ");
            printf("q%d", i);
            first = false;
        }
    }
    if (first) printf("phi");
    printf(" }");
}

/* Build DFA from epsilon-NFA */
void convertEpsNfaToDfa(void) {
    num_dfa_states = 0;

    /* DFA Start State: D0 = eps-closure(q0) */
    for (int i = 0; i < num_nfa_states; i++) {
        dfa_states[0][i] = eps_closure[0][i];
    }
    num_dfa_states = 1;

    int current = 0;
    while (current < num_dfa_states) {
        for (int sym_idx = 0; sym_idx < num_symbols; sym_idx++) {
            bool move_set[MAX_NFA_STATES] = {false};

            /* Move(D_current, symbol) */
            for (int s = 0; s < num_nfa_states; s++) {
                if (dfa_states[current][s]) {
                    for (int target = 0; target < num_nfa_states; target++) {
                        if (delta_nfa[s][sym_idx][target]) {
                            move_set[target] = true;
                        }
                    }
                }
            }

            /* Next DFA state = eps-closure(Move(D_current, symbol)) */
            bool next_state_set[MAX_NFA_STATES] = {false};
            for (int s = 0; s < num_nfa_states; s++) {
                if (move_set[s]) {
                    for (int closure_state = 0; closure_state < num_nfa_states; closure_state++) {
                        if (eps_closure[s][closure_state]) {
                            next_state_set[closure_state] = true;
                        }
                    }
                }
            }

            int existing_idx = findDFAState(next_state_set);
            if (existing_idx == -1) {
                /* New DFA state discovered */
                for (int s = 0; s < num_nfa_states; s++) {
                    dfa_states[num_dfa_states][s] = next_state_set[s];
                }
                dfa_trans[current][sym_idx] = num_dfa_states;
                num_dfa_states++;
            } else {
                dfa_trans[current][sym_idx] = existing_idx;
            }
        }
        current++;
    }

    /* Identify accepting DFA states */
    for (int i = 0; i < num_dfa_states; i++) {
        dfa_is_final[i] = false;
        if (dfa_states[i][nfa_final_state]) {
            dfa_is_final[i] = true;
        }
    }
}

void printDfaTable(void) {
    printf("\n=======================================================\n");
    printf("        CONVERTED EQUIVALENT DFA TRANSITION TABLE      \n");
    printf("=======================================================\n");
    printf("%-10s %-25s %-12s %-12s %-10s\n", "DFA State", "NFA States Subset", "on 'a'", "on 'b'", "Status");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < num_dfa_states; i++) {
        char name[20];
        snprintf(name, sizeof(name), "%sD%d", (i == 0 ? "-> " : "   "), i);

        char subset[64] = "{ ";
        bool first = true;
        for (int s = 0; s < num_nfa_states; s++) {
            if (dfa_states[i][s]) {
                if (!first) strcat(subset, ", ");
                char temp[10];
                snprintf(temp, sizeof(temp), "q%d", s);
                strcat(subset, temp);
                first = false;
            }
        }
        if (first) strcat(subset, "phi");
        strcat(subset, " }");

        char to_a[20], to_b[20];
        snprintf(to_a, sizeof(to_a), "D%d", dfa_trans[i][0]);
        snprintf(to_b, sizeof(to_b), "D%d", dfa_trans[i][1]);

        printf("%-10s %-25s %-12s %-12s %-10s\n",
               name, subset, to_a, to_b, (dfa_is_final[i] ? "[ACCEPT]" : ""));
    }
    printf("=======================================================\n");
}

bool simulateConvertedDfa(const char *input) {
    int current = 0; /* D0 */
    int len = strlen(input);

    printf("\n--- DFA Simulation Trace ---\n");
    printf("Start at D0\n");

    for (int i = 0; i < len; i++) {
        int sym_idx = -1;
        if (input[i] == 'a') sym_idx = 0;
        else if (input[i] == 'b') sym_idx = 1;
        else {
            printf("Invalid symbol '%c'. Alphabet is {a, b}.\n", input[i]);
            return false;
        }

        int next = dfa_trans[current][sym_idx];
        printf("Read '%c': D%d -> D%d\n", input[i], current, next);
        current = next;
    }

    printf("Halted in DFA state D%d (%s)\n", current, dfa_is_final[current] ? "ACCEPT" : "REJECT");
    return dfa_is_final[current];
}

void setupStandardExample(void) {
    num_nfa_states = 3;
    nfa_final_state = 2;
    memset(delta_nfa, false, sizeof(delta_nfa));

    /* Standard eps-NFA accepting (a|b)*abb:
     * q0 --eps--> q1
     * q0 --a--> q0, q0 --b--> q0
     * q1 --a--> q2
     */
    delta_nfa[0][2][1] = true; /* q0 --eps--> q1 */
    delta_nfa[0][0][0] = true; /* q0 --a--> q0 */
    delta_nfa[0][1][0] = true; /* q0 --b--> q0 */
    delta_nfa[1][0][2] = true; /* q1 --a--> q2 (final) */
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 11: Epsilon-Closure & Epsilon-NFA to DFA Conversion\n");
    printf("=================================================================\n");

    setupStandardExample();
    computeAllEpsClosures();

    printf("\nStep 1: Computed Epsilon-Closures for all states:\n");
    for (int i = 0; i < num_nfa_states; i++) {
        printf("  eps-closure(q%d) = ", i);
        printStateSet(eps_closure[i]);
        printf("\n");
    }

    printf("\nStep 2: Performing Subset Construction to generate equivalent DFA...\n");
    convertEpsNfaToDfa();
    printDfaTable();

    while (1) {
        printf("\nEnter input string over {a, b} to test on converted DFA (or 'exit' to quit): ");
        if (!fgets(input, sizeof(input), stdin)) break;

        /* Remove trailing newline */
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting program.\n");
            break;
        }

        bool accepted = simulateConvertedDfa(input);
        if (accepted) {
            printf(">>> Result: ACCEPTED by converted DFA!\n");
        } else {
            printf(">>> Result: REJECTED by converted DFA!\n");
        }
    }

    return 0;
}
