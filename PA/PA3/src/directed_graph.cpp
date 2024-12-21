#include "directed_graph.h"
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

bool DirectedGraph::alloc_wei()
{
    if(vertex_size <= 0)
        return false;
    int8_t *lin_wei_m = new int8_t[vertex_size * vertex_size];
    memset(lin_wei_m, N_CONNECT, sizeof(int8_t)*vertex_size*vertex_size);
    wei_m = new int8_t*[vertex_size];
    for(int i=0; i<vertex_size; i++)
    {
        wei_m[i] = lin_wei_m + vertex_size * i;
    }
    return true;
}

DirectedGraph::DirectedGraph(uint16_t v_size): vertex_size(v_size), edge_size(0)
{
    alloc_wei();
}

DirectedGraph::DirectedGraph(uint16_t v_size, uint32_t edge_num, edge *_edges): vertex_size(v_size), edge_size(edge_num)
{
    alloc_wei();
    for(int i=0; i<edge_num; i++)
    {
        addEdge(_edges[i]);
    }
}

DirectedGraph::~DirectedGraph()
{
    if(wei_m != NULL)
    {
        delete [](wei_m[0]);
        delete []wei_m;
    }
}

DirectedGraph &DirectedGraph::transpose()
{
    DirectedGraph ret = DirectedGraph(vertex_size);
    for(int i=0; i<edge_size; i++)
    {
        ret.addEdge(edges[i].to, edges[i].from, edges[i].weight);
    }
    return ret;
}

void DirectedGraph::addEdge(uint16_t from, uint16_t to, int8_t w)
{
    wei_m[from][to] = w;
    edges.push_back({from, to, w});
    edge_size++;
}

void DirectedGraph::addEdge(edge _edge)
{
    addEdge(_edge.from, _edge.to, _edge.weight);
}

void DirectedGraph::sortEdges()
{
    sort(edges, edges+edge_size, [](const edge &a, const edge &b) -> bool
    {
        return a.weight > b.weight;
    });
}

edge DirectedGraph::getEdge(uint32_t idx) const
{
    return edges[idx];
}

void DirectedGraph::print() const
{
    if(wei_m == NULL)
        return;
    printf("\t|");
    for(int i = 0; i < vertex_size; i++)
    {
        printf("%d\t|", i);
    }
    printf("\n");
    for(int i=0; i < vertex_size; i++)
    {
        printf("%d\t|", i);
        for(int j=0; j < vertex_size; j++)
        {
            if(wei_m[i][j] != N_CONNECT)
                printf("%hd\t|", wei_m[i][j]);
            else
                printf("  \t|");
        }
        printf("\n");
    }
}
