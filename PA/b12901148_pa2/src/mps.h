#ifndef _MPS_H_
#define _MPS_H_

struct map_ele
{
    int size;
    int chord_start;
};

vector<vector<map_ele>> construct_mps_table(vector<int> &chords, int n);
void get_mps(vector<vector<map_ele>> &mps_table, int i, int j, vector<int> &chords, vector<int> &mps);

vector<vector<map_ele>> construct_mps_table(vector<int> &chords, int n)
{
    vector<vector<map_ele>> mps_table(n*2-1, vector<map_ele>(n*2, {0, -1}));
    
    int l_max = n*2-1;
    for(int l=1; l<=l_max; l++)
    {
        int i_max = n*2-1-l;
        for(int i=0; i<=i_max; i++)
        {
            int j = chords[i+l];
            if(i == j)
            {
                mps_table[i][i+l].size = mps_table[i+1][i+l-1].size + 1;
                mps_table[i][i+l].chord_start = i;
            }
            else if(i+l > j > i) // inner case
            {
                // a: discard the chord, b: include the chord
                map_ele a = mps_table[i][i+l-1], b = {1+mps_table[i][j-1].size+mps_table[j+1][i+l-1].size, j};
                if(a.size > b.size)
                    mps_table[i][i+l] = a;
                else
                    mps_table[i][i+l] = b;
            }
            else
            {
                mps_table[i][i+l] = mps_table[i][i+l-1];
            }
        }
    }

    return mps_table;
}

void get_mps(vector<vector<map_ele>> &mps_table, int i, int j, vector<int> &chords, vector<int> &mps)
{
    
    //printf("i: %d, j: %d\n", i, j);
    int next_start = mps_table[i][j].chord_start;
    //printf("next_start: %d\n", next_start);
    int end = chords[next_start];
    //printf("end: %d\n", end);
    if(next_start == -1)
        return;
    if(next_start == i)
    {
        mps.push_back(i);
        get_mps(mps_table, i+1, j-1, chords, mps);
    }
    else
    {
        get_mps(mps_table, i, next_start-1, chords, mps);
        mps.push_back(next_start);
        get_mps(mps_table, next_start+1, end, chords, mps);
    }
}


#endif // _MPS_H_