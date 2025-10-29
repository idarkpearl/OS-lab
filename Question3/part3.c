#include <stdio.h>

int main() {
    int nb, np; // nb = number of blocks, np = number of processes

    printf("FIRST-FIT MEMORY ALLOCATION\n");

    // Input number of blocks and processes
    printf("\nEnter number of memory blocks: ");
    scanf("%d", &nb);
    printf("Enter number of processes: ");
    scanf("%d", &np);

    int blockSize[nb], processSize[np], allocation[np];

    // Input block sizes
    printf("\nEnter sizes of %d memory blocks:\n", nb);
    for (int i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Input process sizes
    printf("\nEnter sizes of %d processes:\n", np);
    for (int i = 0; i < np; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1; // initially unallocated
    }

    // First-Fit Allocation Logic
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nb; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j; // assign block j to process i
                blockSize[j] -= processSize[i]; // reduce available block size
                break; // move to next process
            }
        }
    }

    // Output results
    printf("\n%-10s%-15s%-15s\n", "Process", "Process Size", "Block Allocated");
    for (int i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("P%-9d%-15dB%-14d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("P%-9d%-15dNot Allocated\n", i + 1, processSize[i]);
    }

    return 0;
}
