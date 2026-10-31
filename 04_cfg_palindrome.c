/*
 * EXPERIMENT 04
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to check whether a given string belongs to the language 
 *   defined by a Context Free Grammar (CFG):
 *     S -> 0S0 | 1S1 | 0 | 1 | eps
 * 
 * GRAMMAR ANALYSIS:
 *   - S -> 0S0 generates matching '0' on both ends.
 *   - S -> 1S1 generates matching '1' on both ends.
 *   - Base cases:
 *       S -> 0    (single middle '0' for odd-length palindrome)
 *       S -> 1    (single middle '1' for odd-length palindrome)
 *       S -> eps  (empty center for even-length palindrome)
 *   - Therefore, L(G) is the set of ALL PALINDROMES over {0, 1}.
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

    printf("\n--- CFG Palindrome Derivation ---\n");
    printf("Grammar Rules:\n");
    printf("  S -> 0S0 | 1S1 | 0 | 1 | eps\n\n");

    if (len == 0 || strcmp(input, "eps") == 0 || strcmp(input, "epsilon") == 0) {
        printf("String is epsilon (empty string).\n");
        printf("Derivation: S => eps\n");
        return true;
    }

    if (!isBinaryString(input)) {
        printf("Rejection Reason: String contains characters outside {0, 1}.\n");
        return false;
    }

    /* Check palindrome property */
    int left = 0;
    int right = len - 1;
    while (left < right) {
        if (input[left] != input[right]) {
            printf("Mismatch found: input[%d] = '%c' != input[%d] = '%c'.\n",
                   left, input[left], right, input[right]);
            printf("Rejection Reason: String is not a palindrome, cannot be derived by S -> 0S0 | 1S1.\n");
            return false;
        }
        left++;
        right--;
    }

    /* Print derivation steps */
    printf("String is a valid palindrome! Derivation Steps:\n");
    printf("  S\n");

    char prefix[256] = "";
    char suffix[256] = "";

    left = 0;
    right = len - 1;

    while (left < right) {
        char ch = input[left];
        int plen = strlen(prefix);
        prefix[plen] = ch;
        prefix[plen + 1] = '\0';

        char temp[256];
        snprintf(temp, sizeof(temp), "%c%s", ch, suffix);
        strcpy(suffix, temp);

        printf("  => %s S %s   (using S -> %cS%c)\n", prefix, suffix, ch, ch);
        left++;
        right--;
    }

    if (left == right) {
        /* Odd length palindrome */
        printf("  => %s %c %s   (using S -> %c)\n", prefix, input[left], suffix, input[left]);
    } else {
        /* Even length palindrome */
        printf("  => %s eps %s (using S -> eps)\n", prefix, suffix);
    }

    printf("Successfully derived \"%s\"!\n", input);
    return true;
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 04: String verification for CFG (Palindromes):\n");
    printf("   S -> 0S0 | 1S1 | 0 | 1 | eps\n");
    printf("=================================================================\n");

    while (1) {
        printf("\nEnter input string over {0, 1} (type 'eps' for empty, 'exit' to quit): ");
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
