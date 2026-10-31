/*
 * EXPERIMENT 07
 * COURSE: CSA13 - THEORY OF COMPUTATION
 * 
 * AIM:
 *   Write a C program to check whether a given string belongs to the language 
 *   defined by a Context Free Grammar (CFG):
 *     S -> A101A
 *     A -> 0A | 1A | eps
 * 
 * GRAMMAR ANALYSIS:
 *   - The non-terminal A generates (0 + 1)* (any sequence of 0s and 1s, or epsilon).
 *   - S derives: (0+1)* 101 (0+1)*.
 *   - Language: All binary strings containing "101" as a substring.
 *   - Valid strings:   "101", "0101", "1010", "11011", "0010100", ...
 *   - Invalid strings: "0", "1", "00", "11", "111", "1001", "0110", ...
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

    printf("\n--- CFG Derivation for S -> A101A, A -> 0A | 1A | eps ---\n");

    if (len < 3) {
        printf("Rejection Reason: Length is %d (< 3). String must contain substring \"101\".\n", len);
        return false;
    }

    if (!isBinaryString(input)) {
        printf("Rejection Reason: String contains characters outside {0, 1}.\n");
        return false;
    }

    /* Find substring "101" */
    char *sub = strstr(input, "101");
    if (sub == NULL) {
        printf("Rejection Reason: Substring \"101\" not found anywhere in \"%s\".\n", input);
        return false;
    }

    /* Split into prefix A, "101", and suffix A */
    int prefix_len = sub - input;
    char prefix[256];
    strncpy(prefix, input, prefix_len);
    prefix[prefix_len] = '\0';

    const char *suffix = sub + 3;

    printf("Match found!\n");
    printf("  Prefix u   = \"%s\"\n", prefix);
    printf("  Keyword    = \"101\"\n");
    printf("  Suffix v   = \"%s\"\n", suffix);

    printf("\nDerivation Steps:\n");
    printf("  S\n");
    printf("  => A 101 A\n");

    /* Derive prefix from first A */
    char cur_pre[256] = "";
    for (int i = 0; i < prefix_len; i++) {
        char ch = prefix[i];
        printf("  => %s%cA 101 A   (using A -> %cA)\n", cur_pre, ch, ch);
        int clen = strlen(cur_pre);
        cur_pre[clen] = ch;
        cur_pre[clen + 1] = '\0';
    }
    printf("  => %s 101 A     (using A -> eps for first A)\n", prefix);

    /* Derive suffix from second A */
    char cur_suf[256] = "";
    int suffix_len = strlen(suffix);
    for (int i = 0; i < suffix_len; i++) {
        char ch = suffix[i];
        printf("  => %s 101 %s%cA   (using A -> %cA)\n", prefix, cur_suf, ch, ch);
        int clen = strlen(cur_suf);
        cur_suf[clen] = ch;
        cur_suf[clen + 1] = '\0';
    }
    printf("  => %s 101 %s     (using A -> eps for second A)\n", prefix, suffix);

    printf("Successfully derived \"%s\"!\n", input);
    return true;
}

int main(void) {
    char input[256];

    printf("=================================================================\n");
    printf(" Experiment 07: String verification for CFG:\n");
    printf("   S -> A101A\n");
    printf("   A -> 0A | 1A | eps   => Language: Strings containing \"101\"\n");
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
