#pragma once
#include <math.h>

/**
 * @brief Represents a circular array that automatically expands in capacity as elements are added.
 * 
 * @tparam T which type to store in the circular array
 */
template <typename T>
class CircularArray {
private:
    T* _list;
    int _size;
    int _capacity;
    float _growthFactor;
    int _headIndex;
    int _tailIndex;
public:
    const static int DEFAULT_CAPACITY = 10;
    constexpr static float DEFAULT_GROWTH_FACTOR = 1.5f;

    /**
     * @brief Constructs a circular array with the default capacity.
     */
    CircularArray() : CircularArray(DEFAULT_CAPACITY) { }

    /**
     * @brief Constructs a circular array with a provided initial capacity.
     * 
     * @param capacity the initial capacity of the circular array
     */
    CircularArray(int capacity) {
        if (capacity <= 0)
            throw std::invalid_argument("Capacity cannot be <= 0.");

        _list = new T[capacity];
        _size = 0;
        _capacity = capacity;
        _growthFactor = DEFAULT_GROWTH_FACTOR;
        _headIndex = 0;
        _tailIndex = 0;
    }

    /**
     * @brief Destroys the circular array object.
     */
    ~CircularArray() {
        delete[] _list;
    }

    /**
     * @brief Returns the size of the circular array.
     * 
     * @return int the number of elements stored in the circular array
     */
    int getSize() const {
        return _size;
    }

    /**
     * @brief Returns the capacity of the circular array.
     * 
     * @return int how many elements can be stored in the circular array
     */
    int getCapacity() const {
        return _capacity;
    }

    /**
     * @brief Returns the growth factor. See setGrowthFactor() for more details.
     * 
     * @return float the growth factor
     */
    float getGrowthFactor() const {
        return _growthFactor;
    }

    /**
     * @brief Returns the head index.
     * 
     * @return int the index of the head element (i.e., the oldest element in the circular array)
     */
    int getHeadIndex() const {
        return _headIndex;
    }

    /**
     * @brief Returns the tail index.
     * 
     * @return int the index of the tail element (i.e., the newest element in the circular array) + 1
     */
    int getTailIndex() const {
        return _tailIndex;
    }

    /**
     * @brief Returns an element from the circular array. Does not perform bounds checking.
     * 
     * @param index a position in the list
     * @return T& the element at that index
     */
    T& operator[](int index) const {
        return _list[index];
    }

    /**
     * @brief Sets the capacity of the circular array.
     * 
     * @param capacity how many elements can be stored in the circular array
     */
    void setCapacity(int capacity) {
        // Handle cases where capacity < _size or capacity == _capacity.
        if (capacity == _capacity)
            return;
        if (capacity < _size)
            throw std::invalid_argument("Cannot make capacity < size.");

        // Copy everything over to a new array of larger capacity.
        T* newList = new T[capacity];
        for (int i = 0; i < _capacity; i++) {
            int index = (_headIndex + i) % _capacity;
            newList[i] = _list[index];
        }

        // Reset some fields.
        delete[] _list;
        _list = newList;
        _capacity = capacity;
        _headIndex = 0;
        _tailIndex = _size;
    }

    /**
     * @brief Set the growth factor. This determines how much to increase the capacity of the circular array when its 
     * current capacity is exceeded. More specifically, new capacity = ceiling(old capacity * growth factor).
     * 
     * @param growthFactor the new growth factor
     */
    void setGrowthFactor(float growthFactor) {
        if (growthFactor <= 1.0)
            throw std::invalid_argument("Growth factor must be > 1.0.");

        _growthFactor = growthFactor;
    }

    /**
     * @brief Adds an element to the end of the circular array. Automatically increases the capacity of the circular 
     * array if its current capacity is exceeded.
     * 
     * @param element the element to add to the circular array
     */
    void add(const T& element) {
        if (_size == _capacity) {
            int newCapacity = ceilf(_capacity * _growthFactor);
            setCapacity(newCapacity);
        }
        _list[_tailIndex] = element;
        _tailIndex = (_tailIndex + 1) % _capacity;
        _size++;
    }

    /**
     * @brief Removes the oldest element from the circular array. Does not free any memory.
     * 
     * @return T a copy of the oldest element removed
     */
    T remove() {
        int savedHeadIndex = _headIndex;
        removeFast();
        return _list[savedHeadIndex];
    }

    /**
     * @brief Removes the oldest element from the circular array without returning a copy of it. Does not free any 
     * memory.
     */
    void removeFast() {
        if (_size == 0)
            throw std::runtime_error("Cannot remove from circular array when empty.");

        _headIndex = (_headIndex + 1) % _capacity;
        _size--;
    }

    /**
     * @brief Shrinks the capacity of the circular array to how many elements are in it. This makes capacity == size.
     */
    void shrink() {
        setCapacity(_size);
    }
};
