#ifndef _MPS_H_
#define _MPS_H_

#include <cstring>

struct map_ele
{
    int size;
    //int chord_start;
};

int** init_mps_table(int n);
int mps_len(int* chords, int n, int** mps_table, int i, int j);
void print_mps_table(int** mps_table, int n);
int* get_mps(int** mps_table, int n, int* chords, int i, int j);
void delete_mps_table(int** mps_table, int* mps, int n);
int Max(int a, int b);

int** init_mps_table(int n)
{
    unsigned long size = (2*long(n)+1) * long(n);
    int* tmp_ptr = new int[size];
    memset(tmp_ptr, -1, size*sizeof(int));
    
    int** mps_table = new int*[n*2];
    for(unsigned long i=0, addr=0, d=n*2-1; i<(unsigned long)(n)*2; i++)
    {
        mps_table[i] = tmp_ptr + addr;
        addr += d;
        d-=1;
    }
    //base case
    for(int i=0; i<2*n; i++)
    {
        mps_table[i][i] = 0;
    }
    return mps_table;
}

int mps_len(int* chords, int n, int** mps_table, int i, int j)
{
    if(i>=j)
        return 0;
    if(mps_table[i][j] != -1)
        return mps_table[i][j];
    
    int k = chords[j];

    //printf("[%d, %d]: ", i, j);

    if(k == i)
    {
        //printf("find chord\n");
        mps_table[i][j] = 1 + mps_len(chords, n, mps_table, i+1, j-1);
    }
    else if(j>k && k>i)
    {
        //printf("inner case\n");
        mps_table[i][j] = Max(mps_len(chords, n, mps_table, i, j-1), 1+mps_len(chords, n, mps_table, i, k-1)+mps_len(chords, n, mps_table, k+1, j-1));
    }
    else
    {
        //printf("outer case\n");
        mps_table[i][j] = mps_len(chords, n, mps_table, i, j-1);
    }
    return mps_table[i][j];
}

void print_mps_table(int** mps_table, int n)
{
    printf("mps_table[i]: i+1\n");
    for(int i=0; i<n*2; i++)
    {
        printf("mps_table[%d]: ", i);
        for(int j=i+1; j<n*2; j++)
        {
            printf("%d ", mps_table[i][j]);
        }
        printf("\n");
    }
}

int* get_mps(int** mps_table, int n, int* chords, int i, int j)
{
    //printf("get_mps(%d, %d)\n", i, j);
    static int size = mps_table[0][n*2-1], curr = 0;
    static int *mps = new int [size];
    if(i>=j)
        return mps;
    if(chords[i] == j)
    {
        //printf("case1\n");
        mps[curr++] = i;
        get_mps(mps_table, n, chords, i+1, j-1);
    }
    else 
    {
        int k = chords[j];
        if(k>i && k<j)
        {
            if(1+mps_table[i][k-1]+mps_table[k+1][j-1] > mps_table[i][j-1])
            {
                //printf("case2-1\n");
                get_mps(mps_table, n, chords, i, k-1);
                mps[curr++] = k;
                get_mps(mps_table, n, chords, k+1, j);
            }
            else
            {
                //printf("case2-2\n");
                get_mps(mps_table, n, chords, i, j-1);
            }
        }
        else
        {
            //printf("case3\n");
            get_mps(mps_table, n, chords, i, j-1);
        }
    }

    return mps;
}

void delete_mps_table(int** mps_table, int* mps, int n)
{
    delete[] (mps_table[0]);
    delete[] mps_table;
    delete[] mps;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

#endif // _MPS_H_