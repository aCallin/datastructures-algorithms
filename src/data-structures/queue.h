#pragma once
#include "circular-array.h"

/**
 * @brief Represents a queue: a FIFO data structure where the first element in is the first element out. The queue 
 * automatically grows in size when its capacity is exceeded.
 * 
 * @tparam T the type of the elements being stored in the queue
 */
template <typename T>
class Queue {
private:
    CircularArray<T>* _circularArray; // Pointer so we can delay creation until knowing capacity.
public:
    /**
     * @brief Construct a queue with the default capacity. Default capacity is determined by the circular array data 
     * structure.
     */
    Queue() {
        _circularArray = new CircularArray<T>();
    };

    /**
     * @brief Construct a queue with a provided initial capacity.
     * 
     * @param capacity the initial capacity of the queue.
     */
    Queue(int capacity) {
        _circularArray = new CircularArray<T>(capacity);
    }

    /**
     * @brief Destroy the queue.
     */
    ~Queue() {
        delete _circularArray;
    };

    /**
     * @brief Returns the element at the front of the queue.
     * 
     * @return const T& the front item in the queue
     */
    const T& peek() const {
        return (*_circularArray)[_circularArray->getHeadIndex()];
    }

    /**
     * @brief Returns the size of the queue.
     * 
     * @return int how many elements are in the queue
     */
    int getSize() const {
        return _circularArray->getSize();
    }

    /**
     * @brief Returns the capacity of the queue.
     * 
     * @return int how many items can be stored in the queue before resizing
     */
    int getCapacity() const {
        return _circularArray->getCapacity();
    }

    /**
     * @brief Returns the queue's growth factor.
     * 
     * @return float how much the queue grows in size when its capacity is excdeeded
     */
    float getGrowthFactor() const {
        return _circularArray->getGrowthFactor();
    }

    /**
     * @brief Sets the capacity of the queue.
     * 
     * @param capacity how many items can be stored in the queue
     */
    void setCapacity(int capacity) const {
        _circularArray->setCapacity(capacity);
    }

    /**
     * @brief Sets the growth factor of the queue.
     * 
     * @param growthFactor how much the queue grows in size when its capacity is exceeded.
     */
    void setGrowthFactor(float growthFactor) const {
        _circularArray->setGrowthFactor(growthFactor);
    }

    /**
     * @brief Adds an element to the back of the queue. 
     * 
     * @param element the element to add to the queue
     */
    void enqueue(const T& element) {
        _circularArray->add(element);
    }

    /**
     * @brief Removes the element at the front of the queue.
     * 
     * @return T the front element removed from the queue
     */
    T dequeue() {
        return _circularArray->remove();
    }
};
