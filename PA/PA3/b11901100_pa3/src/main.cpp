#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
//#include "../lib/tm_usage.h"

using namespace std;

char graph_type;     // directed or undirected
int v_num;           //|V|
int e_num;           //|E|
int temp_other_path; // record on dfs

class Edge;
class UD_node;
// class D_node;

class Edge
{
public:
    int weight;
    UD_node *start;
    UD_node *end;
    bool chosen;
    bool operator<(const Edge &);
    Edge operator=(const Edge &);
    bool operator==(const Edge &);
    bool operator!=(const Edge &);
    bool operator>(const Edge &);
    bool operator>=(const Edge &);
    bool operator<=(const Edge &);
    // bool cut; // cut = true if is cut; = false if not cut
    Edge();
};

bool Edge::operator<(const Edge &edge2)
{
    return (weight < edge2.weight);
}
bool Edge::operator>(const Edge &edge2)
{
    return (weight > edge2.weight);
}
bool Edge::operator>=(const Edge &edge2)
{
    return (weight >= edge2.weight);
}
bool Edge::operator<=(const Edge &edge2)
{
    return (weight <= edge2.weight);
}
Edge Edge::operator=(const Edge &edge2)
{
    weight = edge2.weight;
    start = edge2.start;
    end = edge2.end;
    chosen = edge2.chosen;
    // cout << "assignment of edge" << endl;
    return *this;
}

bool Edge::operator==(const Edge &edge2)
{
    if (start == edge2.start && end == edge2.end)
        return true;
    else
        return false;
}

bool Edge::operator!=(const Edge &edge2)
{
    if (start != edge2.start || end != edge2.end)
        return true;
    else
        return false;
}

Edge::Edge()
{
    weight = 0;
    start = 0;
    end = 0;
    chosen = true;
    // cout << "constructor of edge." << endl;
}

class UD_node // undirected node
{
public:
    UD_node *parent;  // parent of a node
    vector<Edge> adj; // adjacency list
    int rank;
    int index;
    char color;
    UD_node();
    UD_node *find();
};

UD_node *UD_node::find() // find-set with path compression
{
    if (parent == NULL)
    {
        return this;
    }
    else
    {
        parent = parent->find();
        return parent;
    }
}

UD_node::UD_node()
{
    parent = NULL;
    rank = 0;
    color = 'w';
}

void init_u_graph(std::istream &fin);
void init_d_graph(std::istream &fin);

int Kruskal();
void Union(UD_node *, UD_node *);
int check_and_print(std::ostream &);
// int DFS_check();
void check_and_print_dfs(std::ostream &);
int Kruskal_weighted();
int cut_neg_edges();

bool compare(const Edge &edge1, const Edge &edge2)
{
    return (edge1.weight < edge2.weight);
}

// vector<Edge> *adj;
// vector<UD_node> ud_vertices;
UD_node *ud_vertices; // array of undirected vertices
// UD_node *d_vertices;
vector<Edge> edges;
// Edge *edges; // array of edges
// Edge *dir_edges;
vector<UD_node *> visited;

int main(int argc, char *argv[])
{
    /*====== time test =========*/
    //CommonNs::TmUsage tmusg;
    //CommonNs::TmStat stat;
    //tmusg.periodStart();
    /*====== open files ========*/
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    /*====== read inputs =========*/
    fin >> graph_type;
    fin >> v_num;
    fin >> e_num;
    /*========== initialize the graph ==========*/
    if (graph_type == 'u')
    {
        // cout << "ckpt 0" << endl;
        init_u_graph(fin);
        // cout << "ckpt 1" << endl;
        // Kruskal();
        fout << Kruskal() << endl;
        check_and_print(fout);
    }
    if (graph_type == 'd')
    {
        init_d_graph(fin);
        // cut_neg_edges();
        // cout << "checkpoint 1" << endl;
        Kruskal();
        // cout << "checkpoint 2" << endl;
        fout << Kruskal_weighted() << endl;
        check_and_print(fout);
    }

    //tmusg.getPeriodUsage(stat);
    //cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    //cout << "memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    // for (int i = 0; i < v_num; i++)
    // {
    //     cout << i << ": ";
    //     for (int j = 0; j < ud_vertices[i].adj.size(); j++)
    //     {
    //         cout << ud_vertices[i].adj[j].end << " weight = " << ud_vertices[i].adj[j].weight << " ";
    //     }
    //     cout << endl;
    // }
    // cout << weighted << endl;
    // for (int i = 0; i < v_num; i++)
    //     cout << ud_vertices[i].set << " " << endl;
    // for (int i = 0; i < e_num; i++)
    // {
    //     cout << edges[i].weight << " ";
    // }
}

