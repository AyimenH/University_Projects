// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <queue>

class Graph {
private:
    int** adjacencyMatrix;
    int numVertices;

public:
    Graph();
    ~Graph();
    void load(const char* filename);
    void display(); //for adjacency matrix
    void displayDFS(int vertex);
    void displayBFS(int vertex);

private:
    void DFS(int vertex, bool visited[]); //helper used in DisplayDFS
};

#endif // GRAPH_H
