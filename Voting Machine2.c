#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NAME 64
#define LINE_BUF 128

static long read_long(const char *prompt, long min, long max) {
    char line[LINE_BUF];
    char *end;
    long val;

    while (1) {
        if (prompt) {
            printf("%s", prompt);
            fflush(stdout);
        }
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Input error. Exiting.\n");
            exit(EXIT_FAILURE);
        }
        // strip newline handled by strtol
        val = strtol(line, &end, 10);
        if (end == line || (*end != '\n' && *end != '\0')) {
            printf("Please enter a valid integer.\n");
            continue;
        }
        if (val < min || val > max) {
            printf("Please enter a number between %ld and %ld.\n", min, max);
            continue;
        }
        return val;
    }
}

static void read_name(const char *prompt, char *buf, size_t bufsize) {
    char line[LINE_BUF];
    printf("%s", prompt);
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Input error. Exiting.\n");
        exit(EXIT_FAILURE);
    }
    // copy at most bufsize-1 chars and strip newline
    line[strcspn(line, "\n")] = '\0';
    strncpy(buf, line, bufsize - 1);
    buf[bufsize - 1] = '\0';
}

int main(void) {
    char c1[MAX_NAME], c2[MAX_NAME], c3[MAX_NAME];
    long v1 = 0, v2 = 0, v3 = 0;
    long voters;
    long vote;
    long i;

    printf("VICTORIA ELECTRONIC VOTING MACHINE\n");
    printf("Simple program for 3 candidates.\n\n");

    read_name("Candidate 1: ", c1, sizeof(c1));
    read_name("Candidate 2: ", c2, sizeof(c2));
    read_name("Candidate 3: ", c3, sizeof(c3));

    voters = read_long("\nNumber of voters: ", 0, LONG_MAX);
    if (voters == 0) {
        printf("No voters. Exiting.\n");
        return 0;
    }

    for (i = 1; i <= voters; ) {
        char prompt[LINE_BUF];
        snprintf(prompt, sizeof(prompt), "\nVote %ld (1=%s  2=%s  3=%s): ", i, c1, c2, c3);
        vote = read_long(prompt, LONG_MIN, LONG_MAX);

        if (vote == 1) { v1++; i++; }
        else if (vote == 2) { v2++; i++; }
        else if (vote == 3) { v3++; i++; }
        else {
            printf("Invalid vote! Please enter 1, 2, or 3.\n");
            // don't increment i so the same voter retries
        }
    }

    printf("\nRESULTS\n");
    printf("%s = %ld   %s = %ld   %s = %ld\n", c1, v1, c2, v2, c3, v3);

    long max = v1;
    if (v2 > max) max = v2;
    if (v3 > max) max = v3;

    printf("Winner: ");
    int winners = 0;
    if (v1 == max) { if (winners) printf(" & "); printf("%s", c1); winners++; }
    if (v2 == max) { if (winners) printf(" & "); printf("%s", c2); winners++; }
    if (v3 == max) { if (winners) printf(" & "); printf("%s", c3); winners++; }

    if (winners == 1) printf("\n");
    else printf(" (tie)\n");

    printf("\nThank you for using Victoria EVM.\n");
    return 0;
}