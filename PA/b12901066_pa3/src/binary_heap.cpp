#ifndef _BINARY_HEAP_CPP_
#define _BINARY_HEAP_CPP_

#include "binary_heap.h"
#include <iostream>
using namespace std;
#define LEFT_CHILD(i) (2 * (i) + 1)
#define RIGHT_CHILD(i) (2 * (i) + 2)
#define PARENT(i) (((i) - 1) / 2)
#define ROOT 0

// parent: i, left: 2 * i + 1, right: 2 * i + 2

binary_heap::binary_heap() {

}

binary_heap::~binary_heap() {

}

vertex* binary_heap::extract_min() {
    if(size == 0) return NULL;
    vertex* result = heap[0];
    result->used = true;
    heap[0] = heap[size - 1];
    heap[0]->heapInd = 0;
    heap[size - 1] = NULL;
    size--;
    if(size > 0) min_heapify(0);
    return result;
}

void binary_heap::decrease_key(int index, int key) {
    if(heap[index]->key < key) return;

    heap[index]->key = key;
    swim(index);
}

void binary_heap::insert(vertex* vertex) {
    heap[size] = vertex;
    heap[size]->used = false;
    heap[size]->heapInd = size;
    size++;
    swim(size - 1);
}

void binary_heap::min_heapify(int index) {
    int smallest = index;
    if(RIGHT_CHILD(index) < size && heap[RIGHT_CHILD(index)]->key < heap[smallest]->key) {
        smallest = RIGHT_CHILD(index);
    }
    if(LEFT_CHILD(index) < size && heap[LEFT_CHILD(index)]->key < heap[smallest]->key) {
        smallest = LEFT_CHILD(index);
    }
    if(smallest != index) {
        vertex* temp = heap[index];
        heap[index] = heap[smallest];
        heap[index]->heapInd = index;
        heap[smallest] = temp;
        heap[smallest]->heapInd = smallest;
        min_heapify(smallest);
    }
}

void binary_heap::build_min_heap() {
    if(size <= 1) return;

    for(int i = size / 2 - 1; i >= 0; i--) {
        min_heapify(i);
    }
}

void binary_heap::swim(int index) {
    if(index == ROOT) return;

    if(heap[PARENT(index)]->key > heap[index]->key) {
        vertex* temp = heap[PARENT(index)];
        heap[PARENT(index)] = heap[index];
        heap[PARENT(index)]->heapInd = PARENT(index);
        heap[index] = temp;
        heap[index]->heapInd = index;
        swim(PARENT(index));
    }
    else return;
}

#endif // _BINARY_HEAP_CPP_