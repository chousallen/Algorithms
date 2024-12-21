#ifndef _DIRECTED_GRAPH_H_
#define _DIRECTED_GRAPH_H_

#include <cstdint>

#include <vector>

using namespace std;

typedef uint16_t v_idx_t;

#define NC INT8_MAX
#define NIL UINT16_MAX

struct edge_t
{
    v_idx_t from;
    v_idx_t to;
    int8_t weight;
    bool used;
};

class DirectedGraph
{
    private:
        // Parameters
        uint16_t num_vertices, num_edges, used_edges;
        bool edge_sorted;

        // Arrays
        vector<edge_t*> edges;
        vector<v_idx_t> scc;
        vector<vector<edge_t>> wei_m;

        // Functions
        vector<uint16_t> DFS() const;
        void DFS_Visit(v_idx_t, vector<uint16_t> &discover_time, vector<uint16_t> &finish_time, uint16_t &time) const;
        void DFS_Transpose(vector<v_idx_t> vertices_inorder);
        void setSCC(v_idx_t curr, v_idx_t scc_root);
        void sortEdges();
        bool checkCycleSCC(v_idx_t origin, v_idx_t curr) const;

    public:
        DirectedGraph(uint16_t num_v);
        ~DirectedGraph();
        void setEdges(vector<edge_t> edges);
        void computeSCC();
        void useEdgesBetweenSCC();
        void useMSTEdges();
        void greedyUseEdges();
        const vector<edge_t*>& getEdges() const;
        void printProgress(double p) const;
};

#endif // _DIRECTED_GRAPH_H_