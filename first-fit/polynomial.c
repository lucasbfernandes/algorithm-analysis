#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int MAX_ITEMS = 100000;
int MAX_BLOCKS = 100000;

struct block {
    int totalCapacity;
    int totalOccupied;
};

struct item {
    int totalWeight;
};

typedef struct item Item;
typedef struct block Block;

void runFirstFit(Item* items, int itemsLength, Block* blocks) {

}

void readBlocks(Block* blocks, int* blocksLength, int* blocksCapacity, int itemsSum) {
    scanf("%d", blocksCapacity);
    *blocksLength = ceil((double)itemsSum / (double)*blocksCapacity);
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
    readBlocks(blocks, &blocksLength, &blocksCapacity, itemsSum);

    for (int i = 0; i < itemsLength; i++) {
        printf("%d /", items[i].totalWeight);
    }

    for (int i = 0; i < blocksLength; i++) {
        printf("%d %d /", blocks[i].totalCapacity, blocks[i].totalOccupied);
    }

    return 0;
}
