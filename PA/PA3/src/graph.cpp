#include "graph.h"
#include <cstdint>
#include <cstring>
#include <cstdio>

bool Graph::alloc_wei()
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

Graph::Graph(uint16_t v_size): vertex_size(v_size)
{
    alloc_wei();
}

Graph::Graph(uint16_t v_size, uint32_t edge_num, edge *_edges)
{
    alloc_wei();
    for(int i=0; i<edge_num; i++)
    {
        addEdge(_edges[i]);
    }
}

Graph::~Graph()
{
    if(wei_m != NULL)
    {
        delete [](wei_m[0]);
        delete []wei_m;
    }
}

void Graph::addEdge(uint16_t from, uint16_t to, int8_t w)
{
    wei_m[from][to] = w;
}

void Graph::addEdge(edge _edge)
{
    addEdge(_edge.from, _edge.to, _edge.weight);
}

void Graph::print() const
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
