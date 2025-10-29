#include <stdio.h>

int main() {
    int nb, np; // nb = number of blocks, np = number of processes

    printf("WORST-FIT MEMORY ALLOCATION\n");

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
        allocation[i] = -1; // Initially not allocated
    }

    // Worst-Fit allocation
    for (int i = 0; i < np; i++) {
        int worstIndex = -1;

        for (int j = 0; j < nb; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex])
                    worstIndex = j;
            }
        }

        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    // Output table
    printf("\n%-10s%-15s%-15s\n", "Process", "Process Size", "Block Allocated");
    for (int i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("P%-9d%-15dB%-14d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("P%-9d%-15dNot Allocated\n", i + 1, processSize[i]);
    }

    return 0;
}
