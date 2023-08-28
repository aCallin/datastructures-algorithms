#include <stdint.h>

/**
 * @brief Finds the index of a given number in a sorted integer array.
 * 
 * O(lg n) time.
 * 
 * @param A sorted integer array
 * @param n the size of A
 * @param value the number to search for
 * @return int the index of the number in A if found; -1 otherwise
 */
int binarySearch(const int* const A, int n, int value);

/**
 * @brief Finds the index of a given number in a sorted integer array.
 * 
 * Average time complexity of O(lg(lg n)).
 * 
 * @param A sorted integer array
 * @param n the size of A
 * @param value the number to search for
 * @return int the index of the number in A if found; -1 otherwise
 */
int interpolationSearch(const int* const A, int n, int value);
