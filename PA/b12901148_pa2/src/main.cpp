#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "main.h"
#include "mps.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Error: Invalid number of arguments" << endl;
        return EXIT_FAILURE;
    }
    string ip_dir = argv[1], op_dir = argv[2];
    fstream ip_file, op_file;
    ip_file.open(ip_dir, ios::in);
    op_file.open(op_dir, ios::out|ios::trunc);

    if (!ip_file.is_open())
    {
        cout << "Error: Unable to open input file" << endl;
        return EXIT_FAILURE;
    }

    int n = 0;
    ip_file >> n; //the first line is 2n
    n /= 2;
    int* chords = get_chords(ip_file, n);
    ip_file.close();
    int** mps_table = init_mps_table(n);
    //print_mps_table(mps_table, n);
    int mpssize = mps_table[0][n*2-1];
    op_file << mpssize << endl;
    for(int i=0; i<mpssize; i++)
    {
        op_file << 0 << " " << 0 << endl;
    }

    /*
    vector<vector<map_ele>> mps_table = construct_mps_table(chords, n);
    printf("MPS table constructed\n");
    int max = 0;
    for(int i=0; i<n*2-1; i++)
    {
        for(int j=i; j<n*2; j++)
        {
            if(mps_table[i][j].size > max)
                max = mps_table[i][j].size;
        }
    }
    printf("2n: %d\n", n*2);
    printf("Max: %d\n", max);
    vector<int> mps;
    get_mps(mps_table, 0, n*2-1, chords, mps);
    printf("MPS found\n");

    op_file << mps_table[0][n*2-1].size << endl;
    for(int i=0; i<int(mps.size()); i++)
    {
        op_file << mps[i] << " " << chords[mps[i]] << endl;
    }*/
    delete_mps_table(mps_table, n);
    delete[] chords;
    op_file.close();

    return EXIT_SUCCESS;
}