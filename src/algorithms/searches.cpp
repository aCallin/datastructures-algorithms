#include "searches.h"

int binarySearch(const int* const A, int n, int value) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (A[mid] == value)
            return mid;
        if (A[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1; // Value not found.
}

int interpolationSearch(const int* const A, int n, int value) {
    int64_t low = 0;
    int64_t high = n - 1;

    while (low <= high) {
        int64_t numerator = (value - A[low]) * (high - low);
        int64_t denominator = A[high] - A[low];
        int64_t index = low + numerator / denominator;

        if (A[index] == value)
            return index;
        else if (A[index] < value)
            low = index + 1;
        else // A[index] > value.
            high = index - 1;
    }

    return -1; // Value not found.
}
