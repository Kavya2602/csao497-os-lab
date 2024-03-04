#include <stdio.h>
#define MAX_BLOCKS 100
int main() {
    int memory[MAX_BLOCKS]; 
    int blockSize[MAX_BLOCKS]; 
    int numBlocks, numProcesses, processSize[MAX_BLOCKS], allocation[MAX_BLOCKS];
    int i, j;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);
    printf("Enter the size of each memory block:\n");
    for (i = 0; i < numBlocks; i++) {
        scanf("%d", &blockSize[i]);
        memory[i] = blockSize[i]; 
    }
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the size of each process:\n");
    for (i = 0; i < numProcesses; i++) {
        scanf("%d", &processSize[i]);
        allocation[i] = -1; 
    }
    for (i = 0; i < numProcesses; i++) {
        int bestFitIdx = -1;
        for (j = 0; j < numBlocks; j++) {
            if (memory[j] >= processSize[i]) {
                if (bestFitIdx == -1 || memory[j] < memory[bestFitIdx]) {
                    bestFitIdx = j;
                }
            }
        }
        if (bestFitIdx != -1) {
            allocation[i] = bestFitIdx;
            memory[bestFitIdx] -= processSize[i]; 
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < numProcesses; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i]+1);
        } else {
            printf("Not Allocated\n");
        }
    }
    return 0;
}
