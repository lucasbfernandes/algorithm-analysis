#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MAX_ITEMS = 1000;
int MAX_BLOCKS = 1000;
int MAX_BLOCKS_CAPACITY = 100;
int NUMBER_OF_ITERATIONS = 100;

struct block {
    int totalCapacity;
    int totalOccupied;
};

struct item {
    int totalWeight;
};

typedef struct item Item;
typedef struct block Block;

int isBlockEligible(Item item, Block block) {
    return (block.totalOccupied + item.totalWeight) <= block.totalCapacity;
}

int runFirstFit(Item* items, int itemsLength, Block* blocks, int blocksLength) {
    int usedBlocks = 0;
    for (int i = 0; i < itemsLength; i++) {
        for (int j = 0; j < blocksLength; j++) {
            if (isBlockEligible(items[i], blocks[j])) {
                blocks[j].totalOccupied += items[i].totalWeight;
                usedBlocks = usedBlocks >= (j + 1) ? usedBlocks : (j + 1);
                break;
            }
        }
    }
    return usedBlocks;
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
    }
}

void readBlocks(Block* blocks, int* blocksLength, int* blocksCapacity, int itemsLength) {
    scanf("%d", blocksCapacity);
    *blocksLength = itemsLength;
    for (int i = 0; i < *blocksLength; i++) {
        blocks[i].totalCapacity = *blocksCapacity;
        blocks[i].totalOccupied = 0;
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
    int printSolution = 0;

    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        if (userInput) {
            readItems(items, &itemsLength, &itemsSum);
            readBlocks(blocks, &blocksLength, &blocksCapacity, itemsLength);
        } else {
            generateRandomData(items, &itemsLength, &itemsSum, blocks, &blocksLength, &blocksCapacity);
        }

        start = clock();
        int usedBlocks = runFirstFit(items, itemsLength, blocks, blocksLength);
        end = clock();

        if (printSolution) {
            printf("SOLUTION: %d BLOCKS\n", usedBlocks);
        } else {
            printf("%lf\n", (double)(end - start) / CLOCKS_PER_SEC);
        }
    }

    return 0;
}
