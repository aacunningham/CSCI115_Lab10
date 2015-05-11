/*
 * graphs.cpp
 *
 *  Created on: May 4, 2015
 *      Author: aaronc
 */

#include <iostream>
#include <string>
#include <sstream>
#include "Graphm.h"
#include "heap.tpp"
#include "ParPtrTree.h"

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

void Kruskal(Graph* g, Graph* m);
int components(Graph* g, ParPtrTree* t);
Graph* extract(Graph* g, int v);



//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    std::string input;
    std::cout << ">> ";
    while (std::getline(std::cin, input)) {
        std::stringstream ss(input);
        std::string word;
        while (ss >> word) {
            int temp;
            ss >> temp;
            if (temp < 0 || temp >= registers) {
                std::cout << "No such graph.\n\n";
            }

            else if (word == "input") {
                std::string filename;
                ss >> filename;
                delete graph[temp];
                graph[temp] = readGraph(filename);
                if (graph[temp] == 0) {
                    std::cout << "Input failed.\n\n";
                    continue;
                }
                delete comps[temp];
                numcomps[temp] = components(graph[temp], comps[temp]);
                std::cout << "Input successful.\n\n";
            }

            else if (word == "output") {
                std::string filename;
                ss >> filename;
                if (graph[temp] == 0) {
                    std::cout << "No such graph.\n\n";
                    continue;
                }
                if (!writeGraph(graph[temp], filename)) {
                    std::cout << "Output failed.\n\n";
                    continue;
                }
                std::cout << "Output successful.\n\n";
            }

            else if (word == "info") {
                if (graph[temp] != 0) {
                    std::cout << "Graph in register " << temp << " has "
                              << graph[temp]->vertices() << " vertices, "
                              << graph[temp]->edges() << " edges, and "
                              << numcomps[temp] << " components.\n\n";
                } else {
                    std::cout << "No such graph.\n\n";
                }
            }

            else if (word == "kruskal") {
                if (numcomps[temp] != 1) {
                    std::cout << "Graph is not connected.\n\n";
                    continue;
                }
                int temp2;
                ss >> temp2;
                if (temp2 < 0 || temp2 >= registers) {
                    std::cout << "No such graph.\n\n";
                    continue;
                }
                delete graph[temp2];
                Kruskal(graph[temp], graph[temp2]);
                numcomps[temp2] = 1;
            }

            else if (word == "extract") {
                int temp2, temp3;
                ss >> temp2 >> temp3;
                if (temp3 < 0 || temp3 >= registers) {
                    std::cout << "No such graph.\n\n";
                    continue;
                }
                if (temp2 < 0 || temp2 > graph[temp]->vertices()) {
                    std::cout << "No such vertex.\n\n";
                    continue;
                }
                delete graph[temp3];
                graph[temp3] = extract(graph[temp], temp2);
                numcomps[temp3] = 1;
            }

            else if (word == "print") {
                for (int i = 0; i < graph[temp]->vertices(); ++i) {
                    for (int w = graph[temp]->next(i, i); w < graph[temp]->vertices(); w = graph[temp]->next(i, w)) {
                        std::cout << i << ' ' << w << ' ' << graph[temp]->weight(i, w) << '\n';
                    }
                }
                std::cout << '\n';
            }

            else if (word == "exit") {
                break;
            }

            else {
                std::cout << "'" << word << "' is not a command.\n\n";
            }
        }
        if (word == "exit") {
            std::cout << "Exiting...\n";
            break;
        }
        std::cout << ">> ";
    }

    for (int i = 0; i < registers; ++i) {
        delete graph[i];
        delete comps[i];
    }
    return 0;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


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
    m = new Graphm(g->vertices());
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
    int numbercomps = g->vertices();
    for (int i = 0; i < g->vertices(); ++i) {
        for (int w = g->next(i, i); w < g->vertices(); w = g->next(i, w)) {
            if (t->DIFFER(i, w)) {
                t->UNION(i, w);
                --numbercomps;
            }
        }
    }
    return numbercomps;
}

Graph* extract(Graph* g, int v) {
    Graph* m = new Graphm(g->vertices());
    for (int i = 0; i < g->vertices(); ++i) {
        g->setMark(i, 0);
    }
    int list[g->edges()];
    int listbottom, listtop = 0;
    list[listtop++] = v;
    while (listbottom != listtop) {
        int current = list[listbottom];
        for (int i = g->first(current); i < g->vertices(); i = g->next(current, i)) {
            if (g->getMark(i) != 0) {
                continue;
            }
            m->setEdge(current, i, g->weight(current, i));
            list[listtop++] = i;
        }
        g->setMark(current, 1);
        ++listbottom;
    }
    return m;
}