void init_u_graph(std::istream &fin)
{
    ud_vertices = new UD_node[v_num];
    // ud_vertices.reserve(v_num);
    for (int i = 0; i < v_num; i++)
    {
        ud_vertices[i].index = i;
    }
    // edges = new Edge[e_num];
    // edges.reserve(2 * e_num);
    for (int i = 0; i < e_num; i++)
    {
        int strt, ed, wght;
        fin >> strt >> ed >> wght;
        Edge temp;
        temp.start = &ud_vertices[strt];
        temp.end = &ud_vertices[ed];
        temp.weight = wght;
        edges.push_back(temp);
        // edges[i].start = &ud_vertices[strt];
        // edges[i].end = &ud_vertices[ed];
        // edges[i].weight = wght;
        // edges[2 * i + 1].start = ed;
        // edges[2 * i + 1].end = strt;
        // edges[2 * i + 1].weight = wght;
        // cout << "ckpt 3" << endl;
        ud_vertices[strt]
            .adj.push_back(edges[i]);
        // cout << "ckpt 3" << endl;
        ud_vertices[ed].adj.push_back(edges[i]);
    }
}

void init_d_graph(std::istream &fin)
{
    ud_vertices = new UD_node[v_num];
    // d_vertices = new UD_node[v_num];
    for (int i = 0; i < v_num; i++)
    {
        ud_vertices[i].index = i;
    }
    // ud_vertices.reserve(v_num);
    // dir_edges = new Edge[e_num];
    // edges = new Edge[e_num];
    // edges.reserve(e_num);

    for (int i = 0; i < e_num; i++)
    {
        int strt, ed, wght;
        fin >> strt >> ed >> wght;
        Edge temp;
        temp.start = &ud_vertices[strt];
        temp.end = &ud_vertices[ed];
        temp.weight = wght;
        edges.push_back(temp);

        // edges[i].start = &ud_vertices[strt];
        // edges[i].end = &ud_vertices[ed];
        // edges[i].weight = wght;
        ud_vertices[strt].adj.push_back(edges[i]);
        ud_vertices[ed].adj.push_back(edges[i]);
    }
}

void Union(UD_node *n1, UD_node *n2) // union by rank
{
    if (n1->rank > n2->rank)
        n2->parent = n1;
    else if (n1->rank < n2->rank)
        n1->parent = n2;
    else
    {
        n2->parent = n1;
        n1->rank++;
    }
}

int Kruskal()
{
    /*========= sort the edges ==========*/
    sort(edges.begin(), edges.end(), compare); // sort the edges
    // cout << "after sort" << endl;
    /*========= add edges to the final graph ==========*/
    int reduction = 0;
    for (int i = e_num - 1; i >= 0; i--)
    {
        UD_node *n1 = edges[i].start->find(); // Find-set(u)
        UD_node *n2 = edges[i].end->find();   // Find-set(v)
        if (n1 == n2)
        {
            reduction += edges[i].weight; // add reduced weight
            edges[i].chosen = false;
            // if (edges[i].weight < 0)
            // cout << "a neg edge is deleted." << endl;
        }
        if (n1 != n2)
        {
            edges[i].chosen = true;
            Union(n1, n2);
        }
    }
    return reduction;
}

int check_and_print(std::ostream &fout) // print the omitted edges
{
    // int reduction = 0;
    for (int i = 0; i < e_num; i++)
    {
        if (!edges[i].chosen)
        {
            fout << edges[i].start->index << " " << edges[i].end->index << " " << edges[i].weight << endl;
        }
    }
    return 0;
}

// int DFS_check()
// {
//     sort(edges, edges + e_num);
//     int reduction = 0;
//     for (int i = 0; i < e_num; i++)
//     {
//         UD_node *temp = edges[i].end;
//         edges[i].end = NULL;
//         if (DFS_visit(edges[i].start, edges[i].end) == true) // do dfs visit without edges[i]
//         {
//             reduction += edges[i].weight;
//             edges[i].chosen = false;
//         }
//         else
//         {
//             edges[i].end = temp;
//             edges[i].chosen = true;
//         }
//     }
//     return reduction;
// }

bool DFS_visit(UD_node *cur_node, UD_node *dest)
{
    if (cur_node == dest)
        return true;
    cur_node->color = 'g';
    visited.push_back(cur_node);
    for (unsigned int i = 0; i < cur_node->adj.size(); i++)
    {
        if (cur_node->adj[i].end->color == 'w')
        {
            cur_node->adj[i].end->parent = cur_node;
            if (DFS_visit(cur_node->adj[i].end, dest))
            {
                return true;
            };
        }
    }
    cur_node->color = 'b';
    return false;
}

