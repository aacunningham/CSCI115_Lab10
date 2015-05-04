/*
 * ParPtrTree.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: aaronc
 */

#include "ParPtrTree.h"


ParPtrTree::ParPtrTree(int size) :
    array (new int[size]),
    weight (new int[size]),
    size (size) {
    for (int i = 0; i < size; ++i) {
        array[i] = -1;
        weight[i] = 1;
    }
}

ParPtrTree::~ParPtrTree() {
    delete[] array;
    delete[] weight;
}

int ParPtrTree::FIND(int curr) const {
    if (array[curr] == -1) return curr;
    array[curr] = FIND(array[curr]);
    return array[curr];
}

void ParPtrTree::UNION(int a, int b) {
    int roota = FIND(a);
    int rootb = FIND(b);
    if (roota != rootb) {
        if (weight[roota] >= weight[rootb]) {
            array[rootb] = roota;
            weight[roota] += weight[rootb];
        } else {
            array[roota] = rootb;
            weight[rootb] += weight[roota];
        }
    }
}

bool ParPtrTree::DIFFER(int a, int b) {
    return FIND(a) != FIND(b);
}
