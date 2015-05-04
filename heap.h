/*
 * heap.cpp
 *
 *  Created on: May 3, 2015
 *      Author: aaronc
 */

#include <exception>


class max {
public:
    template <typename E>
    static bool prior (E a, E b) {
        return a > b;
    }
};

class min {
public:
    template <typename E>
    static bool prior (E a, E b) {
        return a < b;
    }
};

class heapException: public std::exception {
public:
    const char* string;
    heapException (const char* c) {
        string = c;
    }
    virtual const char* what() const throw() {
        return string;
    }
};


template <typename E>
void swap (E* arr, int a, int b) {
    E temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

template <typename E, typename Comp>
class Heap {
private:
    E* heap;
    int maxsize;
    int n;
    void siftdown(int pos) {
        while (!isLeaf(pos)) {
            int j = leftchild(pos);
            int rc = rightchild(pos);
            if ((rc < n) && Comp::prior(heap[rc], heap[j])) {
                j = rc;
            }
            if (Comp::prior(heap[pos], heap[j])) {
                return;
            }
            swap(heap, pos, j);
            pos = j;
        }
    }

public:
    Heap(E* h, int num, int max) :
        heap (h), maxsize (max), n (num) {
        buildHeap();
    }
    int size() const { return n; }
    bool isLeaf(int pos) const {
        return (pos >= n/2) && (pos < n);
    }
    int leftchild(int pos) const {
        return 2 * pos + 1;
    }
    int rightchild(int pos) const {
        return 2 * pos + 2;
    }
    int parent(int pos) const {
        return (pos - 1) / 2;
    }
    void buildHeap() {
        for (int i = n / 2 - 1; i >= 0; --i) {
            siftdown(i);
        }
    }

    void insert(const E& it) {
        if (n >= maxsize) {
            const char* c = "Heap is full";
            throw heapException(c);
        }
        int curr = n++;
        heap[curr] = it;
        while ((curr != 0) && (Comp::prior(heap[curr], heap[parent(curr)]))) {
            swap(heap, curr, parent(curr));
            curr = parent(curr);
        }
    }

    E removefirst() {
        if (n < 1) {
            const char* c = "Heap is empty";
            throw heapException(c);
        }
        swap(heap, 0, --n);
        if (n != 0) {
            siftdown(0);
        }
        return heap[n];
    }

    E remove(int pos) {
        if (!((pos >= 0) && (pos < n))) {
            const char* c = "Element does not exist";
            throw heapException(c);
        }
        if (pos == (n - 1)) { --n; }
        else {
            swap(heap, pos, --n);
            while ((pos != 0) && (Comp::prior(heap[pos], heap[parent(pos)]))) {
                swap(heap, pos, parent(pos));
                pos = parent(pos);
            }
            if (n != 0) { siftdown(pos); }
        }
        return heap[n];
    }
};



