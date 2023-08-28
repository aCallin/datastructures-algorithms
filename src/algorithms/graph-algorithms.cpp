#include "graph-algorithms.h"

Graph* minimumSpanningTree(const Graph& graph) {
    Graph* result = new Graph();
    int countEdges = 0;
    for (int i = 0; i < graph.getEdges().size(); i++)
        countEdges += graph.getEdges()[i].size();
    Edge edges[countEdges];

    // Prim's algorithm.
    Heap<Edge> edgeHeap(edges, 0, countEdges, HeapType::min);
    for (int i = 0; i < graph.getVertices().size(); i++) {
        // Insert all edges from the current vertex into a min heap.
        for (int j = 0; j < graph.getEdges()[i].size(); j++)
            edgeHeap.insert(graph.getEdges()[i][j]);
        
        // Build result by repeatedly finding the next smallest valid edge from the min heap.
        bool foundValidEdge = false;
        while (foundValidEdge == false) {
            // Break if there's nothing to do.
            if (edgeHeap.getCount() == 0)
                break;

            // Extract minimum edge. If one of the vertices in the edge is not in result, then add this edge and that 
            // vertex to result. If both vertices are already in result then don't do anything.
            Edge edge = edgeHeap.extractMinMax();
            bool validVertexA = true;
            bool validVertexB = true;
            for (int j = 0; j < result->getVertices().size(); j++) {
                if (result->getVertices()[j] == *edge.vertexA)
                    validVertexA = false;
                if (result->getVertices()[j] == *edge.vertexB)
                    validVertexB = false;
            }
            if (validVertexA)
                result->addVertex(*edge.vertexA);
            if (validVertexB)
                result->addVertex(*edge.vertexB);
            if (validVertexA || validVertexB) {
                result->addEdge(edge);
                foundValidEdge = true;
            }
        }
    }

    return result;
}

/*
 * TODO: something tells me the heap is not being used correctly here. I don't think all reachable edges are supposed 
 * to be considered, only the smallest edges until all reachable vertices have been marked as visited. Otherwise, why 
 * use a min heap and not just a queue?
 * 
 * Implementation: https://youtu.be/CerlT7tTZfY
 * 
 * Also, room for improvement: make indexOfVertex O(1) with something like a hash table. Right now it is O(|V|) which 
 * may slow the algorithm down for large graphs.
 * 
 * A good article that takes a slightly different approach: https://www.baeldung.com/cs/dijkstra-time-complexity
*/

DijkstraInfo* singleSourceShortestPath(const Graph& graph, const Vertex& origin) {
    // Set up some variables.
    const Vertex* vertex = &origin;
    int vertexIndex = graph.indexOfVertex(*vertex);

    DijkstraInfo* dijkstraTable = new DijkstraInfo[graph.getVertices().size()];
    dijkstraTable[vertexIndex].visited = true;
    dijkstraTable[vertexIndex].predecessor = &origin;
    dijkstraTable[vertexIndex].cost = 0;
    for (int i = 0; i < graph.getVertices().size(); i++) {
        if (i != vertexIndex) {
            dijkstraTable[i].visited = false;
            dijkstraTable[i].predecessor = nullptr;
            dijkstraTable[i].cost = INT32_MAX;
        }
    }

    Edge edgeHeapSource[graph.edgeCount()];
    Heap<Edge> edgeHeap(edgeHeapSource, 0, graph.edgeCount(), HeapType::min);

    // Algorithm.
    bool working = true;
    while (working) {
        // Process current unvisited vertex.
        for (int i = 0; i < graph.getEdges()[vertexIndex].size(); i++) {
            const Edge& edge = graph.getEdges()[vertexIndex][i];
            const Vertex& adjacentVertex = (*edge.vertexA == *vertex) ? *edge.vertexB : *edge.vertexA;
            const int adjacentVertexIndex = graph.indexOfVertex(adjacentVertex);
            
            // If the adjacent vertex has not been visited yet, then add the edge going to that vertex to the heap.
            if (dijkstraTable[adjacentVertexIndex].visited == false)
                edgeHeap.insert(edge);

            // Check if this edge offers a better path cost to the adjacent vertex than what has so far.
            int currentCost = dijkstraTable[adjacentVertexIndex].cost;
            int newCost = dijkstraTable[vertexIndex].cost + edge.weight;
            if (newCost < currentCost) {
                dijkstraTable[adjacentVertexIndex].predecessor = vertex;
                dijkstraTable[adjacentVertexIndex].cost = newCost;
            }
        }

        // Point to the next unvisited vertex. How: keep extracting the next smallest edge from the heap until a vertex 
        // has been found that has not been visited yet.
        while (edgeHeap.getCount() > 0) {
            const Edge& edge = edgeHeap.extractMinMax();
            int vertexAIndex = graph.indexOfVertex(*edge.vertexA);
            int vertexBIndex = graph.indexOfVertex(*edge.vertexB);
            bool vertexAVisited = dijkstraTable[vertexAIndex].visited;
            bool vertexBVisited = dijkstraTable[vertexBIndex].visited;
            
            if (vertexAVisited == false) {
                vertex = edge.vertexA;
                vertexIndex = vertexAIndex;
            } else if (vertexBVisited == false) {
                vertex = edge.vertexB;
                vertexIndex = vertexBIndex;
            }
            if (vertexAVisited == false || vertexBVisited == false) {
                dijkstraTable[vertexIndex].visited = true;
                break;
            }
        }

        // There are no more edges in the heap so there is nowhere to go. Algorithm is done.
        if (edgeHeap.getCount() == 0)
            working = false;
    }

    return dijkstraTable;
}
