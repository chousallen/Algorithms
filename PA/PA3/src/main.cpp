#include <iostream>
#include <fstream>

#include "graph.h"

using namespace std;

bool directed = false;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("3 arguments expected, but %d got\n", argc);
        return EXIT_FAILURE;
    }
    ifstream input_f(argv[1]);
    ofstream output_f(argv[2]);
    
    char tmp;
    input_f >> tmp;
    switch(tmp)
    {
        case 'u':
            directed = false;
            break;
        case 'd':
            directed = true;
        default:
            printf("read direct error, %c got\n", tmp);
            break;
    }
    int weight = 0, tmp_int = 1;
    uint16_t v_size = 0, from = 0, to = 0;
    uint32_t e_size = 0;
    input_f >> v_size >> e_size;
    
    Graph mygraph = Graph(v_size);
    if(!directed)
    {
        for(uint32_t i=0; i<e_size; i++)
        {
            input_f >> from >> to >> weight;
            mygraph.addEdge(from, to, weight);
            mygraph.addEdge(to, from, weight);
        }
    }
    else
    {
        for(uint32_t i=0; i<e_size; i++)
        {
            input_f >> from >> to >> weight;
            mygraph.addEdge(from, to, weight);
        }
    }
    input_f >> tmp_int;
    if(tmp_int != 0)
    {
        printf("expect ended by 0, but %hd got\n", (tmp_int));
    }
    mygraph.print();

    input_f.close();
    output_f.close();
}
