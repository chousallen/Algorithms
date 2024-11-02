#ifndef _MPS_H_
#define _MPS_H_

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
    
    int** mps_table = new int*[n*2];
    for(unsigned long i=0, addr=0, d=n*2-1; i<(unsigned long)(n)*2; i++)
    {
        mps_table[i] = tmp_ptr + addr;
        addr += d;
        d-=1;
    }
    return mps_table;
}

int** fill_mps_table(int* chords, int n)
{
    int** mps_table = init_mps_table(n);

    //base case
    for(int i=0; i<2*n; i++)
    {
        mps_table[i][i] = 0;
    }
    
    for(int l=1; l<=2*n-1; l++)
    {
        int i_max = 2*n-1-l;
        for(int i=0; i<=i_max; i++)
        {
            int j = chords[i+l];
            if(j == i)                                                                                                                 cccccccccccccccc  c nnnnnn   n nnnn
            {
                mps_table[i][i+l] = mps_table[i+1][i+l-1] + 1;
            }
            else if(i+l>j && j>i)
            {
                mps_table[i][i+l] = Max(1 + mps_table[i][j-1] + mps_table[j+1][i+l-1], mps_table[i][i+l-1]);
            }
            else
            {
                mps_table[i][i+l] = mps_table[i][i+l-1];
            }
        }
    }
    return mps_table;
}

void print_mps_table(int** mps_table, int n)
{
    for(int i=0; i<n*2-1; i++)
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