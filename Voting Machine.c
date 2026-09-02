#include <stdio.h>

int main() {
    char c1[20], c2[20], c3[20];
    int v1=0, v2=0, v3=0;
    int voters, vote, i;

    printf("VICTORIA ELECTRONIC VOTING MACHINE\n");
    printf("Simple program for 3 candidates.\n\n");

    printf("Candidate 1: "); scanf("%s", c1);
    printf("Candidate 2: "); scanf("%s", c2);
    printf("Candidate 3: "); scanf("%s", c3);

    printf("\nNumber of voters: ");
    scanf("%d", &voters);

    for(i=1; i<=voters; ) {
        printf("\nVote %d (1=%s  2=%s  3=%s): ", i, c1, c2, c3);
        scanf("%d", &vote);

        if(vote == 1) { v1++; i++; }
        else if(vote == 2) { v2++; i++; }
        else if(vote == 3) { v3++; i++; }
        else {
            printf("Invalid vote! Please enter 1, 2, or 3.\n");
            continue;   // REPEAT same voter
        }
    }

    printf("\nRESULTS\n");
    printf("%s = %d   %s = %d   %s = %d\n", c1, v1, c2, v2, c3, v3);

    printf("Winner: ");
    if(v1 > v2 && v1 > v3) printf("%s\n", c1);
    else if(v2 > v1 && v2 > v3) printf("%s\n", c2);
    else if(v3 > v1 && v3 > v2) printf("%s\n", c3);
    else printf("Tie\n");

    printf("\nThank you for using Group 13 EVM.\n");
    return 0;
}
