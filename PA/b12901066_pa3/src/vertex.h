#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <vector>
#include <cstdlib>
#define INF 2147483647
#define NINF -2147483646

enum colors {
    WHITE,
    GRAY,
    BLACK
};

struct vertex {
    int index;
    int d = 0; // degree
    vertex* p = NULL;
    colors color = WHITE;
    int nowCheck = 0; 
    // candy variable for saving the status of checking edges

    int key = INF;
    bool used = false;
    int heapInd = 0;
};

#endif // _VERTEX_H_