#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector<pair<int, int> > ans;
int** dp;
int* chord;
char buffer[200];
int cnt = 0;

void trace_back(int j, int i) {
    if (j <= i) return;
    if (dp[j][i] <= 0) {
        trace_back(j - 1, i);
    }
    else {
        int k = chord[j];
        if (k == i) {
            ans[cnt++] = make_pair(i, j);
            trace_back(j - 1, i + 1);
        }
        else {
            ans[cnt++] = make_pair(k, j);
            trace_back(k - 1, i);
            trace_back(j - 1, k + 1);
        }
    }
    // if (backtrack[j][i] == 1) {
    //     ans[cnt++] = make_pair(i, j);
    //     trace_back(j - 1, i + 1);
    // }
    // else if (backtrack[j][i] == 2) {
    //     trace_back(j - 1, i);
    // }
    // else {
    //     int k = chord[j];
    //     ans[cnt++] = make_pair(k, j);
    //     trace_back(k - 1, i);
    //     trace_back(j - 1, k + 1);
    // }
}

int main(int argc, char* argv[]) {

    FILE* fin = fopen(argv[1], "r");
    FILE* fout = fopen(argv[2], "w");
    int n, a, b;
    fscanf(fin, "%d", &n);
    chord = new int[n];
    n >>= 1;
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d %d", &a, &b);
        chord[a] = b;
        chord[b] = a;
    }
    n <<= 1;
    dp = new int* [n];
    for (int i = 0; i < n; i++) {
        dp[i] = new int[i + 1];
    }
    for (int j = 1; j < n; j++) {
        for (int i = j - 1; i >= 0; i--) {
            int k = chord[j];
            if (k == i)
                dp[j][i] = abs(dp[j - 1][i + 1]) + 1;

            else if (k > j || k < i)
                dp[j][i] = -abs(dp[j - 1][i]);
            else {
                if (1 + abs(dp[k - 1][i]) + abs(dp[j - 1][k + 1]) > abs(dp[j - 1][i]))
                    dp[j][i] = 1 + abs(dp[k - 1][i]) + abs(dp[j - 1][k + 1]);
                else
                    dp[j][i] = -abs(dp[j - 1][i]);
            }
        }
    }

    fprintf(fout, "%d\n", abs(dp[n - 1][0]));
    ans.resize(abs(dp[n - 1][0]));
    trace_back(n - 1, 0);
    sort(ans.begin(), ans.end());
    for (int i = 0; i < abs(dp[n - 1][0]); i++) {
        fprintf(fout, "%d %d\n", ans[i].first, ans[i].second);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
