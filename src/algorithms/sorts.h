#pragma once

#include "heap.h"

/**
 * @brief Sorts A by repeatedly "bubbling up" large numbers through the array.
 * 
 * Best case time complexity: O(n). Average and worst case time complexity: O(n^2).
 * 
 * Comparison, in-place, stable.
 * 
 * @param A integer array
 * @param n the size of A
 */
void bubbleSort(int* const A, int n);

/**
 * @brief Sorts A by repeatedly placing the smallest element of the unsorted section of A into the next position of the 
 * sorted section of A. 
 * 
 * Time complexity: O(n^2).
 * 
 * Comparison, in-place, unstable.
 * 
 * @param A integer array
 * @param n the size of A
 */
void selectionSort(int* const A, int n);

/**
 * @brief Sorts A by repeatedly placing the next element of the unsorted section of A into the correct spot of the 
 * sorted section of A.
 * 
 * Best case time complexity: O(n). Average and worst case time complexity: O(n^2).
 * 
 * Comparison, in-place, stable.
 * 
 * @param A integer array
 * @param n the size of A
 */
void insertionSort(int* const A, int n);

/**
 * @brief Sorts A using a divide-and-conquer approach, where partitions are recursively created around pivot points and 
 * then sorted.
 * 
 * Best and average case time complexity: O(n*logn). Worst case time complexity: O(n^2).
 * 
 * Comparison, in-place, unstable.
 * 
 * @param A integer array
 * @param n the size of A
 */
void quickSort(int* const A, int n);

/**
 * @brief Sorts A using a max heap, where the max element is repeatedly extracted from the heap and placed in the 
 * sorted section of the array.
 * 
 * Time complexity: O(n*logn).
 * 
 * Comparison, in-place, unstable.
 * 
 * @param A integer array
 * @param n the size of A
 */
void heapSort(int* const A, int n);

/**
 * @brief Sorts A by counting the number of occurences of each unique value in A, and keeping track of the next 
 * placement of each unique value in the sorted array.
 * 
 * Time complexity: O(n+k), where k is the range of values.
 * 
 * Non-comparison, not-in-place, stable.
 * 
 * @param A integer array
 * @param n the size of A
 * @param min less than or equal to the minimum value in A
 * @param max greater than or equal to the maximum value in A
 * @return int* a copy of A but sorted
 */
int* countingSort(const int* const A, int n, int min, int max);
