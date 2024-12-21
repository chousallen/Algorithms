#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <tuple>

#include "undirected_graph.h"
#include "directed_graph.h"
#include "disjoint_set.h"

using namespace std;

bool directed = false;
uint16_t v_size = 0;
uint32_t e_size = 0;

vector<tuple<uint16_t, uint16_t, int8_t>> read_edges(ifstream &input_f);
void directed_main(DirectedGraph &mygraph, ofstream &output_f);
void undirected_main(UndirectedGraph &mygraph, ofstream &output_f);

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("3 arguments expected, but %d got\n", argc);
        return EXIT_FAILURE;
    }
    ifstream input_f(argv[1]);
    ofstream output_f(argv[2], ofstream::trunc);
    
    vector<tuple<uint16_t, uint16_t, int8_t>> edges = read_edges(input_f);
    if(directed)
    {
        //DirectedGraph mygraph(v_size, e_size, edges.data());
        //mygraph.print();
    }
    else
    {
        UndirectedGraph mygraph(v_size, e_size, edges);
        undirected_main(mygraph, output_f);
    }

    output_f.close();
}


vector<tuple<uint16_t, uint16_t, int8_t>> read_edges(ifstream &input_f)
{
    vector<tuple<uint16_t, uint16_t, int8_t>> edges;
    char tmp;
    input_f >> tmp;
    switch(tmp)
    {
        case 'u':
            directed = false;
            break;
        case 'd':
            directed = true;
            break;
        default:
            printf("read direct error, %c got\n", tmp);
            break;
    }
    int weight = 0, tmp_int = 1;
    uint16_t from = 0, to = 0;
    input_f >> v_size >> e_size;

    for(uint32_t i=0; i<e_size; i++)
    {
        input_f >> from >> to >> weight;
        edges.emplace_back(from, to, weight);
    }
    input_f >> tmp_int;
    if(tmp_int != 0)
    {
        printf("expect ended by 0, but %hd got\n", (tmp_int));
    }
    input_f.close();
    return edges;
}

void undirected_main(UndirectedGraph &mygraph, ofstream &output_f)
{
    mygraph.sortEdges();
    DisjointSet ds(mygraph.getVertexSize());

    uint32_t edge_idx=0, edge_size = mygraph.getEdgeSize();
    int64_t total_cost = 0;
    tuple<uint16_t, uint16_t, int8_t> curr_edge;
    vector<tuple<uint16_t, uint16_t, int8_t>> rm_edges;
    for (edge_idx = 0; edge_idx < edge_size; edge_idx++)
    {
        curr_edge = mygraph.getEdge(edge_idx);
        if(ds.find(get<0>(curr_edge)) != ds.find(get<1>(curr_edge)))
        {
            ds.union_set(get<0>(curr_edge), get<1>(curr_edge));
        }
        else
        {
            rm_edges.emplace_back(curr_edge);
            total_cost += get<2>(curr_edge);
        }
    }
    
    output_f << total_cost << endl;
    for(auto &e: rm_edges)
    {
        output_f << get<0>(e) << " " << get<1>(e) << " " << int(get<2>(e)) << endl;
    }
}