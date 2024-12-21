#ifndef _DISJOINT_SET_H_
#define _DISJOINT_SET_H_

#include <cstdint>
#include <vector>
using namespace std;

class DisjointSet
{
private:
    vector<uint16_t> parent; // parent of each node
    vector<uint16_t> rank; // rank of the component
    void link(uint16_t x, uint16_t y);
public:
    DisjointSet(uint16_t v_size);
    ~DisjointSet();
    uint16_t find(uint16_t x);
    void union_set(uint16_t x, uint16_t y);
};

#endif //disjoint_set.h