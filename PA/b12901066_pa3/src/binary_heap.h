#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

#include "vertex.h"
#include <cstdlib>

class binary_heap {
    public:
        binary_heap();
        ~binary_heap();
        vertex* extract_min();
        void decrease_key(int index, int key);
        void insert(vertex* vertex);
        int get_size() {return size;}

    private:
        vertex* heap[10000] = {};
        int size = 0;
        void min_heapify(int index);
        void build_min_heap();
        void swim(int index);
};

#endif // _BINARY_HEAP_H_