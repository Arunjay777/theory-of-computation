/*
 * EXPERIMENT 13
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Design a Pushdown Automata (PDA) simulator to accept the input string "aabb" 
 *   (Language L = { a^n b^n | n >= 1 }).
 * 
 * PDA 7-TUPLE M = (Q, Sigma, Gamma, delta, q0, Z0, F):
 *   Q = { q0, q1, q2 }
 *   Sigma = { a, b }
 *   Gamma = { A, Z0 }
 *   Start State: q0
 *   Start Stack Symbol: Z0
 *   Final State: F = { q2 }
 * 
 * TRANSITION RULES:
 *   1. delta(q0, 'a', Z0) = (q0, A Z0)      [Push 'A' onto stack]
 *   2. delta(q0, 'a', 'A') = (q0, A A)      [Push 'A' onto stack]
 *   3. delta(q0, 'b', 'A') = (q1, eps)      [Pop 'A' and switch to q1]
 *   4. delta(q1, 'b', 'A') = (q1, eps)      [Pop 'A' on each 'b']
 *   5. delta(q1, eps, Z0) = (q2, Z0)        [Accept by reaching final state q2]
 * 
 * INSTANTANEOUS DESCRIPTION (ID) FOR "aabb":
 *   (q0, aabb, Z0) |- (q0, abb, AZ0) |- (q0, bb, AAZ0) |- (q1, b, AZ0) |- (q1, eps, Z0) |- (q2, eps, Z0) [ACCEPTED]
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STACK 256

typedef struct {
    char items[MAX_STACK];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = 0;
    s->items[s->top] = 'Z'; /* Z represents Z0 */
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
        printf("Empty string rejected (PDA requires n >= 1).\n");
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
                printf("  Action: Push 'A' to stack. Remaining input: \"%s\"\n", input + i + 1);
                i++;
            } else if (ch == 'b') {
                if (top_sym == 'A') {
                    pop(&stack);
                    state = 1;
                    printf("  Action: Pop 'A' from stack, transition q0 -> q1. Remaining input: \"%s\"\n", input + i + 1);
                    i++;
                } else {
                    printf("  Action: Error! Encountered 'b' with no 'A' on stack. Transition undefined.\n");
                    return false;
                }
            } else {
                printf("  Error: Invalid symbol '%c'.\n", ch);
                return false;
            }
        } else if (state == 1) {
            if (ch == 'b') {
                if (top_sym == 'A') {
                    pop(&stack);
                    printf("  Action: Pop 'A' from stack, stay in q1. Remaining input: \"%s\"\n", input + i + 1);
                    i++;
                } else {
                    printf("  Action: Error! Encountered 'b' with stack top '%c' (not 'A'). Mismatch in number of a's and b's.\n", top_sym);
                    return false;
                }
            } else if (ch == 'a') {
                printf("  Action: Error! Cannot read 'a' after transitioning to 'b' reading state q1.\n");
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

    /* Input consumed: check epsilon transition delta(q1, eps, Z0) = (q2, Z0) */
    printf("\nEnd of Input Reached.\n");
    if (state == 1 && peek(&stack) == 'Z') {
        state = 2; /* q2 is final state */
        printf("Epsilon Transition: delta(q1, eps, Z0) -> (q2, Z0)\n");
        printf("Current State: q2 (ACCEPTING STATE)\n");
        printf("Stack: ");
        printStackContent(&stack);
        printf("\n>>> RESULT: ACCEPTED by PDA!\n");
        return true;
    } else {
        printf("Failed to reach final state q2 with stack top Z0. Final State: q%d, Stack Top: %c\n", state, peek(&stack));
        printf(">>> RESULT: REJECTED by PDA!\n");
        return false;
    }
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 13: PDA Simulator to accept input string \"aabb\"\n");
    printf(" Language: L = { a^n b^n | n >= 1 }\n");
    printf("=================================================================\n");

    /* Default check with target string "aabb" */
    printf("\nVerifying mandatory target string \"aabb\":\n");
    simulatePDA("aabb");

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
