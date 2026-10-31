/*
 * EXPERIMENT 06
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to check whether a given string belongs to the language 
 *   defined by a Context Free Grammar (CFG):
 *     S -> 0S1 | eps
 * 
 * GRAMMAR ANALYSIS:
 *   - S -> 0S1 generates one '0' on the left and one '1' on the right.
 *   - S -> eps terminates the recursion.
 *   - Language: L(G) = { 0^n 1^n | n >= 0 }
 *   - Valid strings:   eps (n=0), "01" (n=1), "0011" (n=2), "000111" (n=3), ...
 *   - Invalid strings: "0", "1", "001", "011", "10", "0101", ...
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isBinaryString(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0' && str[i] != '1') return false;
    }
    return true;
}

bool checkGrammar(const char *input) {
    int len = strlen(input);

    printf("\n--- CFG Derivation for S -> 0S1 | eps ---\n");

    if (len == 0 || strcmp(input, "eps") == 0 || strcmp(input, "epsilon") == 0) {
        printf("String is epsilon (n = 0).\n");
        printf("Derivation: S => eps\n");
        return true;
    }

    if (!isBinaryString(input)) {
        printf("Rejection Reason: String contains characters outside {0, 1}.\n");
        return false;
    }

    if (len % 2 != 0) {
        printf("Rejection Reason: String length %d is odd. 0^n 1^n requires equal number of 0s and 1s (even length).\n", len);
        return false;
    }

    int n = len / 2;

    /* Verify first n characters are '0' */
    for (int i = 0; i < n; i++) {
        if (input[i] != '0') {
            printf("Rejection Reason: Character at index %d is '%c', expected '0'.\n", i, input[i]);
            return false;
        }
    }

    /* Verify next n characters are '1' */
    for (int i = n; i < len; i++) {
        if (input[i] != '1') {
            printf("Rejection Reason: Character at index %d is '%c', expected '1'.\n", i, input[i]);
            return false;
        }
    }

    /* Print derivation steps */
    printf("Valid String! Form is 0^%d 1^%d. Derivation Steps:\n", n, n);
    printf("  S\n");

    for (int i = 1; i <= n; i++) {
        printf("  => ");
        for (int j = 0; j < i; j++) printf("0");
        printf(" S ");
        for (int j = 0; j < i; j++) printf("1");
        printf("   (using S -> 0S1)\n");
    }

    printf("  => ");
    for (int j = 0; j < n; j++) printf("0");
    printf(" eps ");
    for (int j = 0; j < n; j++) printf("1");
    printf(" (using S -> eps)\n");

    printf("Successfully derived \"%s\"!\n", input);
    return true;
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 06: String verification for CFG:\n");
    printf("   S -> 0S1 | eps   => Language: 0^n 1^n (n >= 0)\n");
    printf("=================================================================\n");

    while (1) {
        printf("\nEnter input string (type 'eps' for empty, 'exit' to quit): ");
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
