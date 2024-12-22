#include <cstdint>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#include "directed_graph.h"
#include "disjoint_set.h"

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
    num_scc = cnt;
    //printf("Found %d SCCs, %.2f vertices each in average\n", cnt, (double)num_vertices/cnt);
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
    if(edge_sorted)
    {
        return;
    }
    sort(edges.begin(), edges.end(), [](edge_t* a, edge_t* b) -> bool
    {
        return a->weight > b->weight;
    });
}

bool DirectedGraph::checkCycleSCC(v_idx_t origin, v_idx_t curr) 
{
    if(curr == origin)
    {
        return true;
    }
    if(visited[curr])
    {
        return false;
    }
    visited[curr] = true;
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

DirectedGraph::DirectedGraph(uint16_t num_v): num_vertices(num_v), num_edges(0), used_edges(0), edge_sorted(false)
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
    used_edges = cnt;
    printProgress((double)used_edges/num_edges*100);;
    //printf("Used %d edges between SCCs (%.2f percents)\n", cnt, (double)cnt/num_edges*100);
}

void DirectedGraph::useMSTEdges()
{
    sortEdges();
    DisjointSet ds(num_vertices);
    uint16_t cnt = 0;
    for (auto &e: edges)
    {
        if (ds.find(e->from) != ds.find(e->to))
        {
            e->used = true;
            ds.union_set(e->from, e->to);
            cnt++;
        }
    }
    used_edges += cnt;
    printProgress((double)used_edges/num_edges*100);
    //printf("Used %d edges in MST (%.2f percents)\n", cnt, (double)cnt/num_edges*100);
}

void DirectedGraph::greedyUseEdges()
{
    visited.resize(num_vertices, false);
    sortEdges();
    uint16_t cnt = 0;
    for (auto &e: edges)
    {
        ++cnt;
        if (!e->used)
        {
            visited.assign(num_vertices, false);
            if (!checkCycleSCC(e->from, e->to))
            {
                used_edges++;
                e->used = true;
                printProgress((double)cnt/num_edges*100);
            }
        }
    }
}

const vector<edge_t*>& DirectedGraph::getEdges() const
{
    return edges;
}

void DirectedGraph::printProgress(double percentage) const
{
    //printf("\rProgress: %.2f%%", percentage);
    if(percentage == 100)
    {
        //printf("\n");
    }
}

uint16_t DirectedGraph::getNumSCC() const
{
    return num_scc;
}