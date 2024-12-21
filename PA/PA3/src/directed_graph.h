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

class DirectedGraph
{
    private: 
        uint16_t vertex_size;
        uint32_t edge_size;
        vector<edge> edges;
        int8_t **wei_m;
        bool alloc_wei();

    public: 
        //Graph();
        DirectedGraph(uint16_t v_size);
        DirectedGraph(uint16_t v_size, uint32_t edge_num, edge *_edges);
        ~DirectedGraph();
        DirectedGraph &transpose();
        void addEdge(uint16_t from, uint16_t to, int8_t w = 1);
        void addEdge(edge _edge);
        void sortEdges();
        edge getEdge(uint32_t idx) const;
        void print() const;
};


#endif //graph.h
