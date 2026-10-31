/*
 * EXPERIMENT 17
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Design a Turing Machine (TM) simulator to accept the input string 
 *   Palindrome "ababa" (and general palindromes over {a, b}).
 * 
 * TM 7-TUPLE M = (Q, Sigma, Gamma, delta, q0, B, F):
 *   States: Q = { q0, q1, q2, q3, q4, q5, q_accept }
 *   Input alphabet: Sigma = { a, b }
 *   Tape alphabet: Gamma = { a, b, B }
 *   Start state: q0
 *   Blank symbol: B
 *   Accepting state: F = { q_accept }
 * 
 * ALGORITHM:
 *   1. In q0:
 *      - If 'B', string is empty or completely verified -> ACCEPT (q_accept)
 *      - If 'a', replace with 'B', move R -> q1 (remember 'a')
 *      - If 'b', replace with 'B', move R -> q2 (remember 'b')
 *   2. In q1 / q2: Move right over all 'a' and 'b' until 'B', then move L -> q3 / q4
 *   3. In q3:
 *      - If 'a', matches! Replace with 'B', move L -> q5
 *      - If 'B', odd length palindrome center symbol -> ACCEPT (q_accept)
 *      - If 'b', mismatch! REJECT
 *   4. In q4:
 *      - If 'b', matches! Replace with 'B', move L -> q5
 *      - If 'B', odd length palindrome center symbol -> ACCEPT (q_accept)
 *      - If 'a', mismatch! REJECT
 *   5. In q5: Move left over all 'a' and 'b' until 'B', then move R -> q0
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAPE_SIZE 100
#define BLANK 'B'

typedef enum {
    Q0 = 0,
    Q1 = 1,
    Q2 = 2,
    Q3 = 3,
    Q4 = 4,
    Q5 = 5,
    Q_ACCEPT = 6
} State;

const char* getStateName(State s) {
    switch (s) {
        case Q0: return "q0 (Start / Scan Left)";
        case Q1: return "q1 (Remember 'a', scan Right)";
        case Q2: return "q2 (Remember 'b', scan Right)";
        case Q3: return "q3 (Verify rightmost 'a')";
        case Q4: return "q4 (Verify rightmost 'b')";
        case Q5: return "q5 (Return Left to start)";
        case Q_ACCEPT: return "q_accept (ACCEPT)";
        default: return "Unknown";
    }
}

void printTape(const char tape[], int head_pos, State state) {
    printf("%-28s | Tape: ", getStateName(state));
    for (int i = 0; i < 20; i++) {
        if (tape[i] == '\0') break;
        printf("[%c]", tape[i]);
    }
    printf("\n                             ");
    for (int i = 0; i < head_pos; i++) {
        printf("   ");
    }
    printf(" ^ (head)\n");
}

bool simulatePalindromeTM(const char *input) {
    char tape[TAPE_SIZE];
    int len = strlen(input);

    /* Initialize tape with BLANK */
    for (int i = 0; i < TAPE_SIZE; i++) tape[i] = BLANK;

    /* Copy input characters onto tape starting at index 1, leaving index 0 as BLANK marker */
    tape[0] = BLANK;
    for (int i = 0; i < len; i++) {
        if (input[i] != 'a' && input[i] != 'b') {
            printf("Error: Invalid symbol '%c'. Alphabet is {a, b}.\n", input[i]);
            return false;
        }
        tape[i + 1] = input[i];
    }
    tape[len + 1] = BLANK;

    int head = 1; /* Start at first symbol of string */
    State state = Q0;
    int steps = 0;
    const int MAX_STEPS = 1000;

    printf("\n--- Turing Machine Palindrome Simulation ---\n");
    printf("Input: \"%s\"\n", input);

    while (state != Q_ACCEPT && steps < MAX_STEPS) {
        steps++;
        printTape(tape, head, state);

        char sym = tape[head];

        if (state == Q0) {
            if (sym == BLANK) {
                state = Q_ACCEPT;
            } else if (sym == 'a') {
                tape[head] = BLANK;
                head++;
                state = Q1;
            } else if (sym == 'b') {
                tape[head] = BLANK;
                head++;
                state = Q2;
            } else {
                break;
            }
        } else if (state == Q1) {
            if (sym == 'a' || sym == 'b') {
                head++;
                state = Q1;
            } else if (sym == BLANK) {
                head--;
                state = Q3;
            }
        } else if (state == Q2) {
            if (sym == 'a' || sym == 'b') {
                head++;
                state = Q2;
            } else if (sym == BLANK) {
                head--;
                state = Q4;
            }
        } else if (state == Q3) {
            if (sym == 'a') {
                tape[head] = BLANK;
                head--;
                state = Q5;
            } else if (sym == BLANK) {
                /* Center character of odd palindrome */
                state = Q_ACCEPT;
            } else {
                /* Mismatch: expected 'a', found 'b' */
                break;
            }
        } else if (state == Q4) {
            if (sym == 'b') {
                tape[head] = BLANK;
                head--;
                state = Q5;
            } else if (sym == BLANK) {
                /* Center character of odd palindrome */
                state = Q_ACCEPT;
            } else {
                /* Mismatch: expected 'b', found 'a' */
                break;
            }
        } else if (state == Q5) {
            if (sym == 'a' || sym == 'b') {
                head--;
                state = Q5;
            } else if (sym == BLANK) {
                head++;
                state = Q0;
            }
        }
    }

    if (state == Q_ACCEPT) {
        printTape(tape, head, state);
        printf("\n>>> RESULT: ACCEPTED - Turing Machine verified \"%s\" is a PALINDROME in %d steps!\n", input, steps);
        return true;
    } else {
        printf("\n>>> RESULT: REJECTED - String \"%s\" is NOT a palindrome.\n", input);
        return false;
    }
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 17: Turing Machine Simulator to Accept Palindrome \"ababa\"\n");
    printf(" Language: L = { w in {a, b}* | w = w^R }\n");
    printf("=================================================================\n");

    /* Default check with target string "ababa" */
    printf("\nVerifying mandatory target palindrome string \"ababa\":\n");
    simulatePalindromeTM("ababa");

    while (1) {
        printf("\nEnter string over {a, b} to test on Palindrome TM (or type 'exit' to quit): ");
        if (!fgets(input, sizeof(input), stdin)) break;

        /* Remove trailing newline */
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting program.\n");
            break;
        }

        simulatePalindromeTM(input);
    }

    return 0;
}
