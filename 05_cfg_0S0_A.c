/*
 * EXPERIMENT 05
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to check whether a given string belongs to the language 
 *   defined by a Context Free Grammar (CFG):
 *     S -> 0S0 | A
 *     A -> 1A | eps
 * 
 * GRAMMAR ANALYSIS:
 *   - S -> 0S0 adds one '0' at the start and one '0' at the end simultaneously.
 *   - S -> A switches from recursive zero generation to A.
 *   - A -> 1A | eps generates any sequence of '1's (1^m).
 *   - Language: L(G) = { 0^n 1^m 0^n | n >= 0, m >= 0 }
 *   - Condition:
 *       Equal count of leading 0's and trailing 0's (n), with only 1's (m) in the middle.
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

    printf("\n--- CFG Derivation for S -> 0S0 | A, A -> 1A | eps ---\n");

    if (len == 0 || strcmp(input, "eps") == 0 || strcmp(input, "epsilon") == 0) {
        printf("String is epsilon (n=0, m=0).\n");
        printf("Derivation Steps:\n");
        printf("  S => A => eps\n");
        return true;
    }

    if (!isBinaryString(input)) {
        printf("Rejection Reason: String contains characters outside {0, 1}.\n");
        return false;
    }

    /* Count leading zeros */
    int leading_zeros = 0;
    while (leading_zeros < len && input[leading_zeros] == '0') {
        leading_zeros++;
    }

    /* If all characters are zeros */
    if (leading_zeros == len) {
        if (len % 2 == 0) {
            int n = len / 2;
            int m = 0;
            printf("String is 0^%d 1^%d 0^%d (n=%d, m=%d).\n", n, m, n, n, m);
            printf("Derivation Steps:\n");
            printf("  S\n");
            for (int i = 1; i <= n; i++) {
                printf("  => ");
                for (int j = 0; j < i; j++) printf("0");
                printf(" S ");
                for (int j = 0; j < i; j++) printf("0");
                printf("   (using S -> 0S0)\n");
            }
            printf("  => ");
            for (int j = 0; j < n; j++) printf("0");
            printf(" A ");
            for (int j = 0; j < n; j++) printf("0");
            printf("   (using S -> A)\n");
            printf("  => ");
            for (int j = 0; j < n; j++) printf("0");
            printf(" eps ");
            for (int j = 0; j < n; j++) printf("0");
            printf(" (using A -> eps)\n");
            printf("Successfully derived \"%s\"!\n", input);
            return true;
        } else {
            printf("Rejection Reason: All zeros with odd length %d cannot have equal leading and trailing zeros with 0^n 1^m 0^n.\n", len);
            return false;
        }
    }

    /* Count middle ones */
    int ones_start = leading_zeros;
    int ones_count = 0;
    while (ones_start + ones_count < len && input[ones_start + ones_count] == '1') {
        ones_count++;
    }

    /* Count trailing zeros */
    int trailing_zeros_start = ones_start + ones_count;
    int trailing_zeros = 0;
    while (trailing_zeros_start + trailing_zeros < len && input[trailing_zeros_start + trailing_zeros] == '0') {
        trailing_zeros++;
    }

    /* Verify if trailing zeros reach end of string */
    if (trailing_zeros_start + trailing_zeros != len) {
        printf("Rejection Reason: Additional 1s found after trailing zeros. Grammar only permits 0^n 1^m 0^n.\n");
        return false;
    }

    /* Check if leading zeros == trailing zeros */
    if (leading_zeros != trailing_zeros) {
        printf("Rejection Reason: Leading zeros (%d) != Trailing zeros (%d). Must be equal (n).\n",
               leading_zeros, trailing_zeros);
        return false;
    }

    int n = leading_zeros;
    int m = ones_count;
    printf("Valid pattern: 0^%d 1^%d 0^%d (n=%d, m=%d).\n", n, m, n, n, m);
    printf("Derivation Steps:\n");
    printf("  S\n");
    for (int i = 1; i <= n; i++) {
        printf("  => ");
        for (int j = 0; j < i; j++) printf("0");
        printf(" S ");
        for (int j = 0; j < i; j++) printf("0");
        printf("   (using S -> 0S0)\n");
    }

    printf("  => ");
    for (int j = 0; j < n; j++) printf("0");
    printf(" A ");
    for (int j = 0; j < n; j++) printf("0");
    printf("   (using S -> A)\n");

    for (int i = 1; i <= m; i++) {
        printf("  => ");
        for (int j = 0; j < n; j++) printf("0");
        for (int j = 0; j < i; j++) printf("1");
        printf(" A ");
        for (int j = 0; j < n; j++) printf("0");
        printf("   (using A -> 1A)\n");
    }

    printf("  => ");
    for (int j = 0; j < n; j++) printf("0");
    for (int j = 0; j < m; j++) printf("1");
    for (int j = 0; j < n; j++) printf("0");
    printf("   (using A -> eps)\n");

    printf("Successfully derived \"%s\"!\n", input);
    return true;
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 05: String verification for CFG:\n");
    printf("   S -> 0S0 | A\n");
    printf("   A -> 1A | eps   => Language: 0^n 1^m 0^n (n>=0, m>=0)\n");
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
