#include "auxiliary.h"

int* randomIntArray(int n, int min, int max) {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(min, max);

    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        int value = distribution(generator);
        A[i] = value;
    }
    return A;
}

void printIntArray(const int* const A, int n) {
    for (int i = 0; i < n; i++)
        std::cout << A[i] << " ";
    std::cout << std::endl;
}

void printGraph(const Graph& graph) {
    for (int i = 0; i < graph.getVertices().size(); i++) {
        // Vertex.
        const Vertex& vertex = graph.getVertices()[i];
        std::cout << vertex.tag << ": " << std::endl;

        // Adjacency list.
        for (int j = 0; j < graph.getEdges()[i].size(); j++) {
            const Edge& edge = graph.getEdges()[i][j];
            std::string destination = (edge.vertexA->tag == vertex.tag) ? edge.vertexB->tag : edge.vertexA->tag;
            std::cout << "  " << destination << " " << edge.weight << std::endl;
        }
    }
}

void printDijkstraTable(const Graph& graph, const DijkstraInfo* const dijkstraTable) {
    for (int i = 0; i < graph.vertexCount(); i++) {
        std::cout << graph.getVertices()[i].tag << ": " << ((dijkstraTable[i].predecessor == nullptr) ? "nullptr" : 
                dijkstraTable[i].predecessor->tag) << ", " << dijkstraTable[i].cost << std::endl;
    }
}

std::chrono::_V2::system_clock::time_point startTimer() {
    return std::chrono::high_resolution_clock::now();
}

int64_t stopTimer(const std::chrono::_V2::system_clock::time_point& start) {
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return elapsed.count();
}

void linkedListDemo(const int n) {
    LinkedList<int> list;

    // Add elements to the list.
    std::cout << "~~~~~ ADD ELEMENTS ~~~~~" << std::endl;
    std::cout << "Linked list size: " << list.getSize() << std::endl;
    std::cout << "Adding " << n << " random integers to the list: ";
    for (int i = 0; i < n; i++) {
        int value = (rand() % 10) + 1;
        std::cout << value << " ";
        list.add(value);
    }
    std::cout << std::endl;
    std::cout << "List size: " << list.getSize() << std::endl;
    std::cout << "List contents: ";
    printLinkedList(list);

    // Remove elements from the list.
    std::cout << std::endl << "~~~~~ REMOVE ELEMENTS ~~~~~" << std::endl;
    std::cout << "Removing a body node (i == 1)" << std::endl;
    list.remove(1);
    std::cout << "List size: " << list.getSize() << std::endl;
    std::cout << "List contents: ";
    printLinkedList(list);
    std::cout << "Removing the head node" << std::endl;
    list.remove(0);
    std::cout << "List size: " << list.getSize() << std::endl;
    std::cout << "List contents: ";
    printLinkedList(list);
    std::cout << "Removing the tail node" << std::endl;
    list.remove(list.getSize() - 1);
    std::cout << "List size: " << list.getSize() << std::endl;
    std::cout << "List contents: ";
    printLinkedList(list);
    std::cout << "Clearing the list" << std::endl;
    list.clear();
    std::cout << "List size: " << list.getSize() << std::endl;
    std::cout << "List contents: ";
    printLinkedList(list);
}

void alphabetSetDemo() {
    int set1 = 0x0000000F; // abcd. Initialize directly (shown here) or add letters individually with setAdd().
    int set2 = 0x0300003C; // cdefyz. Notice how bits 26-31 aren't used.
    int set3 = setComplement(set1);
    int set4 = setUnion(set1, set2);
    int set5 = setIntersection(set1, set2);
    int set6 = setDifference(set1, set2);

    std::cout << "Set 1                       " << setContents(set1) << std::endl;
    std::cout << "Set 2                       " << setContents(set2) << std::endl;
    std::cout << "Set 1 complement            " << setContents(set3) << std::endl;
    std::cout << "Set 1 union Set 2           " << setContents(set4) << std::endl;
    std::cout << "Set 1 intersect Set 2       " << setContents(set5) << std::endl;
    std::cout << "Set 1 difference Set 2      " << setContents(set6) << std::endl;
}

