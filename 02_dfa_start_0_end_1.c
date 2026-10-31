/*
 * EXPERIMENT 02
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to simulate a Deterministic Finite Automata (DFA) 
 *   for the given language representing strings that start with '0' and end with '1'.
 * 
 * LANGUAGE SPECIFICATION:
 *   Alphabet: Sigma = {0, 1}
 *   Language: L = { w | w starts with '0' and ends with '1' }
 *   Valid strings:   "01", "001", "011", "0101", "0001", "01111", ...
 *   Invalid strings: "0", "1", "00", "10", "11", "010", "101", "", ...
 * 
 * DFA 5-TUPLE M = (Q, Sigma, delta, q0, F):
 *   States: Q = {q0, q1, q2, q_trap}
 *   Start state: q0
 *   Accept state: F = {q2}
 *   Transition Function delta:
 *     delta(q0, '0') = q1,      delta(q0, '1') = q_trap
 *     delta(q1, '0') = q1,      delta(q1, '1') = q2
 *     delta(q2, '0') = q1,      delta(q2, '1') = q2
 *     delta(q_trap, '0') = q_trap, delta(q_trap, '1') = q_trap
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    Q0 = 0,    /* Initial state */
    Q1 = 1,    /* Started with '0' and ends with '0' */
    Q2 = 2,    /* Started with '0' and ends with '1' (ACCEPTING) */
    Q_TRAP = 3 /* Trap state: started with '1' */
} State;

const char* getStateName(State s) {
    switch (s) {
        case Q0: return "q0 (Start)";
        case Q1: return "q1 (Ends with 0)";
        case Q2: return "q2 (Ends with 1, Accepting)";
        case Q_TRAP: return "q_trap (Dead)";
        default: return "Unknown";
    }
}

State transition(State current, char symbol) {
    switch (current) {
        case Q0:
            if (symbol == '0') return Q1;
            if (symbol == '1') return Q_TRAP;
            break;
        case Q1:
            if (symbol == '0') return Q1;
            if (symbol == '1') return Q2;
            break;
        case Q2:
            if (symbol == '0') return Q1;
            if (symbol == '1') return Q2;
            break;
        case Q_TRAP:
            return Q_TRAP;
    }
    return Q_TRAP;
}

bool simulateDFA(const char *input) {
    State current = Q0;
    int len = strlen(input);

    printf("\n--- DFA Simulation Trace ---\n");
    printf("Initial State: %s\n", getStateName(current));

    if (len == 0) {
        printf("Empty string rejected (length = 0).\n");
        return false;
    }

    for (int i = 0; i < len; i++) {
        char ch = input[i];
        if (ch != '0' && ch != '1') {
            printf("Error: Invalid symbol '%c' at position %d. Alphabet is {0, 1}.\n", ch, i + 1);
            return false;
        }
        State next = transition(current, ch);
        printf("Step %d: delta(%s, '%c') -> %s\n", i + 1, getStateName(current), ch, getStateName(next));
        current = next;
    }

    printf("Final State: %s\n", getStateName(current));
    return (current == Q2);
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 02: DFA for strings that start with '0' and end with '1'\n");
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

        bool accepted = simulateDFA(input);
        if (accepted) {
            printf(">>> Result: ACCEPTED - String \"%s\" belongs to the language.\n", input);
        } else {
            printf(">>> Result: REJECTED - String \"%s\" does NOT belong to the language.\n", input);
        }
    }

    return 0;
}
