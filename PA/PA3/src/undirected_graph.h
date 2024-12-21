#ifndef _UNDIRECTED_GRAPH_H_
#define _UNDIRECTED_GRAPH_H_

#include <cstdint>
#include <vector>
#include <tuple>

using namespace std;

class UndirectedGraph
{
    private: 
        uint16_t vertex_size;
        uint32_t edge_size;
        vector<tuple<uint16_t, uint16_t, int8_t>> edges;

    public:
        UndirectedGraph(uint16_t v_size);
        UndirectedGraph(uint16_t v_size, uint32_t edge_num, const vector<tuple<uint16_t, uint16_t, int8_t>> &_edges);
        ~UndirectedGraph();
        void addEdge(uint16_t from, uint16_t to, int8_t w = 1);
        void addEdge(const tuple<uint16_t, uint16_t, int8_t> &_edge);
        void sortEdges();
        const tuple<uint16_t, uint16_t, int8_t>& getEdge(uint32_t idx) const;
        uint16_t getVertexSize() const;
        uint32_t getEdgeSize() const;
        void print() const;
};

#endif //undirected_graph.h