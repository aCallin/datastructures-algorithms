#pragma once

#include <cstddef>

enum HeapType {max, min};

/**
 * @brief Represents a binary min or max heap.
 * 
 * @tparam T the type of data to store in the heap
 */
template <typename T>
class Heap {
private:
    T* _source;
    std::size_t _count;
    std::size_t _capacity;
    HeapType _type;

    /**
     * @brief Returns the index of which child should be selected for comparison during heapification, based on the 
     * heap's type.
     * 
     * @param parentIndex index of the parent
     * @return int index of left or right child, or index of parent if neither child exists
     */
    int comparisonChildIndex(int parentIndex) const {
        int leftChildIndex = (parentIndex * 2) + 1;
        int rightChildIndex = (parentIndex * 2) + 2;
        bool leftChildExists = leftChildIndex < _count;
        bool rightChildExists = rightChildIndex < _count;

        if (!leftChildExists && !rightChildExists)
            return parentIndex;
        if (leftChildExists && !rightChildExists)
            return leftChildIndex;

        if (_type == HeapType::min)
            return (_source[leftChildIndex] <= _source[rightChildIndex]) ? leftChildIndex : rightChildIndex;
        else
            return (_source[leftChildIndex] >= _source[rightChildIndex]) ? leftChildIndex : rightChildIndex;
    }

    /**
     * @brief Returns whether a parent and child are out of order, based on the heap's type.
     * 
     * @param parentIndex index of parent
     * @param childIndex index of child
     * @return bool true if the parent and child are out of order, false otherwise
     */
    bool outOfOrder(int parentIndex, int childIndex) const {
        if (_type == HeapType::min)
            return _source[parentIndex] > _source[childIndex];
        else
            return _source[parentIndex] < _source[childIndex];
    }

    /**
     * @brief Sifts down an element until in order, based on the heap's type.
     * 
     * @param index index of element
     */
    void siftDown(int index) {
        int parentIndex = index;
        int childIndex = comparisonChildIndex(parentIndex);
        while (outOfOrder(parentIndex, childIndex)) {
            T temp = _source[parentIndex];
            _source[parentIndex] = _source[childIndex];
            _source[childIndex] = temp;

            parentIndex = childIndex;
            childIndex = comparisonChildIndex(parentIndex);
        }
    }

    /**
     * @brief Sifts up an element until in order, based on the heap's type.
     * 
     * @param index index of element
     */
    void siftUp(int index) {
        int childIndex = index;
        int parentIndex = (index - 1) / 2;
        while (childIndex != 0 && outOfOrder(parentIndex, childIndex)) {
            T temp = _source[parentIndex];
            _source[parentIndex] = _source[childIndex];
            _source[childIndex] = temp;

            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
    }
public:
    /**
     * @brief Constructs a new min or max heap.
     * 
     * @param source source array; directly used by the heap
     * @param count how many elements should initially be considered in the source array
     * @param capacity the size of the source array
     * @param type min or max
     */
    Heap(T* source, size_t count, size_t capacity, HeapType type) {
        _source = source;
        _count = count;
        _capacity = capacity;
        _type = type;

        // Bottom-up heapify.
        for (int i = (_count / 2) - 1; i >= 0; i--)
            siftDown(i);
    }

    /**
     * @brief Destroy the heap. Does not attempt to destroy the source array.
     */
    ~Heap() = default;

    /**
     * @brief Returns how many elements are stored in the heap. Not to be confused with capacity.
     * 
     * @return size_t how many elements are stored in the heap
     */
    size_t getCount() const {
        return _count;
    }

    /**
     * @brief Returns how many elements can be stored in the heap. Not to be confused with count.
     * 
     * @return size_t how many elements can be stored in the heap
     */
    size_t getCapacity() const {
        return _capacity;
    }

    /**
     * @brief Returns the heap's type.
     * 
     * @return HeapType either min or max
     */
    HeapType getType() const {
        return _type;
    }

    /**
     * @brief Returns the min or max element in the heap.
     * 
     * @return const T& the min or max element, based on the heap's type.
     */
    const T& getMinMax() const {
        return _source[0];
    }

    /**
     * @brief Returns the min or max element and removes it from the heap.
     * 
     * @return T the min or max element, based on the heap's type
     */
    T extractMinMax() {
        T minMax = _source[0];
        _source[0] = _source[_count - 1];
        _count--;
        siftDown(0);
        return minMax;
    }

    /**
     * @brief Inserts an element into the heap if the capacity has not been reached.
     * 
     * @param element the element to put into the heap
     * @return bool true if there was room and the element was inserted, false otherwise
     */
    bool insert(T element) {
        if (_count < _capacity) {
            _source[_count] = element;
            siftUp(_count);
            _count++;
            return true;
        }
        return false;
    }
};
