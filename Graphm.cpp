/*
 * Graphm.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: aaronc
 */

#include "Graphm.h"
#include <fstream>
#include <sstream>


Graphm::Graphm(int numVert) {
    Init(numVert);
}

Graphm::~Graphm() {
    delete[] mark;
    delete[] matrix;
}

void Graphm::Init(int n) {
    int i;
    numVertex = n;
    numEdge = 0;
    mark = new int[n];
    for (i = 0; i < numVertex; ++i) {
        mark[i] = 0;
    }

    int arraySize = (((n-1) * (n-2) / 2) + n-2);
    matrix = new int [arraySize + 1];
    for (i = 0; i <= arraySize; ++i) {
        matrix[i] = 0;
    }
}

int Graphm::vertices() {
    return numVertex;
}

int Graphm::edges() {
    return numEdge;
}

int Graphm::first(int v) {
    if (v > 0) {
        int location = (v * (v-1) / 2);
        for (int i = 0; i < v; ++i) {
            if (matrix[location + i] != 0) return i;
        }
    }
    for (int i = v + 1; i < numVertex; ++i) {
        int location = (i * (i-1) / 2);
        if (matrix[location + v] != 0) return i;
    }
    return numVertex;
}

int Graphm::next(int v1, int v2) {
    if (v1 > v2) {
        int location = (v1 * (v1-1) / 2);
        for (int i = v2 + 1; i < v1; ++i) {
            if (matrix[location + i] != 0) return i;
        }
    }
    int largest = v1;
    if (v2 > largest) { largest = v2; };
    for (int i = largest + 1; i < numVertex; ++i) {
        int location = (i * (i-1) / 2);
        if (matrix[location + v1] != 0) return i;
    }
    return numVertex;
}

void Graphm::setEdge(int v1, int v2, int wt) {
    if (wt <= 0) return;
    if (v2 > v1) {
        int temp = v1;
        v1 = v2;
        v2 = temp;
    }
    int location = ((v1 * (v1-1) / 2) + v2);
    if (matrix[location] == 0) ++numEdge;
    matrix[location] = wt;
}

void Graphm::delEdge(int v1, int v2) {
    if (v2 > v1) {
        int temp = v1;
        v1 = v2;
        v2 = temp;
    }
    int location = ((v1 * (v1-1) / 2) + v2);
    if (matrix[location] != 0) numEdge--;
    matrix[location] = 0;
}

bool Graphm::isEdge(int v1, int v2) {
    if (v2 > v1) {
        int temp = v1;
        v1 = v2;
        v2 = temp;
    }
    int location = (((v1 * (v1-1)) / 2) + v2);
    return matrix[location] != 0;
}

int Graphm::weight(int v1, int v2) {
    if (v2 > v1) {
        int temp = v1;
        v1 = v2;
        v2 = temp;
    }
    int location = ((v1 * (v1-1) / 2) + v2);
    return matrix[location];
}

int Graphm::getMark(int v) {
    return mark[v];
}

void Graphm::setMark(int v, int val) {
    mark[v] = val;
}




/*
 * The format of the file for storing the graphs is:
 * Size of Graph
 * Graph Vertex, Graph Vertex, Edge Weight
 * Graph Vertex, Graph Vertex, Edge Weight
 * ...
 *
 * This format continues for the number of edges in the graph.
 * When the reader hits the end of file, it is complete.
 */

Graph* readGraph(std::string filename) {
    std::ifstream input (filename.c_str());
    if (!input.is_open()) {
        return 0;
    }
    int size;
    input >> size;
    Graphm* newGraph = new Graphm(size);
    std::string temp;
    while (std::getline(input, temp)) {
        std::istringstream sstream (temp);
        int v1, v2, wt;
        sstream >> v1 >> v2 >> wt;
        newGraph->setEdge(v1, v2, wt);
    }
    input.close();
    return newGraph;
}

bool writeGraph(Graph* oldGraph, std::string filename) {

    std::ofstream output (filename.c_str());
    if (!output.is_open()) {
        return false;
    }
    int size = oldGraph->vertices();
    output << size << '\n';
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (oldGraph->isEdge(i,j)) {
                output << i << ' ' << j << ' ' << oldGraph->weight(i,j) << '\n';
            }
        }
    }
    output.close();
    return true;
}
