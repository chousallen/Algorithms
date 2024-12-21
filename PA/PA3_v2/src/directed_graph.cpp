#include <cstdint>
#include <cstdio>

#include <vector>
#include <algorithm>

using namespace std;

#include "directed_graph.h"

vector<uint16_t> DirectedGraph::DFS() const
{
    vector<uint16_t> discover_time(num_vertices, NIL), finish_time(num_vertices, NIL);
    uint16_t time = 0;
    for (v_idx_t i = 0; i < num_vertices; i++)
    {
        if (discover_time[i] == NIL)
        {
            DFS_Visit(i, discover_time, finish_time, time);
        }
    }
    return finish_time;
}

void DirectedGraph::DFS_Visit(v_idx_t v, vector<uint16_t> &discover_time, vector<uint16_t> &finish_time, uint16_t &time) const
{
    discover_time[v] = time++;
    for (v_idx_t i = 0; i < num_vertices; i++)
    {
        if (wei_m[v][i].weight != NC && discover_time[i] == NIL)
        {
            DFS_Visit(i, discover_time, finish_time, time);
        }
    }
    finish_time[v] = time++;
}

void DirectedGraph::DFS_Transpose(vector<v_idx_t> vertices_inorder)
{
    uint16_t cnt = 0;
    for(auto &s: vertices_inorder)
    {
        if (scc[s] == NIL)
        {
            cnt++;
            setSCC(s, s);
        }
    }
    printf("Found %d SCCs, %f vertices each in average\n", cnt, (double)num_vertices/cnt);
}

void DirectedGraph::setSCC(v_idx_t curr, v_idx_t scc_root)
{
    scc[curr] = scc_root;
    for (v_idx_t i = 0; i < num_vertices; i++)
    {
        if (wei_m[i][curr].weight != NC && scc[i] == NIL)
        {
            setSCC(i, scc_root);
        }
    }
}

void DirectedGraph::sortEdges()
{
    sort(edges.begin(), edges.end(), [](edge_t* a, edge_t* b) -> bool
    {
        return a->weight > b->weight;
    });
}

bool DirectedGraph::checkCycleSCC(v_idx_t origin, v_idx_t curr) const
{
    if(curr == origin)
    {
        return true;
    }
    for (v_idx_t i = 0; i < num_vertices; i++)
    {
        if (wei_m[curr][i].weight != NC && wei_m[curr][i].used && scc[i] == scc[origin])
        {
            if (checkCycleSCC(origin, i))
            {
                return true;
            }
        }
    }
    return false;
}

DirectedGraph::DirectedGraph(uint16_t num_v): num_vertices(num_v), num_edges(0)
{
    scc.resize(num_v, NIL);
    wei_m.resize(num_v);
    for (v_idx_t i = 0; i < num_v; i++)
    {
        wei_m[i].resize(num_v);
        for (v_idx_t j = 0; j < num_v; j++)
        {
            wei_m[i][j] = {i, j, NC, false};
        }
        
    }    
}

DirectedGraph::~DirectedGraph()
{
    // Nothing to do
}

void DirectedGraph::setEdges(vector<edge_t> _edges)
{
    num_edges = _edges.size();
    edges.reserve(num_edges);
    for (auto &e: _edges)
    {
        wei_m[e.from][e.to].weight = e.weight;
        edges.emplace_back(&(wei_m[e.from][e.to]));
    }
}

void DirectedGraph::computeSCC()
{
    vector<uint16_t> finish_time = DFS();
    vector<v_idx_t> vertices_inorder(num_vertices);
    v_idx_t idx = 0;
    for (auto &v: vertices_inorder)
    {
        v = idx++;
    }
    sort(vertices_inorder.begin(), vertices_inorder.end(), [&finish_time](v_idx_t a, v_idx_t b) -> bool
    {
        return finish_time[a] > finish_time[b];
    });
    DFS_Transpose(vertices_inorder);
}

void DirectedGraph::useEdgesBetweenSCC()
{
    uint16_t cnt = 0;
    for (auto &e: edges)
    {
        if (scc[e->from] != scc[e->to])
        {
            e->used = true;
            cnt++;
        }
    }
    printf("Used %d edges between SCCs (%f%)\n", cnt, (double)cnt/num_edges*100);
}

void DirectedGraph::greedyUseEdges()
{
    sortEdges();
    for (auto &e: edges)
    {
        if (!e->used)
        {
            if (!checkCycleSCC(e->from, e->to))
            {
                e->used = true;
            }
        }
    }
}

const vector<edge_t*>& DirectedGraph::getEdges() const
{
    return edges;
}