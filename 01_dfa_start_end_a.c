/*
 * EXPERIMENT 01
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to simulate a Deterministic Finite Automata (DFA) 
 *   for the given language representing strings that start with 'a' and end with 'a'.
 * 
 * LANGUAGE SPECIFICATION:
 *   Alphabet: Sigma = {a, b}
 *   Language: L = { w | w starts with 'a' and ends with 'a' }
 *   Valid strings:   "a", "aa", "aba", "abba", "aaaa", "abaa", ...
 *   Invalid strings: "b", "ab", "ba", "bb", "bab", "", ...
 * 
 * DFA 5-TUPLE M = (Q, Sigma, delta, q0, F):
 *   States: Q = {q0, q1, q2, q_trap}
 *   Start state: q0
 *   Accept state: F = {q1}
 *   Transition Function delta:
 *     delta(q0, 'a') = q1,      delta(q0, 'b') = q_trap
 *     delta(q1, 'a') = q1,      delta(q1, 'b') = q2
 *     delta(q2, 'a') = q1,      delta(q2, 'b') = q2
 *     delta(q_trap, 'a') = q_trap, delta(q_trap, 'b') = q_trap
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    Q0 = 0,    /* Initial state */
    Q1 = 1,    /* Started with 'a' and last symbol was 'a' (ACCEPTING) */
    Q2 = 2,    /* Started with 'a' and last symbol was 'b' */
    Q_TRAP = 3 /* Trap state: started with 'b' */
} State;

const char* getStateName(State s) {
    switch (s) {
        case Q0: return "q0 (Start)";
        case Q1: return "q1 (Accepting)";
        case Q2: return "q2 (Non-accepting)";
        case Q_TRAP: return "q_trap (Dead)";
        default: return "Unknown";
    }
}

State transition(State current, char symbol) {
    switch (current) {
        case Q0:
            if (symbol == 'a') return Q1;
            if (symbol == 'b') return Q_TRAP;
            break;
        case Q1:
            if (symbol == 'a') return Q1;
            if (symbol == 'b') return Q2;
            break;
        case Q2:
            if (symbol == 'a') return Q1;
            if (symbol == 'b') return Q2;
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
        if (ch != 'a' && ch != 'b') {
            printf("Error: Invalid symbol '%c' at position %d. Alphabet is {a, b}.\n", ch, i + 1);
            return false;
        }
        State next = transition(current, ch);
        printf("Step %d: delta(%s, '%c') -> %s\n", i + 1, getStateName(current), ch, getStateName(next));
        current = next;
    }

    printf("Final State: %s\n", getStateName(current));
    return (current == Q1);
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 01: DFA for strings that start with 'a' and end with 'a'\n");
    printf(" Alphabet: {a, b}\n");
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
