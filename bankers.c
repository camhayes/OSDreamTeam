#include <stdio.h>
#include <stdbool.h>

#define P 5 // # of processes
#define R 3 // # of resources

void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

bool checkSafety(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    
    // calculate need matrix
    calculateNeed(need, max, allot);

    bool finish[P] = {0}; // array of falses
    int safeSeq[P];
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }

                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in safe state");
            // what else do we need here?
            return false;
        }
    }
    // system is safe - now what?
    return true;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {3, 3, 2};

    // i generated these values randomly
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    
    // resource allocation here?

    // Check system is in safe state or not
    checkSafety(processes, avail, max, alloc);

    return 0;
}
