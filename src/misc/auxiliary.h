#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include "dynamic-array.h"
#include "circular-array.h"
#include "linked-list.h"
#include "graph.h"
#include "graph-algorithms.h"
#include "alphabet-set.h"

/**
 * @brief Creates an array of random integer values in a range.
 * 
 * @param n the size of the array
 * @param min the minimum value (inclusive) that can be generated
 * @param max the maximum value (inclusive) that can be generated
 * @return int* an array of size n storing integer values between min and max (inclusive)
 */
int* randomIntArray(int n, int min, int max);

/**
 * @brief Prints the contents of an integer array.
 * 
 * @param A the integer array
 * @param n the size of A
 */
void printIntArray(const int* const A, int n);

/**
 * @brief Prints the contents of a dynamic array.
 * 
 * @tparam T list content type
 * @param list the dynamic array
 */
template <typename T>
void printDynamicArray(const DynamicArray<T>& list) {
    for (int i = 0; i < list.size(); i++)
        std::cout << list[i] << " ";
    std::cout << std::endl;
}

/**
 * @brief Prints the contents of a circular array in the order of head element to tail element.
 * 
 * @tparam T the type of element stored in the circular array
 * @param circularArray the circular array
 */
template <typename T>
void printCircularArray(const CircularArray<T>& circularArray) {
    std::cout << "Circular array (n=" << circularArray.getSize() << ", c=" << circularArray.getCapacity() << "): ";
    for (int i = 0; i < circularArray.getSize(); i++) {
        int index = (circularArray.getHeadIndex() + i) % circularArray.getCapacity();
        std::cout << circularArray[index] << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Prints the contents of a linked list.
 * 
 * @tparam T list content type
 * @param linkedList the linked list
 */
template <typename T>
void printLinkedList(const LinkedList<T>& linkedList) {
    for (int i = 0; i < linkedList.getSize(); i++)
        std::cout << linkedList.get(i) << " ";
    std::cout << std::endl;
}

/**
 * @brief Prints the vertices and edges of an undirected graph.
 * 
 * @param graph the graph to print out
 */
void printGraph(const Graph& graph);

/**
 * @brief Prints the contents of a Dijkstra table.
 * 
 * @param graph the original graph
 * @param dijkstraTable the dijkstra table
 */
void printDijkstraTable(const Graph& graph, const DijkstraInfo* const dijkstraTable);

/**
 * @brief Semantically, returns the start time of a timer. This is used as a point of reference for stopTimer().
 * 
 * @return std::chrono::_V2::system_clock::time_point the system clock's current time
 */
std::chrono::_V2::system_clock::time_point startTimer();

/**
 * @brief Returns how much time has elapsed between start and now.
 * 
 * @param start the start time, probably from startTimer()
 * @return int64_t the system clock's current time - start
 */
int64_t stopTimer(const std::chrono::_V2::system_clock::time_point& start);

/**
 * @brief A demonstration of the linked list data structure.
 * 
 * @param n how many elements to put in the linked list -- less than 3 will demonstrate exception handling
 */
void linkedListDemo(int n);

/**
 * @brief A demonstration of the alphabet set problem.
 */
void alphabetSetDemo();

/**
 * @brief Minimum spanning tree and Dijkstra's algorithm on a simple graph.
 */
void graphDemo1();

/**
 * @brief Minimum spanning tree and Dijkstra's algorithm on a graph of a few real-world locations.
 */
void graphDemo2();
