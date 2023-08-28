#pragma once

#include <stdexcept>
#include "linked-list-node.h"

/**
 * @brief A singly linked list data structure.
 * 
 * @tparam T the type of data to store in the list
 */
template <typename T>
class LinkedList {
private:
    LinkedListNode<T>* _head;
    int _size;
 
    /**
     * @brief Throws an invalid argument exception if the provided index is out of bounds of the list.
     * 
     * @param index list index
     */
    void assertIndexInBounds(int index) const {
        if (index < 0 || index > _size - 1)
            throw std::invalid_argument("Index value out of bounds");
    }
public:
    /**
     * @brief Construct a new LinkedList object with no elements in it.
     */
    LinkedList() {
        _head = nullptr;
        _size = 0;
    }

    /**
     * @brief Destroy the LinkedList object. This calls the clear() method first to remove all elements from the list.
     */
    ~LinkedList() {
        clear();
    }

    /**
     * @brief Returns how many elements are stored in the list.
     * 
     * @return int the size of the list
     */
    int getSize() const {
        return _size;
    }

    /**
     * @brief Gets an element from the list.
     * 
     * @param index the index of the element to get
     * @return const T& the element in the list at the specified index
     */
    const T& get(int index) const {
        assertIndexInBounds(index);
        
        LinkedListNode<T>* node = _head;
        for (int i = 0; i < index; i++)
            node = node->getNext();

        return node->getElement();
    }

    /**
     * @brief Adds an element to the list. New elements are inserted at the back of the list.
     * 
     * @param element the element to add to the list
     */
    void add(T element) {
        LinkedListNode<T>* newNode = new LinkedListNode<T>;
        newNode->setElement(element);

        if (_size == 0)
            _head = newNode;
        else {
            LinkedListNode<T>* tail = _head;
            while (tail->getNext() != nullptr)
                tail = tail->getNext();
            tail->setNext(newNode);
        }

        _size++;
    }

    /**
     * @brief Removes an element from the list.
     * 
     * @param index the index of the element to be removed
     */
    void remove(int index) {
        assertIndexInBounds(index);

        // Special case: remove head node.
        if (index == 0) {
            LinkedListNode<T>* removed = _head;
            _head = _head->getNext();
            delete removed;
        } else {
            // Remove body or tail node.
            LinkedListNode<T>* current = _head;
            for (int i = 0; i < index - 1; i++)
                current = current->getNext();
            LinkedListNode<T>* removed = current->getNext();
            current->setNext(current->getNext()->getNext());
            delete removed;
        }

        _size--;
    }

    /**
     * @brief Clears the contents of the list. The size of the list will be 0 after this operation.
     */
    void clear() {
        while (_size > 0)
            remove(0);
    }
};
