#include "graph.h"

Graph::Graph() {
    _adjacencies = 0;
}

int Graph::indexOfVertex(const Vertex& vertex) const {
    for (int i = 0; i < _vertices.size(); i++) {
        if (_vertices[i] == vertex)
            return i;
    }
    return -1;
}

const std::vector<Vertex>& Graph::getVertices() const {
    return _vertices;
}

const std::vector<std::vector<Edge>>& Graph::getEdges() const {
    return _edges;
}

int Graph::vertexCount() const {
    return _vertices.size();
}

int Graph::edgeCount() const {
    return _adjacencies / 2;
}

void Graph::addVertex(const Vertex& vertex) {
    _vertices.emplace_back(vertex);
    _edges.emplace_back(std::vector<Edge>());
}

void Graph::addEdge(const Edge& edge) {
    for (int i = 0; i < _vertices.size(); i++) {
        if (_vertices[i] == *edge.vertexA || _vertices[i] == *edge.vertexB) {
            _edges[i].emplace_back(edge);
            _adjacencies++;
        }
    }
}
