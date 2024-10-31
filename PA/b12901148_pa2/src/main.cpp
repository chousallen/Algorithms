#include <iostream>
#include <fstream>
#include <string>

#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
    string ip_dir = argv[1], op_dir = argv[2];
    fstream ip_file, op_file;
    ip_file.open(ip_dir, ios::in);
    op_file.open(op_dir, ios::out|ios::trunc);
    

    return EXIT_SUCCESS;
}