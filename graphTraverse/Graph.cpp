// Graph.cpp
#include "Graph.h"

Graph::Graph() {
    numVertices = 0;
    adjacencyMatrix = nullptr;
}

// Destructor
Graph::~Graph() { 
    for (int i = 0; i < numVertices; ++i) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

//load function
void Graph::load(const char* filename) {
    std::ifstream inputFile(filename);
    inputFile >> numVertices;

    adjacencyMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        adjacencyMatrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; ++j) {
            adjacencyMatrix[i][j] = 0;  // Initialize the matrix with zeros
        }
    }

    int vertex1, vertex2;
    while (inputFile >> vertex1 >> vertex2) {
        adjacencyMatrix[vertex1][vertex2] = 1;
        adjacencyMatrix[vertex2][vertex1] = 1;
    }

    inputFile.close();
}

// adjacency matrix display
void Graph::display() {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// depth first search
void Graph::displayDFS(int vertex) {
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visited[i] = false;
    }

    DFS(vertex, visited);

    delete[] visited;
}

// recursive call that prints out verticies for dfs
void Graph::DFS(int vertex, bool visited[]) {
    visited[vertex] = true;
    std::cout << vertex << " ";

    for (int i = 0; i < numVertices; ++i) {
        if (adjacencyMatrix[vertex][i] && !visited[i]) {
            DFS(i, visited);
        }
    }
}

// breadth first search
void Graph::displayBFS(int vertex) {
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        visited[i] = false;
    }

    std::queue<int> q;
    visited[vertex] = true;
    q.push(vertex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        std::cout << current << " ";

        for (int i = 0; i < numVertices; ++i) {
            if (adjacencyMatrix[current][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    delete[] visited;
}
