#pragma once
#include <vector>

/**
 * @brief The coin selection problem asks: given a collection of coins (values), is there an arrangement of coins 
 * that sum to a certain value? The arrangement may include the same value more than once.
 * 
 * @param values collection of values
 * @param valuesSize size of the collection of values
 * @param targetValue the value the coins should sum to
 * @return std::vector<int> a solution to the coin selection problem, where a size of 0 indicates no solution
 */
std::vector<int> coinSelection(const int* const values, int valuesSize, int targetValue);

/**
 * @brief Represents an item in the 0-1 knapsack problem.
 */
struct KnapsackItem {
    int value;
    int weight;
};

/**
 * @brief The knapsack problem asks: given a collection of items each with their own weight and value, and a knapsack 
 * of a given capacity, what is the most profitable arrangement of items that can be put in the knapsack?
 * 
 * @param items collection of possible knapsack items
 * @param itemsSize size of the collection of possible knapsack items
 * @param capacity capacity of the knapsack
 * @return std::vector<KnapsackItem> a solution to the 0-1 knapsack problem, where a size of 0 indicates no solution
 */
std::vector<KnapsackItem> knapsack0_1(const KnapsackItem* const items, int itemsSize, int capacity);
