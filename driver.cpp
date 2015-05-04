/*
 * main.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: aaronc
 */


#include <iostream>
#include "Graphm.h"
#include "ParPtrTree.h"
#include "heap.h"


int main(int argc, char **argv) {
    Graph* g = new Graphm(5);
    g->setEdge(0,1,4);
    g->setEdge(0,2,5);
    g->setEdge(0,4,5);
    g->setEdge(1,3,3);
    g->setEdge(3,2,4);

    std::cout << "Graph Tests\n";
    std::cout << "List of all edges: \n";
    for (int i = 0; i < g->vertices(); ++i) {
        for (int j = i + 1; j < g->vertices(); ++j) {
            if (g->isEdge(i, j)) {
                std::cout << i << '-' << j << ": " << g->weight(i,j) << '\n';
            }
        }
    }
    std::cout << "\nnext(1, 0): " << g->next(1,0);
    std::cout << "\nnext(0, 1): " << g->next(0,1);
    std::cout << "\nfirst(3): " << g->first(3);

    std::string saveFile = "Test.txt";
    if (writeGraph(g, saveFile)) {
        std::cout << "\n\nGraph Write Successful\n";
    }

    std::cout << "\nReading graph from " << saveFile << '\n';
    Graph* test = readGraph(saveFile);
    std::cout << "List of all edges: \n";
    for (int i = 0; i < test->vertices(); ++i) {
        for (int j = i + 1; j < test->vertices(); ++j) {
            if (test->isEdge(i, j)) {
                std::cout << i << '-' << j << ": " << test->weight(i,j) << '\n';
            }
        }
    }
    delete test;

    std::cout << "\n\nParPtrTree Tests\n";
    ParPtrTree j(5);
    j.UNION(0,1);
    j.UNION(1,2);
    j.UNION(2,3);
    std::cout << "differ(0,3): " << j.DIFFER(0,3) << "\ndiffer(0,4): " << j.DIFFER(0,4) << '\n';


    std::cout << "\n\nHeap Tests\n";
    int array[5];
    Heap<int, max> h(array, 0, 5);
    h.insert(1);
    h.insert(2);
    h.insert(3);
    h.insert(4);
    h.insert(5);

    std::cout << "remove(3): " << h.remove(3) << "\nremovefirst(): " << h.removefirst() << '\n';

    return 0;
}