void graphDemo1() {
    // Vertices and edges.
    Vertex verticies[] = {
        {"A"},
        {"B"},
        {"C"},
        {"D"}
    };
    Edge edges[] = {
        {&verticies[0], &verticies[1], 4}, // A - B, 4.
        {&verticies[0], &verticies[2], 2}, // A - C, 2.
        {&verticies[0], &verticies[3], 7}, // A - D, 7.
        {&verticies[2], &verticies[3], 3}, // C - D, 3.
    };
    const int verticiesCount = sizeof(verticies) / sizeof(Vertex);
    const int edgesCount = sizeof(edges) / sizeof(Edge);

    // Put the verticies and edges into a graph.
    Graph graph;
    for (int i = 0; i < verticiesCount; i++)
        graph.addVertex(verticies[i]);
    for (int i = 0; i < edgesCount; i++)
        graph.addEdge(edges[i]);

    // Print the graph.
    std::cout << "Original graph:" << std::endl;
    printGraph(graph);

    // Print the minimum spanning tree.
    std::cout << std::endl << "Minimum spanning tree:" << std::endl;
    Graph* mst = minimumSpanningTree(graph);
    printGraph(*mst);
    delete mst;

    // Print the shortest paths from A.
    DijkstraInfo* dijkstraTable = singleSourceShortestPath(graph, graph.getVertices()[0]);
    std::cout << std::endl << "Shortest paths from A:" << std::endl;
    printDijkstraTable(graph, dijkstraTable);
    delete[] dijkstraTable;
}

void graphDemo2() {
    // List of cities and flights between them.
    Vertex cities[] = {
        {"Dublin"},
        {"London"},
        {"Paris"},
        {"Brussels"},
        {"Prague"},
        {"Bern"},
        {"Madrid"}
    };
    Edge flights[] = {
        {&cities[0], &cities[1], 464},  // Dublin - London, 464km.
        {&cities[0], &cities[2], 783},  // Dublin - Paris, 783km.
        {&cities[1], &cities[2], 340},  // London - Paris, 340km.
        {&cities[1], &cities[3], 320},  // London - Brussels, 320km.
        {&cities[3], &cities[4], 720},  // Brussels - Prague, 720km.
        {&cities[3], &cities[5], 489},  // Brussels - Bern, 489km.
        {&cities[3], &cities[2], 252},  // Brussels - Paris, 252km.
        {&cities[2], &cities[5], 435},  // Paris - Bern, 435km.
        {&cities[2], &cities[6], 1052}, // Paris - Madrid, 1052km.
        {&cities[5], &cities[6], 1151}, // Bern - Madrid, 1151km.
        {&cities[5], &cities[4], 620}   // Bern - Prague, 620km.
    };
    const int countCities = sizeof(cities) / sizeof(Vertex);
    const int countFlights = sizeof(flights) / sizeof(Edge);

    // Compose the cities and flights as a weighted undirected graph.
    Graph graph;
    for (int i = 0; i < countCities; i++)
        graph.addVertex(cities[i]);
    for (int i = 0; i < countFlights; i++)
        graph.addEdge(flights[i]);

    // Print the graph.
    std::cout << "Original graph:" << std::endl;
    printGraph(graph);

    // Print the minimum spanning tree.
    std::cout << std::endl << "Minimum spanning tree:" << std::endl;
    Graph* mst = minimumSpanningTree(graph);
    printGraph(*mst);
    delete mst;

    // Print the shortest paths from Dublin.
    DijkstraInfo* dijkstraTable = singleSourceShortestPath(graph, graph.getVertices()[0]);
    std::cout << std::endl << "Shortest paths from Dublin:" << std::endl;
    printDijkstraTable(graph, dijkstraTable);
    delete[] dijkstraTable;
}
