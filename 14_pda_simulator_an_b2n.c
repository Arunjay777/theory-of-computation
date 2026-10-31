/*
 * EXPERIMENT 14
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Design a Pushdown Automata (PDA) simulator to accept strings of the form 
 *   a^n b^(2n) for n >= 1 (e.g., "abb", "aabbbb", "aaabbbbbb").
 * 
 * PDA 7-TUPLE M = (Q, Sigma, Gamma, delta, q0, Z0, F):
 *   Q = { q0, q1, q2 }
 *   Sigma = { a, b }
 *   Gamma = { A, Z0 }
 *   Start State: q0
 *   Start Stack Symbol: Z0
 *   Final State: F = { q2 }
 * 
 * DESIGN STRATEGY:
 *   For every 'a' encountered, push TWO 'A's onto the stack.
 *   For every 'b' encountered, pop ONE 'A' from the stack.
 *   This ensures exactly 2 * n 'b's match n 'a's.
 * 
 * TRANSITION RULES:
 *   1. delta(q0, 'a', Z0) = (q0, A A Z0)    [Push two 'A's for first 'a']
 *   2. delta(q0, 'a', 'A') = (q0, A A A)    [Push two 'A's for subsequent 'a']
 *   3. delta(q0, 'b', 'A') = (q1, eps)      [Pop one 'A' on first 'b', switch to q1]
 *   4. delta(q1, 'b', 'A') = (q1, eps)      [Pop one 'A' on each subsequent 'b']
 *   5. delta(q1, eps, Z0) = (q2, Z0)        [Accept on reaching final state q2 with Z0]
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STACK 512

typedef struct {
    char items[MAX_STACK];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = 0;
    s->items[s->top] = 'Z'; /* Z0 */
}

void push(Stack *s, char c) {
    if (s->top < MAX_STACK - 1) {
        s->top++;
        s->items[s->top] = c;
    }
}

char pop(Stack *s) {
    if (s->top >= 0) {
        char c = s->items[s->top];
        s->top--;
        return c;
    }
    return '\0';
}

char peek(Stack *s) {
    if (s->top >= 0) return s->items[s->top];
    return '\0';
}

void printStackContent(Stack *s) {
    printf("[ ");
    for (int i = 0; i <= s->top; i++) {
        if (s->items[i] == 'Z') printf("Z0 ");
        else printf("%c ", s->items[i]);
    }
    printf("] (top)");
}

bool simulatePDA(const char *input) {
    Stack stack;
    initStack(&stack);

    int state = 0; /* q0 */
    int len = strlen(input);

    printf("\n--- PDA Simulation Execution Trace ---\n");
    printf("Input: \"%s\"\n", input);
    printf("Initial Configuration: (q0, \"%s\", ", input);
    printStackContent(&stack);
    printf(")\n");

    if (len == 0) {
        printf("Empty string rejected (requires n >= 1).\n");
        return false;
    }

    int i = 0;
    while (i < len) {
        char ch = input[i];
        char top_sym = peek(&stack);

        printf("\nStep %d:\n", i + 1);
        printf("  Current State: q%d\n", state);
        printf("  Reading Symbol: '%c'\n", ch);
        printf("  Stack Top: %s\n", (top_sym == 'Z' ? "Z0" : (top_sym == 'A' ? "A" : "Empty")));

        if (state == 0) {
            if (ch == 'a') {
                push(&stack, 'A');
                push(&stack, 'A');
                printf("  Action: Pushed TWO 'A's to stack (since rule is a^n b^2n). Remaining input: \"%s\"\n", input + i + 1);
                i++;
            } else if (ch == 'b') {
                if (top_sym == 'A') {
                    pop(&stack);
                    state = 1;
                    printf("  Action: Popped ONE 'A' from stack, transition q0 -> q1. Remaining input: \"%s\"\n", input + i + 1);
                    i++;
                } else {
                    printf("  Action: Error! Encountered 'b' without prior 'a's on stack.\n");
                    return false;
                }
            } else {
                printf("  Error: Invalid symbol '%c'. Alphabet is {a, b}.\n", ch);
                return false;
            }
        } else if (state == 1) {
            if (ch == 'b') {
                if (top_sym == 'A') {
                    pop(&stack);
                    printf("  Action: Popped ONE 'A' from stack, stay in q1. Remaining input: \"%s\"\n", input + i + 1);
                    i++;
                } else {
                    printf("  Action: Error! Stack depleted of 'A's while reading 'b'. Too many 'b's!\n");
                    return false;
                }
            } else if (ch == 'a') {
                printf("  Action: Error! Cannot read 'a' after 'b's have started in q1.\n");
                return false;
            } else {
                printf("  Error: Invalid symbol '%c'.\n", ch);
                return false;
            }
        }

        printf("  Current Stack: ");
        printStackContent(&stack);
        printf("\n");
    }

    printf("\nEnd of Input Reached.\n");
    if (state == 1 && peek(&stack) == 'Z') {
        state = 2; /* q2 is final state */
        printf("Epsilon Transition: delta(q1, eps, Z0) -> (q2, Z0)\n");
        printf("Current State: q2 (ACCEPTING STATE)\n");
        printf("Stack: ");
        printStackContent(&stack);
        printf("\n>>> RESULT: ACCEPTED - \"%s\" is of the form a^n b^(2n)!\n", input);
        return true;
    } else {
        printf("Failed to accept. Final State: q%d, Stack Top: %c (Remaining 'A's indicate fewer 'b's than 2n).\n",
               state, peek(&stack));
        printf(">>> RESULT: REJECTED by PDA!\n");
        return false;
    }
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 14: PDA Simulator to accept strings a^n b^(2n) (n >= 1)\n");
    printf(" Examples: \"abb\" (n=1), \"aabbbb\" (n=2), \"aaabbbbbb\" (n=3)\n");
    printf("=================================================================\n");

    /* Default check with example n=2 ("aabbbb") */
    printf("\nVerifying standard string \"aabbbb\":\n");
    simulatePDA("aabbbb");

    while (1) {
        printf("\nEnter string over {a, b} to test (or type 'exit' to quit): ");
        if (!fgets(input, sizeof(input), stdin)) break;

        /* Remove trailing newline */
        input[strcspn(input, "\r\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting program.\n");
            break;
        }

        simulatePDA(input);
    }

    return 0;
}
