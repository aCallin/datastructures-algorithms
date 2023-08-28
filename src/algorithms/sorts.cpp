#include "sorts.h"

void swap(int* const A, int indexA, int indexB) {
    int temp = A[indexA];
    A[indexA] = A[indexB];
    A[indexB] = temp;
}

void bubbleSort(int* const A, int n) {
    int right = n;
    bool swapped = true;

    while (swapped) {
        swapped = false;
        for (int i = 1; i < right; i++) {
            if (A[i] < A[i - 1]) {
                swap(A, i, i - 1);
                swapped = true;
            }                
        }
        right--; // Sorted subarray grows from the right side of A. No swaps happen in this region so don't compare.
    }
}

void selectionSort(int* const A, int n) {
    for (int i = 0; i < n; i++) {
        // Find the index of the smallest element in the unsorted subarray A[i..n-1].
        int indexSmallest = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[indexSmallest])
                indexSmallest = j;
        }

        // Swap the smallest element with A[i], placing it into the sorted section.
        int temp = A[i];
        A[i] = A[indexSmallest];
        A[indexSmallest] = temp;
    }
}

void insertionSort(int* const A, int n) {
    for (int i = 1; i < n; i++) { // Start at 1 because A[0] is already sorted.
        // Insert the element into the sorted subarray A[0..i-1]. Result: A[0..i] is now sorted.
        for (int j = i; j > 0; j--) {
            // The element is out of order with the previous element --> swap.
            if (A[j] < A[j - 1]) {
                int temp = A[j - 1];
                A[j - 1] = A[j];
                A[j] = temp;
            }
        }
    }
}

void quickSort_r(int* const A, int n, int leftIndex, int rightIndex) {
    if (leftIndex >= rightIndex)
        return;

    // Partition. By the end, the pivot is in its correct spot in the sorted array, and numbers to the left of it are 
    // smaller and numbers to the right of it are larger.
    int pivot = A[rightIndex];
    int j = leftIndex; // j <- index of where to put the next number less than the pivot.
    for (int i = leftIndex; i < rightIndex; i++) {
        if (A[i] < pivot) {
            swap(A, i, j);
            j++;
        }
    }
    swap(A, rightIndex, j); // Put the pivot in its correct spot.

    // Recursively sort the left and right sides of the pivot.
    quickSort_r(A, n, leftIndex, j - 1);
    quickSort_r(A, n, j + 1, rightIndex);
}

void quickSort(int* const A, int n) {
    quickSort_r(A, n, 0, n - 1);
}

void heapSort(int* const A, int n) {
    // Heapify A.
    Heap<int> heap(A, n, n, HeapType::max);

    // Repeatedly extract max, placing it at the sorted section of the array.
    for (int i = n - 1; i >= 0; i--)
        A[i] = heap.extractMinMax();

    // To sort in descending order instead use a min heap and repeatedly extract min.
}

int* countingSort(const int* const A, int n, int min, int max) {
    // Build the count array, which tells us exactly where each value in A should be placed.
    int countsSize = max - min + 1;
    int counts[countsSize] = {};
    for (int i = 0; i < n; i++)
        counts[A[i] - min]++;
    for (int i = 1; i < countsSize; i++)
        counts[i] += counts[i - 1];

    // Build the sorted array by scanning each value in A and asking the count array where it should go.
    int* sorted = new int[n];
    for (int i = n - 1; i >= 0; i--) { // Iterating backwards ensures stability.
        int placement = counts[A[i] - min] - 1;
        sorted[placement] = A[i];
        counts[A[i] - min]--; // So that equal values are placed next to each other.
    }
    return sorted;
}
