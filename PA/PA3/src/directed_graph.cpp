#include "directed_graph.h"
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

void DirectedGraph::DFS_Visit(uint16_t u, uint32_t &time)
{
    vertices[u].discover = time++;
    for(int i=0; i<vertex_size; i++)
    {
        if(wei_m[u][i].weight != N_CONNECT && vertices[i].discover == UINT32_MAX)
        {
            DFS_Visit(i, time);
        }
    }
    vertices[u].finish = time++;
}

void DirectedGraph::DFS_setSCC(uint16_t parent, uint16_t root)
{
    vertices[parent].scc_root = root;
    for(int i=0; i<vertex_size; i++)
    {
        if(wei_m[parent][i].weight != N_CONNECT && vertices[i].scc_root == UINT16_MAX)
        {
            DFS_setSCC(i, root);
        }
    }
}

DirectedGraph::DirectedGraph(uint16_t v_size): vertex_size(v_size), edge_size(0)
{
    vertices.resize(v_size);
    wei_m.resize(v_size);
    for(int i=0; i<v_size; i++)
    {
        wei_m[i].resize(v_size, {0, 0, N_CONNECT});
    }
}

DirectedGraph::DirectedGraph(uint16_t v_size, uint32_t edge_num, edge *_edges): vertex_size(v_size), edge_size(0)
{
    vertices.resize(v_size);
    wei_m.resize(v_size);
    for(int i=0; i<v_size; i++)
    {
        wei_m[i].resize(v_size, {0, 0, N_CONNECT});
    }

    for(int i=0; i<edge_num; i++)
    {
        addEdge(_edges[i]);
    }
}

DirectedGraph::~DirectedGraph()
{
}

/*
DirectedGraph &DirectedGraph::transpose()
{
    DirectedGraph ret = DirectedGraph(vertex_size);
    for(int i=0; i<edge_size; i++)
    {
        ret.addEdge(edges[i].to, edges[i].from, edges[i].weight);
    }
    return ret;
}
*/

void DirectedGraph::addEdge(uint16_t from, uint16_t to, int8_t w)
{
    wei_m[from][to].weight = w;
    edges.push_back({{from, UINT32_MAX, UINT32_MAX, UINT16_MAX}, {to, UINT32_MAX, UINT32_MAX, UINT16_MAX}, w});
    edge_size++;
}

void DirectedGraph::addEdge(edge _edge)
{
    edges.push_back(_edge);
    wei_m[_edge.from.id][_edge.to.id] = _edge;
    edge_size++;
}

void DirectedGraph::sortEdges()
{
    sort(edges.begin(), edges.end(), [](const edge &a, const edge &b) -> bool
    {
        return a.weight > b.weight;
    });
}

void DirectedGraph::sortVertices()
{
    sort(vertices.begin(), vertices.end(), [](const vertex &a, const vertex &b) -> bool
    {
        return a.finish > b.finish;
    });
}

void DirectedGraph::DFS()
{
    uint32_t time = 0;
    for(int i=0; i<vertex_size; i++)
    {
        if(vertices[i].discover == UINT32_MAX)
        {
            DFS_Visit(i, time);
        }
    }
}

void DirectedGraph::DFS_Transpose()
{
    sortVertices();
    for (int i = 0; i < vertex_size; i++)
    {
        if(vertices[i].scc_root == UINT16_MAX)
        {
            DFS_setSCC(vertices[i].id, vertices[i].id);
        }
    }
    
}

void DirectedGraph::useEdgeBetweenSCC()
{
    for(int i=0; i<edge_size; i++)
    {
        if(vertices[edges[i].from.id].scc_root != vertices[edges[i].to.id].scc_root)
        {
            edges[i].used = true;
        }
    }
}

void DirectedGraph::greedyUseEdge()
{
    for(int i=0; i<edge_size; i++)
    {
        if(!DFS_SCC_detectCycle(edges[i].from, edges[i].to))
        {
            edges[i].used = true;
        }
    }
}

edge DirectedGraph::getEdge(uint32_t idx) const
{
    return edges[idx];
}

bool DirectedGraph::DFS_SCC_detectCycle(vertex source, vertex curr) const
{
    if(wei_m[curr.id][source.id].weight != N_CONNECT)
    {
        return true;
    }
    for(int i=0; i<vertex_size; i++)
    {
        if(wei_m[curr.id][i].used && wei_m[curr.id][i].weight != N_CONNECT && vertices[i].scc_root == curr.scc_root)
        {
            if(DFS_SCC_detectCycle(source, wei_m[curr.id][i].to))
            {
                return true;
            }
        }
    }
    return false;
}

uint32_t DirectedGraph::getEdgeSize() const
{
    return edge_size;
}

uint16_t DirectedGraph::getVertexSize() const
{
    return vertex_size;
}

void DirectedGraph::print() const
{
    if(wei_m.size() == 0)
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
            if(wei_m[i][j].weight != N_CONNECT)
                printf("%hd\t|", wei_m[i][j]);
            else
                printf("  \t|");
        }
        printf("\n");
    }
}
