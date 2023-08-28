#pragma once
#include "graph.h"
#include "heap.h"

/**
 * @brief Finds the minimum spanning tree of an undirected, weighted graph. Uses Prim's algorithm.
 * 
 * @param graph the source graph to find the minimum spanning tree of
 * @return Graph* minimum spanning tree
 */
Graph* minimumSpanningTree(const Graph& graph);

/**
 * @brief Used in the single source shortest path problem to keep track of visited vertices and their paths/costs.
 */
struct DijkstraInfo {
    bool visited;
    const Vertex* predecessor;
    int cost;
};

/**
 * @brief Returns a table of the shortest paths from a starting vertex to every other reachable vertex.
 * 
 * @param graph source graph
 * @param origin vertex to start from
 * @return DijkstraInfo* a table of shortest paths info
 */
DijkstraInfo* singleSourceShortestPath(const Graph& graph, const Vertex& origin);
