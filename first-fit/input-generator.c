#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MAX_ITEMS = 1000;
int MAX_BLOCKS_CAPACITY = 100;

void printBlocksCapacity(int randomBlocksCapacity) {
	printf("%d\n", randomBlocksCapacity);
}

void printItems(int randomItemsLength, int randomBlocksCapacity) {
	for (int i = 0; i < randomItemsLength; i++) {
		int randomItemWeight = (rand() % randomBlocksCapacity) + 1;
		printf("%d ", randomItemWeight);
	}
	printf("\n");
}

void printItemsLength(int randomItemsLength) {
	printf("%d\n", randomItemsLength);
}

int main() {
	srand(time(NULL));

	int randomItemsLength = (rand() % MAX_ITEMS) + 1;
	int randomBlocksCapacity = (rand() % MAX_BLOCKS_CAPACITY) + 1;

	printItemsLength(randomItemsLength);
	printItems(randomItemsLength, randomBlocksCapacity);
	printBlocksCapacity(randomBlocksCapacity);

	return 0;
}
