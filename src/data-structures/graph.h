#pragma once
#include <string>
#include <vector>

/*
 * Note: it is impossible to create a generic graph covering all situations. This is a very basic, weighted, undirected 
 * graph for the purposes of playing around with some graph algorithms.
*/

struct Vertex {
    std::string tag;

    bool operator==(const Vertex& other) const {
        return tag == other.tag;
    }
};

struct Edge {
    const Vertex* vertexA;
    const Vertex* vertexB;
    int weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }

    bool operator<=(const Edge& other) const {
        return weight <= other.weight;
    }

    bool operator>=(const Edge& other) const {
        return weight >= other.weight;
    }
};

class Graph {
private:
    std::vector<Vertex> _vertices;
    std::vector<std::vector<Edge>> _edges;
    int _adjacencies;

public:
    Graph();
    ~Graph() = default;

    int indexOfVertex(const Vertex& vertex) const;

    const std::vector<Vertex>& getVertices() const;
    const std::vector<std::vector<Edge>>& getEdges() const;

    int vertexCount() const;
    int edgeCount() const;

    void addVertex(const Vertex& vertex);
    void addEdge(const Edge& edge);
};
