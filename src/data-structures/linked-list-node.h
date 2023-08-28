#pragma once

/**
 * @brief Represents a singly-linked node to be used in a linked list data structure.
 * 
 * @tparam T the type of element stored in the node
 */
template <typename T>
class LinkedListNode {
private:
    T _element;
    LinkedListNode* _next;
public:
    /**
     * @brief Construct a new LinkedListNode object.
     */
    LinkedListNode() {
        _next = nullptr;
    }

    /**
     * @brief Destroy the LinkedListNode object.
     */
    ~LinkedListNode() = default;

    /**
     * @brief Returns the element stored in this node.
     * 
     * @return const T& the element stored in this node
     */
    const T& getElement() const {
        return _element;
    }

    /**
     * @brief Returns the next node that this node points to.
     * 
     * @return LinkedListNode<T>* the next node
     */
    LinkedListNode<T>* getNext() const {
        return _next;
    }

    /**
     * @brief Sets the element stored in this node.
     * 
     * @param element the element to store in this node
     */
    void setElement(T element) {
        _element = element;
    }

    /**
     * @brief Sets the next node that this node should point to.
     * 
     * @param next the next node
     */
    void setNext(LinkedListNode<T>* const next) {
        _next = next;
    }
};
