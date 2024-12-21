#include <cstdint>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>

#include "undirected_graph.h"

using namespace std;

UndirectedGraph::UndirectedGraph(uint16_t v_size): vertex_size(v_size), edge_size(0)
{
}

UndirectedGraph::UndirectedGraph(uint16_t v_size, uint32_t edge_num, const vector<tuple<uint16_t, uint16_t, int8_t>> &_edges): vertex_size(v_size), edge_size(edge_num), edges(_edges)
{
}

UndirectedGraph::~UndirectedGraph()
{
}

void UndirectedGraph::addEdge(uint16_t from, uint16_t to, int8_t w)
{
    edges.emplace_back(from, to, w);
    edge_size++;
}

void UndirectedGraph::addEdge(const tuple<uint16_t, uint16_t, int8_t> &_edge)
{
    edges.emplace_back(_edge);
    edge_size++;
}

void UndirectedGraph::sortEdges()
{
    sort(edges.begin(), edges.end(), [](const tuple<uint16_t, uint16_t, int8_t> &a, const tuple<uint16_t, uint16_t, int8_t> &b) -> bool
    {
        return get<2>(a) > get<2>(b);
    });
}

const tuple<uint16_t, uint16_t, int8_t>& UndirectedGraph::getEdge(uint32_t idx) const
{
    return edges[idx];
}

uint16_t UndirectedGraph::getVertexSize() const
{
    return vertex_size;
}

uint32_t UndirectedGraph::getEdgeSize() const
{
    return edge_size;
}

void UndirectedGraph::print() const
{
    printf("vertex size: %d\n", vertex_size);
    printf("edge size: %d\n", edge_size);
    for(auto &e: edges)
    {
        printf("%d %d %d\n", get<0>(e), get<1>(e), get<2>(e));
    }
}