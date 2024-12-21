#include "directed_graph.h"
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

void DirectedGraph::DFS_Visit(uint16_t u, uint32_t &time)
{
    //printf("discover %d\n", u);
    vertices[u].discover = time++;
    for(int i=0; i<vertex_size; i++)
    {
        if(wei_m[u][i].weight != N_CONNECT && vertices[i].discover == UINT32_MAX)
        {
            DFS_Visit(i, time);
        }
    }
    //printf("finish %d\n", u);
    vertices[u].finish = time++;
}

void DirectedGraph::DFS_setSCC(vertex &curr, const vertex &root)
{
    printf("set %d's scc %d\n", curr.id, root.id);
    vertices[curr.id].scc_root = root.id;
    for(int i=0; i<vertex_size; i++)
    {
        if(wei_m[i][curr.id].weight != N_CONNECT && vertices[i].scc_root == UINT16_MAX)
        {
            DFS_setSCC(vertices[i], root);
        }
    }
}

DirectedGraph::DirectedGraph(uint16_t v_size): vertex_size(v_size), edge_size(0)
{
    vertices.resize(v_size);
    int i=0;
    for (auto &v : vertices)
    {
        v.id = i++;
    }
    
    wei_m.resize(v_size);
    for(uint16_t i=0; i<v_size; i++)
    {
        wei_m[i].resize(v_size);
        for(uint16_t j=0; j<v_size; j++)
        {
            wei_m[i][j] = {i, j, N_CONNECT};
        }
    }
}

DirectedGraph::DirectedGraph(uint16_t v_size, uint32_t edge_num, vector<edge> _edges): vertex_size(v_size), edge_size(0)
{
    vertices.resize(v_size);
    int i=0;
    for (auto &v : vertices)
    {
        v.id = i++;
    }
    wei_m.resize(v_size);
    for(uint16_t i=0; i<v_size; i++)
    {
        wei_m[i].resize(v_size);
        for(uint16_t j=0; j<v_size; j++)
        {
            wei_m[i][j] = {i, j, N_CONNECT};
        }
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
    edges.push_back({from, to, w});
    edge_size++;
}

void DirectedGraph::addEdge(edge _edge)
{
    edges.push_back(_edge);
    wei_m[_edge.from_idx][_edge.to_idx] = _edge;
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
            printf("find scc with root %d\n", vertices[i].id);
            vertices[i].scc_root = vertices[i].id;
            DFS_setSCC(vertices[i], vertices[i]);
        }
    }
    
}

void DirectedGraph::useEdgeBetweenSCC()
{
    for(int i=0; i<edge_size; i++)
    {
        if(vertices[edges[i].from_idx].scc_root != vertices[edges[i].to_idx].scc_root)
        {
            edges[i].used = true;
        }
    }
}

void DirectedGraph::greedyUseEdge()
{
    for(int i=0; i<edge_size; i++)
    {
        if(!DFS_SCC_detectCycle(vertices[edges[i].from_idx], vertices[edges[i].to_idx]))
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
            if(DFS_SCC_detectCycle(source, vertices[wei_m[curr.id][i].to_idx]))
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

void DirectedGraph::printOriginal(ofstream &md_f) const
{
    md_f << "```mermaid\nstateDiagram\n";
    for (const auto &e : edges)
    {
        md_f << "    " << e.from_idx << " --> " << e.to_idx << " : " << static_cast<int>(e.weight) << "\n";
    }
    md_f << "```\n";
}

void DirectedGraph::print(ofstream &md_f) const
{
    md_f << "```mermaid\nstateDiagram\n";
    for (const auto &e : edges)
    {
        if (e.used)
        {
            md_f << "    " << e.from_idx << "/" << vertices[e.from_idx].scc_root << " --> " << e.to_idx << "/" << vertices[e.to_idx].scc_root << " : " << static_cast<int>(e.weight) << "\n";
        }
    }
    md_f << "```\n";
}

void DirectedGraph::printVertices() const
{
    for (const auto &v : vertices)
    {
        printf("id: %d, scc_root: %d\n", v.id, v.scc_root);
    }
}

void DirectedGraph::printEdges() const
{
    for(auto &i: wei_m)
    {
        for(auto &j: i)
        {
            printf("%d \t", int(j.weight));
        }
        printf("\n");
    }
}