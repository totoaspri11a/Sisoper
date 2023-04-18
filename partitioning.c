#include<stdio.h>
#include<stdlib.h>

int totalMemory, blockSize, numberOfBlocks, numberOfProcess;
int *memoryBlockSizes, *processMemory;
int i,p=0, externalFrag=0,internalFrag=0;
int method;

void MFT(FILE *f){
    // Enter the total memory available 
    fscanf(f, "%d", &totalMemory);
    // Enter the block size
    fscanf(f, "%d", &blockSize);
    // calculate the number of blocks and the external fragmentation
    numberOfBlocks=totalMemory/blockSize;
    externalFrag = totalMemory - ( numberOfBlocks * blockSize );

    // Enter the number of processes
    fscanf(f, "%d", &numberOfProcess);
    // allocate memory for the memory block sizes and the memory size of each process
    memoryBlockSizes = (int *) malloc(numberOfBlocks * sizeof(int));
    processMemory = (int *) malloc(numberOfProcess * sizeof(int));
    
    // initialize the memory block sizes and the memory size of each process
    for(int i = 0; i < numberOfBlocks; i++) memoryBlockSizes[i] = blockSize;
    for(int i = 0; i < numberOfProcess; i++) fscanf(f, "%d", &processMemory[i]);

    // For each process, allocate the memory block
    for(i=0;i<numberOfProcess;i++){
        if(processMemory[i] > memoryBlockSizes[p]) 
            printf("P%d -> %d Not allocated.\n", i, processMemory[i]);
        else{
            printf("P%d -> %d is put in %d, %d fragmentation.\n", i, processMemory[i], memoryBlockSizes[p], blockSize - processMemory[i]);
            internalFrag += memoryBlockSizes[p] - processMemory[i];
            p++;
        }
    }
    printf("Memory Allocated: %d\n", totalMemory - externalFrag);
    printf("Internal fragmentation: %d\n", internalFrag);
    printf("External fragmentation: %d\n", externalFrag);
}

void MVT(FILE *f){
    // Enter the total memory available 
    fscanf(f, "%d", &totalMemory);
    int tmpMemory = totalMemory;
    // internal fragmentation
    fscanf(f, "%d", &internalFrag);
    // get number of processes
    fscanf(f, "%d", &numberOfProcess);
    // allocate memory for the memory size of each process
    processMemory = (int *) malloc(numberOfProcess * sizeof(int));
    // initialize the memory size of each process
    for(int i = 0; i < numberOfProcess; i++) fscanf(f, "%d", &processMemory[i]);

    // for each process, allocate and calculate the new memory left
    for(i=0;i<numberOfProcess;i++){
        if (processMemory[i] <= tmpMemory){
            printf("P%d -> %d is put in Mem.\n", i, processMemory[i]);
            tmpMemory -= processMemory[i];
        } else {
            printf("P%d -> %d Not allocated.\n", i, processMemory[i]);
            break;
        }
    }
    printf("Memory Allocated: %d\n", totalMemory - tmpMemory);
    printf("Internal fragmentation: %d\n", internalFrag);
    printf("External fragmentation: %d\n", tmpMemory);

}

int main(){
    FILE *f = fopen("partitioning.txt", "r");
    // obtain the method from input.txt
    fscanf(f, "%d", &method);
    if (method == 1){
        MFT(f);
    } else if (method == 2){
        MVT(f);
    } else {
        printf("Invalid method. Please, input the number 1 or number 2.\n");
    }
   
    fclose(f);
    free(memoryBlockSizes);
    free(processMemory);

    return 0;
}
  