#include <stdio.h>
#include <stdlib.h>

int MAX_ITEMS = 100000;
int MAX_BLOCKS = MAX_ITEMS;

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

    int usedBlocks = runFirstFit(items, itemsLength, blocks, blocksLength);
    printf("SOLUTION: %d BLOCKS\n", usedBlocks);

    return 0;
}
