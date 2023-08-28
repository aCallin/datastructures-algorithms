#pragma once
#include <math.h>

/**
 * @brief Represents an array that automatically expands in capacity as elements are added.
 * 
 * @tparam T the type of object stored in the dynamic array
 */
template <typename T>
class DynamicArray {
private:
    T* _list;
    int _size;
    int _capacity;
    float _growthFactor;
public:
    const static int DEFAULT_CAPACITY = 10;
    constexpr static float DEFAULT_GROWTH_FACTOR = 1.5f;

    /**
     * @brief Creates a DynamicArray object with an initial capacity of 10.
     */
    DynamicArray() : DynamicArray(DEFAULT_CAPACITY) { }

    /**
     * @brief Creates a DynamicArray object with a provided initial capacity.
     * 
     * @param capacity the initial capacity of the list
     */
    DynamicArray(int capacity) {
        if (capacity <= 0)
            throw std::invalid_argument("Capacity cannot be <= 0.");
        
        _size = 0;
        _capacity = capacity;
        _list = new T[_capacity];
        _growthFactor = DEFAULT_GROWTH_FACTOR;
    }

    /**
     * @brief Destroys the DynamicArray object, freeing the underlying conatiner but not elements in the container 
     * themselves.
     */
    ~DynamicArray() {
        delete[] _list;
    }

    /**
     * @brief Returns the element in the list at the provided index. No bounds checking.
     * 
     * @param index a position in the list
     * @return T& the element at that position
     */
    T& operator[](int index) const {
        return _list[index];
    }

    /**
     * @brief Returns the size of the list.
     * 
     * @return int how many elements are stored in the list
     */
    int size() const {
        return _size;
    }

    /**
     * @brief Returns the capacity of the list.
     * 
     * @return int how many elements can be stored in the list
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
     * @brief Sets the capacity of the list.
     * 
     * @param capacity how many elements can be stored in the list
     */
    void setCapacity(int capacity) {
        // Handle cases where capacity < _size or capacity == _capacity.
        if (capacity == _capacity)
            return;
        if (capacity < _size)
            throw std::invalid_argument("Cannot make capacity < size.");

        // Copy everything over to a new array of larger capacity.
        _capacity = capacity;
        T* newList = new T[capacity];
        for (int i = 0; i < _size; i++)
            newList[i] = _list[i];
        delete[] _list;
        _list = newList;
    }

    /**
     * @brief Set the growth factor. This determines how much to increase the capacity of the list when it is exceeded. 
     * More specifically, new capacity = ceiling(old capacity * growth factor).
     * 
     * @param growthFactor the new growth factor
     */
    void setGrowthFactor(float growthFactor) {
        if (growthFactor <= 1.0)
            throw std::invalid_argument("Growth factor must be > 1.0.");

        _growthFactor = growthFactor;
    }

    /**
     * @brief Adds an element to the end of the list. Automatically increases the list's capacity if its current 
     * capacity is exceeded.
     * 
     * @param element the element to add to the list
     */
    void add(const T& element) {
        if (_size == _capacity) {
            int newCapacity = ceilf(_capacity * _growthFactor);
            setCapacity(newCapacity);
        }
        _list[_size] = element;
        _size++;
    }

    /**
     * @brief Inserts an element at the given index. Displaced elements are pushed to the right.
     * 
     * @param element the element to add to the list
     * @param index the index to put the element
     */
    void insert(const T& element, int index) {
        if (index < 0 || index > _size)
            throw std::invalid_argument("Index out of bounds.");

        // Add the element to the end of the list and swap it down until in position.
        add(element);
        for (int i = _size - 1; i > index; i--) {
            T temp = _list[i - 1];
            _list[i - 1] = _list[i];
            _list[i] = temp;
        }
    }

    /**
     * @brief Removes the first occurrence of an element from the list.
     * 
     * @param element the element to remove from the list
     * @return bool true if the element was found and removed from the list, false otherwise
     */
    bool remove(const T& element) {
        for (int i = 0; i < _size; i++) {
            if (_list[i] == element) {
                removeAt(i);
                return true;
            }
        }
        return false; // Element not found.
    }

    /**
     * @brief Removes the element at the provided index.
     * 
     * @param index the index of the element to remove
     */
    void removeAt(int index) {
        if (index < 0 || index >= _size)
            throw std::invalid_argument("Index out of bounds.");
        
        for (int j = (index + 1); j < _size; j++)
            _list[j - 1] = _list[j];
        _size--;
    }

    /**
     * @brief Removes every occurrence of an element.
     * 
     * @param element the element to remove completely from the list
     * @return int how many occurrences of the element there were in the list
     */
    int removeAll(const T& element) {
        int numOccurrences = 0;
        for (int i = 0; i < _size; i++) {
            if (_list[i] == element)
                numOccurrences++;
            else { // Move other elements to the left while passing over the list, simulating removal.
                if (numOccurrences > 0)
                    _list[i - numOccurrences] = _list[i];
            }
        }
        _size -= numOccurrences;
        return numOccurrences;
    }

    /**
     * @brief Shrinks the capacity of the list to how many elements there are in the list. This makes capacity == size.
     */
    void shrink() {
        setCapacity(_size);
    }
};
