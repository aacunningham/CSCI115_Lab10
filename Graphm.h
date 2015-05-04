/*
 * Graphm.h
 *
 *  Created on: Apr 27, 2015
 *      Author: aaronc
 */

#ifndef GRAPHM_H_
#define GRAPHM_H_

#include "Graph.h"
#include <string>


class Graphm : public Graph {
private:
    int numVertex, numEdge;
    int* matrix;
    int* mark;

public:
    Graphm(int numVert);
    ~Graphm();

    void Init(int n);

    int vertices();
    int edges();

    int first(int v);
    int next(int v, int w);

    void setEdge(int v1, int v2, int wt);
    void delEdge(int v1, int v2);
    bool isEdge(int v1, int v2);

    int weight(int v1, int v2);

    int getMark(int v);
    void setMark(int v, int val);


};


Graph* readGraph(std::string filename);
bool writeGraph(Graph* oldGraph, std::string filename);

#endif /* GRAPHM_H_ */
