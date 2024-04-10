#include <stdio.h>
#include <stdbool.h>

#define P 5 // # of processes
#define R 3 // # of resources

int need[P][R];

void calculateNeed(int need[P][R], int max[P][R], int allot[P][R], int avail[R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < P; i++) {
        printf("P%d ", i);
        for (int j = 0; j < R; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailable Resources:\n");
    printf("A B C\n");
    for (int i = 0; i < R; i++) {
        printf("%d ", avail[i]);
    }
    printf("\n");
}

bool checkSafety(int avail[], int max[][R], int allot[][R]) {
    // calculate need matrix
    calculateNeed(need, max, allot, avail);

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
            return false;
        }
    }
    return true;
}

bool requestResources(int process, int request[], int avail[], int max[][R], int allot[][R]) {
    // Check if request can be granted
    for (int i = 0; i < R; i++) {
        if (request[i] > avail[i] || request[i] > max[process][i] - allot[process][i]) {
            printf("Request cannot be granted.\n");
            return false;
        }
    }

    // Try to allocate resources
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allot[process][i] += request[i];
        
    }
    calculateNeed(need, max, allot, avail); // Update need matrix

    // Check if system remains in safe state
    printf("System is a in a safe state. Request granted.\n");
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
    if (checkSafety(avail, max, alloc)) {
        int process_id;
        int request[R];
        printf("\nEnter process id (0 to 4): ");
        scanf("%d", &process_id);
        printf("Enter resource request [A, B, C]: ");
        for (int i = 0; i < R; i++) {
            scanf("%d", &request[i]);
        }
        requestResources(process_id, request, avail, max, alloc);
    }

    return 0;
}
