/*
 * EXPERIMENT 09
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to simulate a Non-Deterministic Finite Automata (NFA) 
 *   for the given language representing strings that start with '0' and end with '1'.
 * 
 * NFA FORMULATION:
 *   Alphabet: Sigma = {0, 1}
 *   States:   Q = {q0, q1, q2}
 *   Start:    q0
 *   Accept:   F = {q2}
 * 
 *   Transition Table delta:
 *     State |  '0'      |  '1'
 *     ------+-----------+---------
 *      q0   |  {q1}     |  {}
 *      q1   |  {q1}     |  {q1, q2}
 *      q2   |  {}       |  {}
 * 
 *   Non-determinism:
 *     In state q1, on input '1', the machine can either:
 *       1. Stay in q1 (if more binary symbols follow)
 *       2. Move to q2 (guessing it is the final '1')
 * 
 * SIMULATION METHOD:
 *   Active State Set tracking (subset construction on the fly).
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NUM_STATES 3

/* State indices: 0 = q0, 1 = q1, 2 = q2 */
const char* state_names[NUM_STATES] = {"q0", "q1", "q2"};

void printStateSet(const bool states[NUM_STATES]) {
    printf("{ ");
    bool first = true;
    for (int i = 0; i < NUM_STATES; i++) {
        if (states[i]) {
            if (!first) printf(", ");
            printf("%s", state_names[i]);
            first = false;
        }
    }
    if (first) printf("Empty Set (phi)");
    printf(" }");
}

bool hasActiveStates(const bool states[NUM_STATES]) {
    for (int i = 0; i < NUM_STATES; i++) {
        if (states[i]) return true;
    }
    return false;
}

bool simulateNFA(const char *input) {
    bool current_states[NUM_STATES] = {false};
    current_states[0] = true; /* Start in {q0} */

    int len = strlen(input);

    printf("\n--- NFA Simulation Trace ---\n");
    printf("Initial Active States: ");
    printStateSet(current_states);
    printf("\n");

    if (len == 0) {
        printf("Empty string rejected.\n");
        return false;
    }

    for (int i = 0; i < len; i++) {
        char ch = input[i];
        if (ch != '0' && ch != '1') {
            printf("Error: Invalid symbol '%c' at position %d. Alphabet is {0, 1}.\n", ch, i + 1);
            return false;
        }

        bool next_states[NUM_STATES] = {false};

        /* Compute delta for all currently active states */
        for (int s = 0; s < NUM_STATES; s++) {
            if (!current_states[s]) continue;

            if (s == 0) { /* q0 */
                if (ch == '0') next_states[1] = true; /* q0 on '0' -> {q1} */
            } else if (s == 1) { /* q1 */
                if (ch == '0') {
                    next_states[1] = true; /* q1 on '0' -> {q1} */
                } else if (ch == '1') {
                    next_states[1] = true; /* q1 on '1' -> {q1, q2} */
                    next_states[2] = true;
                }
            } else if (s == 2) { /* q2 */
                /* q2 has no outgoing transitions */
            }
        }

        printf("Step %d: Read '%c' | Next Active States: ", i + 1, ch);
        printStateSet(next_states);
        printf("\n");

        for (int s = 0; s < NUM_STATES; s++) {
            current_states[s] = next_states[s];
        }

        if (!hasActiveStates(current_states)) {
            printf("Deadlock reached: No valid transitions remaining.\n");
            return false;
        }
    }

    /* Check if accepting state q2 is among current states */
    bool accepted = current_states[2];
    printf("\nFinal Active States: ");
    printStateSet(current_states);
    printf(" | Accepting State {q2} %s\n", accepted ? "FOUND" : "NOT FOUND");

    return accepted;
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 09: NFA Simulation (Strings starting with '0' and ending with '1')\n");
    printf(" Alphabet: {0, 1}\n");
    printf("=================================================================\n");

    while (1) {
        printf("\nEnter input string (or type 'exit' to quit): ");
        if (!fgets(input, sizeof(input), stdin)) break;

        /* Remove trailing newline */
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting program.\n");
            break;
        }

        bool accepted = simulateNFA(input);
        if (accepted) {
            printf(">>> Result: ACCEPTED - \"%s\" belongs to the language.\n", input);
        } else {
            printf(">>> Result: REJECTED - \"%s\" does NOT belong to the language.\n", input);
        }
    }

    return 0;
}
