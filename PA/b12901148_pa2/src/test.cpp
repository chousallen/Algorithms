#include <iostream>
using namespace std;

struct ele
{
    int val;
};

int main()
{
    long n = 50000, sum = 0, size = (2*n+1) * n;
    for(int k = 2*n; k>=2*n-24469; k--)
    {
        sum += k;
    }
    printf("sum: %ld\n", sum);
    printf("size: %ld\n", size);

    return EXIT_SUCCESS;
}