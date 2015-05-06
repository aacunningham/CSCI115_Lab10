/*
 * graphs.cpp
 *
 *  Created on: May 4, 2015
 *      Author: aaronc
 */

#ifndef GRAPHS_CPP_
#define GRAPHS_CPP_

#include "Graph.h"
#include "ParPtrTree.h"
#include "heap.h"

const int registers = 10;

Graph* graph[registers];
ParPtrTree* comps[registers];
int numcomps[registers];

class KruskElem {
public:
    int from, to, distance;
    KruskElem() :
        from (-1), to (-1), distance (-1) {}
    KruskElem(int f, int t, int d) :
        from (f), to (t), distance (d) {}
    bool operator< (const KruskElem &right) {
        return (this->distance < right.distance);
    }
};

void Kruskal(Graph* g, Graph* m) {
    ParPtrTree a(g->vertices());
    KruskElem e[g->edges()];
    int i;
    int edgecount = 0;
    for (i = 0; i < g->vertices(); ++i) {
        for (int w = g->next(i, i); w < g->vertices(); w = g->next(i, w)) {
            e[edgecount].distance = g->weight(i, w);
            e[edgecount].from = i;
            e[edgecount++].to = w;
        }
    }
    Heap<KruskElem, comp> h(e, edgecount, edgecount);
    int numMST = g->vertices();
    for (i = 0; numMST > 1; ++i) {
        KruskElem temp;
        temp = h.removefirst();
        if (a.DIFFER(temp.from, temp.to)) {
            a.UNION(temp.from, temp.to);
            m->setEdge(temp.from, temp.to, temp.distance);
            --numMST;
        }
    }
}

int components(Graph* g, ParPtrTree* t) {
    t = new ParPtrTree(g->vertices());
    for (int i = 0; i < g->vertices(); ++i) {
        for (int w = g->next(i, i); w < g->vertices(); w = g->next(i, w)) {
            if (t->DIFFER(i, w)) {
                t->UNION(i, w);
            }
        }
    }
    return t->ROOTS();

}

#endif
