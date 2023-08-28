#include "dynamic-programming.h"

std::vector<int> coinSelection(const int* const values, int valuesSize, int targetValue) {
    bool solutions[targetValue + 1];
    solutions[0] = true;
    std::vector<int> result;

    // Calculate solutions.
    for (int i = 1; i <= targetValue; i++) {
        solutions[i] = false;
        for (int j = 0; j < valuesSize; j++) {
            int prevSolutionIndex = i - values[j];
            if (prevSolutionIndex >= 0 && solutions[prevSolutionIndex] == true) {
                solutions[i] = true;
                break;
            }
        }
    }

    // If a solution exists then return one.
    if (solutions[targetValue] == true) {
        int solutionIndex = targetValue;
        while (solutionIndex != 0) {
            for (int i = 0; i < valuesSize; i++) {
                int prevSolutionIndex = solutionIndex - values[i];
                if (prevSolutionIndex >= 0 && solutions[prevSolutionIndex] == true) {
                    result.emplace_back(values[i]);
                    solutionIndex = prevSolutionIndex;
                    break;
                }
            }
        }
    }

    return result;
}

std::vector<KnapsackItem> knapsack0_1(const KnapsackItem* const items, int itemsSize, int capacity) {
    const int rows = itemsSize + 1;
    const int columns = capacity + 1;
    int valueTable[rows][columns];
    std::vector<KnapsackItem> result;

    // Zero the first row.
    for (int column = 0; column <= columns; column++)
        valueTable[0][column] = 0;

    // Fill out the value table.
    for (int row = 1; row < itemsSize + 1; row++) {
        for (int column = 0; column < capacity + 1; column++) {
            int aboveValue = valueTable[row - 1][column];
            int currentCapacity = column;
            const KnapsackItem& currentItem = items[row - 1];

            // Current item is too heavy at this capacity so copy the above value to this cell.
            if (currentItem.weight > currentCapacity)
                valueTable[row][column] = aboveValue;
            else {
                // We can carry this item at this capacity. Check if this item's value + the value at the remaining 
                // capacity is greater than the above value.
                int newValue = currentItem.value + valueTable[row - 1][currentCapacity - currentItem.weight];
                if (newValue > aboveValue)
                    valueTable[row][column] = newValue;
                else
                    valueTable[row][column] = aboveValue;
            }
        }
    }

    // Collect the items from the solution.
    int row = rows - 1;
    int column = columns - 1;
    while (row > 0) {
        int aboveValue = valueTable[row - 1][column];
        int currentValue = valueTable[row][column];
        const KnapsackItem& currentItem = items[row - 1];

        if (currentValue != aboveValue) {
            result.emplace_back(currentItem);
            column -= currentItem.weight;
        }
        row--;
    }

    return result;
}
