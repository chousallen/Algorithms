#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int size = 10;
    int *ptr = new int[size];
    memset(ptr, -1, size*sizeof(int));

    for (int i = 0; i < size; i++)
    {
        printf("%d, ", ptr[i]);
    }
    

    return EXIT_SUCCESS;
}