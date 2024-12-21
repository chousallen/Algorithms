#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <cstdint>

#define N_CONNECT INT8_MAX

struct vertex
{
    uint16_t id=0;
    uint32_t discover=UINT32_MAX;
    uint32_t finish=UINT32_MAX;
    uint16_t scc_root=UINT16_MAX;
};

struct edge
{
    vertex from;
    vertex to;
    int8_t weight;
    bool used=false;
};

class DirectedGraph
{
    private: 
        uint16_t vertex_size;
        uint32_t edge_size;
        vector<vertex> vertices;
        vector<edge> edges;
        vector<vector<edge>> wei_m;
        void DFS_Visit(uint16_t u, uint32_t &time);
        void DFS_setSCC(uint16_t parent, uint16_t root);

    public: 
        //Graph();
        DirectedGraph(uint16_t v_size);
        DirectedGraph(uint16_t v_size, uint32_t edge_num, edge *_edges);
        ~DirectedGraph();
        //DirectedGraph &transpose();
        void addEdge(uint16_t from, uint16_t to, int8_t w = 1);
        void addEdge(edge _edge);
        void sortEdges();
        void sortVertices();
        void DFS();
        void DFS_Transpose();
        void useEdgeBetweenSCC();
        void greedyUseEdge();
        bool DFS_SCC_detectCycle(vertex source, vertex curr) const;
        edge getEdge(uint32_t idx) const;
        uint32_t getEdgeSize() const;
        uint16_t getVertexSize() const;
        void print() const;
};


#endif //graph.h
