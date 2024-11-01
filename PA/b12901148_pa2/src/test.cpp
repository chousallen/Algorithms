#include <iostream>
using namespace std;

struct ele
{
    int val;
};

int main()
{
    ele *p = new ele[5*3];
    ele **arr = new ele*[3];
    for(int i=0; i<3; i++)
    {
        arr[i] = p + i*5;
    }

    printf("p: %p\n", p);

    for(int i=0; i<15; i++)
    {
        p[i].val = i;
    }

    printf("arr[0]: %p\n", arr[0]);
    printf("p: %p\n", p);
    printf("p[0].val: %p\n", &p[0].val);
    printf("arr[0][0].val: %p\n", &arr[0][0].val);

    delete[] arr[0];
    delete[] arr;

    return EXIT_SUCCESS;
}