bool DFS_add_edge(Edge *add_edge)
{
    if (DFS_visit(add_edge->start, add_edge->end))
    {
        for (unsigned int i = 0; i < visited.size(); i++)
        {
            visited[i]->color = 'w';
            // visited[i]->parent = NULL;
        }
        visited.clear();
        // cout << "has way from " << add_edge->start->index << " to " << add_edge->end->index << endl;
        // cout << "edge " << add_edge->start->index << " -> " << add_edge->end->index << " deleted" << endl;
        return true;
    }
    else
    {
        for (int i = 0; i < visited.size(); i++)
        {
            visited[i]->color = 'w';
        }
        visited.clear();
        // cout << "no way from " << add_edge->start->index << " to " << add_edge->end->index << endl;
        // cout << "edge " << add_edge->start->index << " -> " << add_edge->end->index << " preserved" << endl;
        return false;
    }
}

bool DFS_other_way(Edge *edge_check)
{
    if (DFS_visit(edge_check->end, edge_check->start))
    {
        for (int i = 0; i < visited.size(); i++)
        {
            visited[i]->color = 'w';
        }
        visited.clear();
        // cout << "has way from " << edge_check->end->index << " to " << edge_check->start->index << endl;
        // cout << "edge " << edge_check->end->index << " -> " << edge_check->start->index << " deleted" << endl;
        return true;
    }
    else
    {
        for (int i = 0; i < visited.size(); i++)
        {
            visited[i]->color = 'w';
        }
        visited.clear();
        // cout << "no way from " << edge_check->end->index << " to " << edge_check->start->index << endl;
        // cout << "edge " << edge_check->end->index << " -> " << edge_check->start->index << " preserved" << endl;
        return false;
    }
}

int cut_neg_edges()
{
    int temp_reduction = 0;
    for (int i = 0; i < e_num && edges[i].weight < 0; i++)
    {

        if (DFS_add_edge(&edges[i]) || DFS_other_way(&edges[i]))
        {
            edges[i].chosen = false;
            temp_reduction += edges[i].weight;
            for (unsigned int j = 0; j < edges[i].start->adj.size(); j++)
            {
                if (edges[i].start->adj[j] == edges[i])
                {
                    edges[i].start->adj.erase(edges[i].start->adj.begin() + j);
                }
            }
        }
        else
        {
            edges[i].start->adj.push_back(edges[i]);
        }
    }
    // cout << "deducted negative: " << temp_reduction << endl;
    return temp_reduction;
}

int Kruskal_weighted()
{
    int reduction = 0;
    /*========= initialize the directed graph (after undirected kruskal) =========*/
    // sort(dir_edges, dir_edges + e_num);
    for (int i = 0; i < e_num; i++)
    {
        // dir_edges[i] = edges[i];
        if (!edges[i].chosen)
        {
            for (unsigned int j = 0; j < edges[i].start->adj.size(); j++)
            {
                if (edges[i] == edges[i].start->adj[j])
                {
                    edges[i].start->adj.erase(edges[i].start->adj.begin() + j);
                }
            }
        }
    }
    // for (int i = 0; i < e_num; i++)
    // cout << edges[i].chosen << " " << endl;
    // reduction = reduction + cut_neg_edges();
    /*=============== adding back postive edges =================*/
    for (int i = e_num - 1; i >= 0; i--)
    {
        // cout << "edges[" << i << "] have weight of " << edges[i].weight << endl;
        if (edges[i].weight > 0)
        {
            if (!edges[i].chosen)
            {
                // cout << "check for edge " << i << endl;
                if (/*!DFS_add_edge(&edges[i]) && */ !DFS_other_way(&edges[i]))
                {
                    // cout << "won't cause loop " << i << endl;
                    edges[i].chosen = true;
                    // cout << "edge " << i << " is chosen." << endl;
                    // cout << "putting back edge..." << endl;
                    edges[i].start->adj.push_back(edges[i]);
                }
                else
                {
                    edges[i].chosen = false;
                    // cout << edges[i].weight << endl;
                    reduction += edges[i].weight;
                }
            }
        }
        else
        {
            if (!edges[i].chosen)
            {
                // cout << "check for edge " << i << endl;

                edges[i].chosen = false;
                // cout << edges[i].weight << endl;
                reduction += edges[i].weight;
            }
        }
    }
    return reduction;
}
