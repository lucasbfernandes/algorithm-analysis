#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_ITEMS 10
#define MAX_BLOCKS 10
#define MAX_BLOCKS_CAPACITY 100
#define NUMBER_OF_ITERATIONS 10
#define APP_INFINITY 20000000

struct item {
    int totalWeight;
};

struct block {
    int totalCapacity;
    int totalOccupied;
    struct item blockItems[MAX_ITEMS];
    int totalItems;
};

typedef struct item Item;
typedef struct block Block;

void resetBlocks(Block* blocks, int blocksLength, int blocksCapacity) {
    for (int i = 0; i < blocksLength; i++) {
        blocks[i].totalCapacity = blocksCapacity;
        blocks[i].totalOccupied = 0;
        blocks[i].totalItems = 0;
    }
}

int isBlockEligible(Item item, Block block) {
    return (block.totalOccupied + item.totalWeight) <= block.totalCapacity;
}

int runFirstFit(Item* items, int itemsLength, Block* blocks, int blocksLength) {
    int usedBlocks = 0;
    int foundAnswer = 1;
    for (int i = 0; i < itemsLength; i++) {
        int foundBlockSlot = 0;
        for (int j = 0; j < blocksLength; j++) {
            if (isBlockEligible(items[i], blocks[j])) {
                blocks[j].totalOccupied += items[i].totalWeight;
                blocks[j].blockItems[blocks[j].totalItems] = items[i];
                blocks[j].totalItems += 1;
                usedBlocks = usedBlocks >= (j + 1) ? usedBlocks : (j + 1);
                foundBlockSlot = 1;
                break;
            }
        }
        foundAnswer = foundBlockSlot ? foundAnswer : 0;
    }
    return foundAnswer ? usedBlocks : APP_INFINITY;
}

void swapItem(Item* a, Item* b) {
    Item temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void runExponentialFirstFitPermutations(Item* items, int start, int end, Block* blocks, int blocksLength, int blocksCapacity, int* answer) {
    if(start == end) {
        resetBlocks(blocks, blocksLength, blocksCapacity);
        int firstFitResult = runFirstFit(items, end + 1, blocks, blocksLength);
        *answer = firstFitResult < *answer ? firstFitResult : *answer;
        return;
    }
    for(int i = start; i <= end; i++){
        swapItem((items + i), (items + start));
        runExponentialFirstFitPermutations(items, start + 1, end, blocks, blocksLength, blocksCapacity, answer);
        swapItem((items + i), (items + start));
    }
}

void generateRandomData(Item* items, int* itemsLength, int* itemsSum, Block* blocks, int* blocksLength, int* blocksCapacity) {
    *itemsLength = MAX_ITEMS;
    *blocksCapacity = (rand() % MAX_BLOCKS_CAPACITY) + 1;

    *itemsSum = 0;
    for (int i = 0; i < *itemsLength; i++) {
        items[i].totalWeight = (rand() % *blocksCapacity) + 1;
        *itemsSum += items[i].totalWeight;
    }

    *blocksLength = *itemsLength;
    for (int i = 0; i < *blocksLength; i++) {
        blocks[i].totalCapacity = *blocksCapacity;
        blocks[i].totalOccupied = 0;
        blocks[i].totalItems = 0;
    }
}

void readBlocks(Block* blocks, int* blocksLength, int* blocksCapacity, int itemsLength) {
    scanf("%d", blocksCapacity);
    *blocksLength = itemsLength;
    for (int i = 0; i < *blocksLength; i++) {
        blocks[i].totalCapacity = *blocksCapacity;
        blocks[i].totalOccupied = 0;
        blocks[i].totalItems = 0;
    }
}

void readItems(Item* items, int* itemsLength, int* itemsSum) {
    scanf("%d", itemsLength);
    *itemsSum = 0;
    for (int i = 0; i < *itemsLength; i++) {
        scanf("%d", &items[i].totalWeight);
        *itemsSum += items[i].totalWeight;
    }
}

void printItems(Item* items, int itemsLength) {
    for (int i = 0; i < itemsLength; i++) {
        printf("Item #%d: [TotalWeight: %d]\n", i + 1, items[i].totalWeight);
    }
    printf("\n");
}


void printBlocks(Block* blocks, int blocksLength) {
    for (int i = 0; i < blocksLength; i++) {
        printf("Block #%d: [TotalCapacity: %d, TotalOccupied: %d]\n", i + 1, blocks[i].totalCapacity, blocks[i].totalOccupied);
        printItems(blocks[i].blockItems, blocks[i].totalItems);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int itemsLength;
    int itemsSum;
    int blocksLength;
    int blocksCapacity;
    Item items[MAX_ITEMS];
    Block blocks[MAX_BLOCKS];

    clock_t start;
    clock_t end;

    int userInput = 0;
    int printSolution = 1;

    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        if (userInput) {
            readItems(items, &itemsLength, &itemsSum);
            readBlocks(blocks, &blocksLength, &blocksCapacity, itemsLength);
        } else {
            generateRandomData(items, &itemsLength, &itemsSum, blocks, &blocksLength, &blocksCapacity);
        }

        if (printSolution) {
            printf("Items length: %d\n", itemsLength);
            printf("Blocks length: %d\n", blocksLength);
            printf("Blocks capacity: %d\n", blocksCapacity);
            printf("Items sum: %d\n\n", itemsSum);
            printItems(items, itemsLength);
        }

        start = clock();
        int minBlocks = ceil((double)itemsSum / (double)blocksCapacity);

        int ceilSolution = APP_INFINITY;
        runExponentialFirstFitPermutations(items, 0, itemsLength - 1, blocks, minBlocks, blocksCapacity, &ceilSolution);

        if (printSolution) {
            printBlocks(blocks, blocksLength);
            if (ceilSolution == APP_INFINITY) {
                printf("CEIL SOLUTION: NOT FOUND\n\n");
            } else {
                printf("CEIL SOLUTION: %d BLOCKS\n\n", ceilSolution);
            }
        }

        int ceilPlusOneSolution = APP_INFINITY;
        runExponentialFirstFitPermutations(items, 0, itemsLength - 1, blocks, minBlocks + 1, blocksCapacity, &ceilPlusOneSolution);

        if (printSolution) {
            printBlocks(blocks, blocksLength);
            if (ceilPlusOneSolution == APP_INFINITY) {
                printf("CEIL PLUS ONE SOLUTION: NOT FOUND\n\n");
            } else {
                printf("CEIL PLUS ONE SOLUTION: %d BLOCKS\n\n", ceilPlusOneSolution);
            }
        }

        if (printSolution) {
            printf("---------------------------------------\n\n");
        }
        end = clock();

        if (!printSolution) {
            printf("%lf\n", (double)(end - start) / CLOCKS_PER_SEC);
        }
    }

    return 0;
}
