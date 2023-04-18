#include<stdio.h>
#include<stdlib.h>
// first fit
void allocationStrategy(int method, int memoryBlockSizes[], int processSize[], int numberOfProcesses, int memoryPartitions){
    int *allocation = (int *) malloc(numberOfProcesses * sizeof(int));
    // initialize all blocks as unallocated
    for(int i = 0; i < numberOfProcesses; i++) allocation[i] = -1;
    // copy the memory block sizes to a new array to use in the output
    int *temp = (int *) malloc(memoryPartitions * sizeof(int));
    for(int i = 0; i < memoryPartitions; i++) temp[i] = memoryBlockSizes[i];

    for(int i = 0; i < numberOfProcesses; i++){
        int blockIndex = -1; // for best and worst fit
        int numBlock = 0; // for first fit
        for(int j = 0; j < memoryPartitions; j++){
            if(memoryBlockSizes[j] >= processSize[i]){
                if (method == 2){ // best fit strategy
                    if (blockIndex == -1){
                        blockIndex = j;
                    } else if (memoryBlockSizes[blockIndex] > memoryBlockSizes[j]){
                        blockIndex = j;
                    }
                } else if (method == 3){ // worst fit strategy
                    if (blockIndex == -1){
                        blockIndex = j;
                    } else if (!(memoryBlockSizes[blockIndex] > memoryBlockSizes[j])){
                        blockIndex = j;
                    }
                } else { // first fit strategy
                    // allocate the block j to the process i
                    allocation[i] = j;
                    // reduce the memory block size by the process size
                    memoryBlockSizes[j] -= processSize[i];
                    numBlock = j;
                    break;
                }
            }
        }
        if (blockIndex != -1){
            allocation[i] = blockIndex;
            memoryBlockSizes[blockIndex] -= processSize[i];
        }
        if(allocation[i] != -1){
            if (method == 2 || method == 3) {
                printf("P%d -> %d is put in %d, %d partition.\n", i, processSize[i], temp[blockIndex], blockIndex+1);
            } else {
                printf("P%d -> %d is put in %d, %d partition.\n", i, processSize[i], temp[numBlock], numBlock+1);
            }
        } else {
            printf("P%d -> %d is not allocated.\n", i, processSize[i]);
        }
    }
}

int main(){
    int method, memoryPartitions, numberOfProcesses;
    // read method from input.txt
    FILE *f = fopen("allocation.txt", "r");
    fscanf(f, "%d", &method);
    if (method >= 1 && method <= 3) {       
        // read number of memory partitions
        fscanf(f, "%d", &memoryPartitions);
        // read size of each memory partition
        int *memoryBlockSizes = (int *) malloc(memoryPartitions * sizeof(int));
        for(int i = 0; i < memoryPartitions; i++){
            fscanf(f, "%d", &memoryBlockSizes[i]);
        }
        // read number of processes
        fscanf(f, "%d", &numberOfProcesses);
        // read size of each process
        int *processSize = (int *) malloc(numberOfProcesses * sizeof(int));
        for(int i = 0; i < numberOfProcesses; i++){
            fscanf(f, "%d", &processSize[i]);
        }
        fclose(f);
        // call the allocation strategy
        allocationStrategy(method, memoryBlockSizes, processSize, numberOfProcesses, memoryPartitions);
        // free the memory
        free(memoryBlockSizes);
        free(processSize);
    } else {
        printf("Invalid method selected. Please, choose between 1 and 3.\n");
    }
    return 0;
}