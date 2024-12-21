#include <cstdint>
#include <vector>

#include "disjoint_set.h"

using namespace std;


void DisjointSet::link(uint16_t x, uint16_t y)
{
    if(rank[x] > rank[y])
    {
        parent[y] = x;
    }
    else
    {
        parent[x] = y;
        if(rank[x] == rank[y])
        {
            rank[y]++;
        }
    }
}

DisjointSet::DisjointSet(uint16_t v_size)
{
    parent.resize(v_size);
    rank.resize(v_size);
    for(int i=0; i<v_size; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

DisjointSet::~DisjointSet()
{
}

uint16_t DisjointSet::find(uint16_t x)
{
    if(x != parent[x])
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void DisjointSet::union_set(uint16_t x, uint16_t y)
{
    link(find(x), find(y));
}
