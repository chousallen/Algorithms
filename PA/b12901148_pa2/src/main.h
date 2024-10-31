#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> get_chords(fstream &ip_file, int n);

vector<int> get_chords(fstream &ip_file, int n)
{
    vector<int> chords(n*2);
    for(int i=0; i<n; i++)
    {
        int start, end;
        ip_file >> start >> end;
        chords[start] = end;
        chords[end] = start;
    }
    int tmp;
    ip_file >> tmp;
    if(tmp != 0)
    {
        cout << "Warning: meets no zero in the end of input file" << endl;
    }
    return chords;
}

#endif // _MAIN_H_