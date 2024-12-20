#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <cstdint>

#define N_CONNECT INT8_MAX

struct edge
{
    uint16_t from;
    uint16_t to;
    int8_t weight;
};

class Graph
{
    private: 
        uint16_t vertex_size;
        //uint16_t **adj_m;
        int8_t **wei_m;
        bool alloc_wei();

    public: 
        //Graph();
        Graph(uint16_t v_size);
        Graph(uint16_t v_size, uint32_t edge_num, edge *_edges);
        ~Graph();
        void addEdge(uint16_t from, uint16_t to, int8_t w = 1);
        void addEdge(edge _edge);
        void print() const;
};


#endif //graph.h
