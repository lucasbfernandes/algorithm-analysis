#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int MAX_ITEMS = 100000;
int MAX_BLOCKS = 100000;
int APP_INFINITY = 20000000;

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
    int foundAnswer = 1;
    for (int i = 0; i < itemsLength; i++) {
        int foundBlockSlot = 0;
        for (int j = 0; j < blocksLength; j++) {
            if (isBlockEligible(items[i], blocks[j])) {
                blocks[j].totalOccupied += items[i].totalWeight;
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

void runExponentialFirstFitPermutations(Item* items, int start, int end, Block* blocks, int blocksLength, int* answer) {
    if(start == end) {
        int firstFitResult = runFirstFit(items, end + 1, blocks, blocksLength);
        *answer = firstFitResult < *answer ? firstFitResult : *answer;
        return;
    }
    for(int i = start; i <= end; i++){
        swapItem((items + i), (items + start));
        runExponentialFirstFitPermutations(items, start + 1, end, blocks, blocksLength, answer);
        swapItem((items + i), (items + start));
    }
}

void resetBlocks(Block* blocks, int blocksLength, int blocksCapacity) {
    for (int i = 0; i < blocksLength; i++) {
        blocks[i].totalCapacity = blocksCapacity;
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
    int itemsLength;
    int itemsSum;
    int blocksLength;
    int blocksCapacity;
    Item items[MAX_ITEMS];
    Block blocks[MAX_BLOCKS];

    readItems(items, &itemsLength, &itemsSum);
    readBlocks(blocks, &blocksLength, &blocksCapacity, itemsLength);

    int minBlocks = ceil((double)itemsSum / (double)blocksCapacity);

    int ceilSolution = APP_INFINITY;
    runExponentialFirstFitPermutations(items, 0, itemsLength - 1, blocks, minBlocks, &ceilSolution);

    resetBlocks(blocks, blocksLength, blocksCapacity);

    int ceilPlusOneSolution = APP_INFINITY;
    runExponentialFirstFitPermutations(items, 0, itemsLength - 1, blocks, minBlocks + 1, &ceilPlusOneSolution);

    if (ceilSolution == APP_INFINITY) {
        printf("CEIL SOLUTION: NOT FOUND\n");
    } else {
        printf("CEIL SOLUTION: %d BLOCKS\n", ceilSolution);
    }

    if (ceilPlusOneSolution == APP_INFINITY) {
        printf("CEIL PLUS ONE SOLUTION: NOT FOUND\n");
    } else {
        printf("CEIL PLUS ONE SOLUTION: %d BLOCKS\n", ceilPlusOneSolution);
    }

    return 0;
}
