/*
 * EXPERIMENT 12
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Design a DFA simulator to accept the input strings "a", "ac", and "bac".
 * 
 * LANGUAGE SPECIFICATION:
 *   Alphabet: Sigma = {a, b, c}
 *   Finite Language: L = { "a", "ac", "bac" }
 * 
 * DFA 5-TUPLE M = (Q, Sigma, delta, q0, F):
 *   States: Q = { q0, q1, q2, q3, q4, q5, q_trap }
 *   Start state: q0
 *   Accepting states: F = { q1, q3, q5 }
 * 
 *   Path traces:
 *     q0 --'a'--> q1 [ACCEPT "a"] --'c'--> q3 [ACCEPT "ac"]
 *     q0 --'b'--> q2 --'a'--> q4 --'c'--> q5 [ACCEPT "bac"]
 *     All other transitions lead to q_trap (Dead state).
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    Q0 = 0,    /* Start state */
    Q1 = 1,    /* Reached by "a" (ACCEPTING) */
    Q2 = 2,    /* Reached by "b" */
    Q3 = 3,    /* Reached by "ac" (ACCEPTING) */
    Q4 = 4,    /* Reached by "ba" */
    Q5 = 5,    /* Reached by "bac" (ACCEPTING) */
    Q_TRAP = 6 /* Dead / Trap state */
} State;

const char* getStateName(State s) {
    switch (s) {
        case Q0: return "q0 (Start)";
        case Q1: return "q1 (Accept 'a')";
        case Q2: return "q2 (Prefix 'b')";
        case Q3: return "q3 (Accept 'ac')";
        case Q4: return "q4 (Prefix 'ba')";
        case Q5: return "q5 (Accept 'bac')";
        case Q_TRAP: return "q_trap (Dead)";
        default: return "Unknown";
    }
}

bool isAccepting(State s) {
    return (s == Q1 || s == Q3 || s == Q5);
}

State transition(State current, char symbol) {
    switch (current) {
        case Q0:
            if (symbol == 'a') return Q1;
            if (symbol == 'b') return Q2;
            return Q_TRAP;

        case Q1:
            if (symbol == 'c') return Q3;
            return Q_TRAP;

        case Q2:
            if (symbol == 'a') return Q4;
            return Q_TRAP;

        case Q3:
            return Q_TRAP;

        case Q4:
            if (symbol == 'c') return Q5;
            return Q_TRAP;

        case Q5:
            return Q_TRAP;

        case Q_TRAP:
            return Q_TRAP;
    }
    return Q_TRAP;
}

bool simulateDFA(const char *input, bool verbose) {
    State current = Q0;
    int len = strlen(input);

    if (verbose) {
        printf("\n--- DFA Simulation for \"%s\" ---\n", input);
        printf("Initial State: %s\n", getStateName(current));
    }

    if (len == 0) {
        if (verbose) printf("Empty string rejected (length = 0).\n");
        return false;
    }

    for (int i = 0; i < len; i++) {
        char ch = input[i];
        if (ch != 'a' && ch != 'b' && ch != 'c') {
            if (verbose) printf("Error: Invalid symbol '%c' at position %d. Alphabet is {a, b, c}.\n", ch, i + 1);
            return false;
        }
        State next = transition(current, ch);
        if (verbose) {
            printf("Step %d: delta(%s, '%c') -> %s\n", i + 1, getStateName(current), ch, getStateName(next));
        }
        current = next;
    }

    bool accepted = isAccepting(current);
    if (verbose) {
        printf("Final State: %s | Result: %s\n", getStateName(current), accepted ? "ACCEPTED" : "REJECTED");
    }
    return accepted;
}

void runTestSuite(void) {
    printf("\n--- Running Mandatory Test Suite ---\n");
    const char *test_cases[] = {"a", "ac", "bac", "b", "c", "ab", "ba", "bca", "ca", "baca", "aa"};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        bool res = simulateDFA(test_cases[i], false);
        printf("  Test string \"%s\": %s\n", test_cases[i], res ? "ACCEPTED [PASS]" : "REJECTED");
    }
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 12: DFA Simulator for Language L = {\"a\", \"ac\", \"bac\"}\n");
    printf(" Alphabet: {a, b, c}\n");
    printf("=================================================================\n");

    /* Run standard test cases first */
    runTestSuite();

    while (1) {
        printf("\nEnter string over {a, b, c} (or type 'exit' to quit): ");
        if (!fgets(input, sizeof(input), stdin)) break;

        /* Remove trailing newline */
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting program.\n");
            break;
        }

        bool accepted = simulateDFA(input, true);
        if (accepted) {
            printf(">>> Result: ACCEPTED - \"%s\" is in {\"a\", \"ac\", \"bac\"}.\n", input);
        } else {
            printf(">>> Result: REJECTED - \"%s\" is NOT accepted.\n", input);
        }
    }

    return 0;
}
