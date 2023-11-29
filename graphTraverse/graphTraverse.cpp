// HW4.cpp
#include "Graph.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    Graph myGraph;
    myGraph.load(argv[1]);

    std::cout << "Adjacency Matrix:" << std::endl;
    myGraph.display();

    int startVertex = 0; // change this to choose starting vertex
    std::cout << "DFS starting from vertex " << startVertex << ": ";
    myGraph.displayDFS(startVertex);
    std::cout << std::endl;

    std::cout << "BFS starting from vertex " << startVertex << ": ";
    myGraph.displayBFS(startVertex);
    std::cout << std::endl;

    return 0;
}
