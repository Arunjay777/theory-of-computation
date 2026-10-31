/*
 * EXPERIMENT 03
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to check whether a given string belongs to the language 
 *   defined by a Context Free Grammar (CFG):
 *     S -> 0A1
 *     A -> 0A | 1A | eps
 * 
 * GRAMMAR ANALYSIS:
 *   - The start symbol S replaces with 0A1.
 *   - The non-terminal A derives any sequence of 0s and 1s, or epsilon (A -> (0+1)*).
 *   - Therefore, L(G) = { 0 w 1 | w in {0, 1}* }.
 *   - A string belongs to L(G) iff:
 *       1. Length >= 2
 *       2. Starts with '0'
 *       3. Ends with '1'
 *       4. Every character is either '0' or '1'
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkGrammar(const char *input) {
    int len = strlen(input);

    printf("\n--- CFG Parsing & Derivation ---\n");
    printf("Grammar Rules:\n");
    printf("  S -> 0A1\n");
    printf("  A -> 0A | 1A | eps\n\n");

    if (len < 2) {
        printf("Rejection Reason: String length is %d (< 2). S requires at least '0' and '1'.\n", len);
        return false;
    }

    /* Check validity of all characters */
    for (int i = 0; i < len; i++) {
        if (input[i] != '0' && input[i] != '1') {
            printf("Rejection Reason: Invalid character '%c' at index %d. Alphabet is {0, 1}.\n", input[i], i);
            return false;
        }
    }

    if (input[0] != '0') {
        printf("Rejection Reason: String starts with '%c' instead of '0'. Rule S -> 0A1 violated.\n", input[0]);
        return false;
    }

    if (input[len - 1] != '1') {
        printf("Rejection Reason: String ends with '%c' instead of '1'. Rule S -> 0A1 violated.\n", input[len - 1]);
        return false;
    }

    /* Valid string: display leftmost derivation */
    printf("Valid String! Derivation Steps:\n");
    printf("  S\n");
    printf("  => 0 A 1\n");

    char prefix[256] = "0";
    for (int i = 1; i < len - 1; i++) {
        if (input[i] == '0') {
            printf("  => %s 0 A 1   (using A -> 0A)\n", prefix);
            strcat(prefix, "0");
        } else {
            printf("  => %s 1 A 1   (using A -> 1A)\n", prefix);
            strcat(prefix, "1");
        }
    }

    printf("  => %s 1       (using A -> eps)\n", prefix);
    printf("Successfully derived \"%s\"!\n", input);
    return true;
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 03: String verification for CFG:\n");
    printf("   S -> 0A1\n");
    printf("   A -> 0A | 1A | eps\n");
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

        bool accepted = checkGrammar(input);
        if (accepted) {
            printf(">>> Result: ACCEPTED - \"%s\" belongs to the CFG language.\n", input);
        } else {
            printf(">>> Result: REJECTED - \"%s\" does NOT belong to the CFG language.\n", input);
        }
    }

    return 0;
}
