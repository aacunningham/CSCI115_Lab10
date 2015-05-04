/*
 * ParPtrTree.h
 *
 *  Created on: Apr 27, 2015
 *      Author: aaronc
 */

#ifndef PARPTRTREE_H_
#define PARPTRTREE_H_

class ParPtrTree {
private:
    int* array;
    int* weight;
    int size;
    int FIND(int) const;
public:
    ParPtrTree(int);
    ~ParPtrTree();
    void UNION(int, int);
    bool DIFFER(int, int);
};



#endif /* PARPTRTREE_H_ */
