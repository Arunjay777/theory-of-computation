/*
 * EXPERIMENT 15
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Design a Turing Machine (TM) simulator to accept strings of the form 
 *   a^n b^n for n >= 1 (e.g., "ab", "aabb", "aaabbb").
 * 
 * TM 7-TUPLE M = (Q, Sigma, Gamma, delta, q0, B, F):
 *   States: Q = { q0, q1, q2, q3, q4 }
 *   Input alphabet: Sigma = { a, b }
 *   Tape alphabet: Gamma = { a, b, X, Y, B }
 *   Start state: q0
 *   Blank symbol: B
 *   Accepting state: F = { q4 }
 * 
 * TRANSITION LOGIC:
 *   - q0: Find leftmost 'a', mark as 'X', move R -> q1
 *         If encounter 'Y', move R -> q3 (check if only 'Y's remain)
 *   - q1: Skip 'a's and 'Y's, find matching 'b', mark as 'Y', move L -> q2
 *   - q2: Move L back over 'a's and 'Y's until 'X', move R -> q0
 *   - q3: Move R over all 'Y's; if blank 'B' reached -> q4 (ACCEPT)
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAPE_SIZE 100
#define BLANK 'B'

void printTape(const char tape[], int head_pos, int state) {
    printf("State: q%d | Tape: ", state);
    for (int i = 0; i < 20; i++) {
        if (tape[i] == '\0') break;
        printf("[%c]", tape[i]);
    }
    printf("\n                ");
    for (int i = 0; i < head_pos; i++) {
        printf("   ");
    }
    printf(" ^ (head)\n");
}

bool simulateTM(const char *input) {
    char tape[TAPE_SIZE];
    int len = strlen(input);

    if (len == 0) {
        printf("Empty string rejected (requires n >= 1).\n");
        return false;
    }

    /* Initialize tape: B followed by input string followed by blanks */
    for (int i = 0; i < TAPE_SIZE; i++) tape[i] = BLANK;
    for (int i = 0; i < len; i++) {
        if (input[i] != 'a' && input[i] != 'b') {
            printf("Error: Invalid symbol '%c'. Alphabet is {a, b}.\n", input[i]);
            return false;
        }
        tape[i] = input[i];
    }

    int head = 0;
    int state = 0;
    int steps = 0;
    const int MAX_STEPS = 500;

    printf("\n--- Turing Machine Simulation Trace ---\n");
    printf("Input: \"%s\"\n", input);

    while (state != 4 && steps < MAX_STEPS) {
        steps++;
        printTape(tape, head, state);

        char sym = tape[head];

        if (state == 0) {
            if (sym == 'a') {
                tape[head] = 'X';
                head++;
                state = 1;
            } else if (sym == 'Y') {
                head++;
                state = 3;
            } else {
                /* Unexpected symbol in q0 */
                break;
            }
        } else if (state == 1) {
            if (sym == 'a' || sym == 'Y') {
                head++;
                state = 1;
            } else if (sym == 'b') {
                tape[head] = 'Y';
                head--;
                state = 2;
            } else {
                /* No matching 'b' found */
                break;
            }
        } else if (state == 2) {
            if (sym == 'a' || sym == 'Y') {
                head--;
                state = 2;
            } else if (sym == 'X') {
                head++;
                state = 0;
            } else {
                break;
            }
        } else if (state == 3) {
            if (sym == 'Y') {
                head++;
                state = 3;
            } else if (sym == BLANK) {
                state = 4; /* ACCEPT */
            } else {
                break;
            }
        }
    }

    if (state == 4) {
        printTape(tape, head, state);
        printf("\n>>> RESULT: ACCEPTED - Turing Machine halted in accepting state q4 after %d steps!\n", steps);
        return true;
    } else {
        printf("\n>>> RESULT: REJECTED - Turing Machine halted in non-accepting state q%d.\n", state);
        return false;
    }
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 15: Turing Machine Simulator for Language a^n b^n (n >= 1)\n");
    printf(" Tape Alphabet: { a, b, X, Y, B }\n");
    printf("=================================================================\n");

    /* Default check with example n=2 ("aabb") */
    printf("\nVerifying standard string \"aabb\":\n");
    simulateTM("aabb");

    while (1) {
        printf("\nEnter string over {a, b} to test on TM (or type 'exit' to quit): ");
        if (!fgets(input, sizeof(input), stdin)) break;

        /* Remove trailing newline */
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting program.\n");
            break;
        }

        simulateTM(input);
    }

    return 0;
}
