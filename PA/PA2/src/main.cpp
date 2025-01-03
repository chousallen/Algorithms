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
    int mps_size = mps_len(chords, n, mps_table, 0, 2*n-1);
    op_file << mps_size << endl;
    //print_mps_table(mps_table, n);
    int* mps = get_mps(mps_table, n, chords, 0, 2*n-1);
    //printf("mps get\n");
    for(int i=0; i<mps_size; i++)
    {
        op_file << mps[i] << " " << chords[mps[i]] << endl;
    }


    delete_mps_table(mps_table, mps, n);
    delete[] chords;
    op_file.close();

    return EXIT_SUCCESS;
}