#ifndef _MPS_H_
#define _MPS_H_

#include <cstring>

struct map_ele
{
    int size;
    //int chord_start;
};

int** init_mps_table(int n);
int** fill_mps_table(int* chords, int n);
void print_mps_table(int** mps_table, int n);
int* get_mps(int** mps_table, int n);
void delete_mps_table(int** mps_table, int n);
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

int* get_mps(int** mps_table, int n)
{
    int* mps = new int[mps_table[0][n*2-1]];
    int i = 0, j = n*2-1, k = 0;
    while(i < j)
    {
        if(mps_table[i][j] == mps_table[i+1][j])
        {
            i++;
        }
        else if(mps_table[i][j] == mps_table[i][j-1])
        {
            j--;
        }
        else
        {
            mps[k++] = i;
            i++;
            j--;
        }
    }
    return mps;
}

void delete_mps_table(int** mps_table, int n)
{
    delete[] (mps_table[0]);
    delete[] mps_table;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

#endif // _MPS_H_