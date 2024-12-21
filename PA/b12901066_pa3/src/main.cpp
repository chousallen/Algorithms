#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include "vertex.h"
#include "binary_heap.h"
using namespace std;

struct data {
    int v1;
    int v2;
    short w;
};

int n, m;
short adjMat[10000][10000] = {};
vector<int> adjList[10000];
vector<int> adjAlledge[10000];
short weight[10000][10000] = {};
vertex vertices[10000] = {};
// Note: check if edge exists before using weight

void help_message() {
    cout << "usage: cb <input_file> <output_file>" << endl;
}

// Helpful functions

bool cmp(data a, data b) {
    return a.w < b.w;
}

void restore(vector<data>& myList) {
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        adjMat[(*it).v1][(*it).v2] = 1;
    }
}

int DFSAux(vector<data>& myList, vector<data>& alternate, data& myData, int UB, int &change, int index) {
    // cout << "HAPPY: " << index << endl;
    int res;
    vertices[index].color = GRAY;
    for(int i = 0; i < adjList[index].size(); i++) {
        // cout << "PARTY: " << adjList[index][i] << " and " << adjMat[index][adjList[index][i]] << endl;
        if(adjMat[index][adjList[index][i]] == 1) {
            if(vertices[adjList[index][i]].color == WHITE) {
                vertices[adjList[index][i]].p = &vertices[index];
                res = DFSAux(myList, alternate, myData, UB, change, adjList[index][i]);
                if(res == -2) { // give up
                    // cout << index << ", Restore time...\n";
                    return -2;
                }
                else if(res != -1) {
                    // cout << index << ", FOUND CYCLE: " << adjList[index][i] << ", backtrace\n";
                    if(weight[index][adjList[index][i]] < myData.w) {
                        myData.v1 = index;
                        myData.v2 = adjList[index][i];
                        myData.w = weight[index][adjList[index][i]];
                    }
                    if(res == index) {
                        // cout << "SUMMARY TIME:\n";
                        alternate.push_back(myData);
                        change += myData.w;
                        adjMat[myData.v1][myData.v2] = -1;
                        // cout << "Change: " << change << "\n";
                        if(change >= UB) {
                            // cout << index << ", Restore time...\n";
                            restore(alternate);
                            return -2;
                        }
                        i--;
                        continue;
                    }
                    else {
                        vertices[index].color = WHITE;
                        vertices[index].p = NULL;
                        return res;
                    }
                }
            }
            else if(vertices[adjList[index][i]].color == GRAY) { // cycle!
                // cout << index << ", FOUND CYCLE: " << adjList[index][i] << ", backtrace\n";
                vertices[index].color = WHITE;
                vertices[index].p = NULL;
                myData.v1 = index;
                myData.v2 = adjList[index][i];
                myData.w = weight[index][adjList[index][i]];
                return adjList[index][i];
            }
        }
    }
    vertices[index].color = BLACK;
    return -1;
}

bool DFS(vector<data>& myList, long long & count, int UB) {
    vector<data> alternate;
    data myData;
    int change = 0, res;
    for(int i = 0; i < n; i++) {
        vertices[i].p = NULL;
        vertices[i].color = WHITE;
    }
    for(int i = 0; i < n; i++) {
        myData.w = 1000;
        if(vertices[i].color == WHITE) {
            res = DFSAux(myList, alternate, myData, UB, change, i);
            // cout << "Obtain: " << UB << " " << change << " " << res << "\n";
            if(res == -2) {
                // cout << "SO SAD\n";
                return false;
            }
        }
    }
    if(alternate.size() != 0) {
        myList.insert(myList.end(), alternate.begin(), alternate.end());
    }
    if(change >= UB) {
        restore(alternate);
        return false;
    }
    count -= UB;
    count += change;
    return true;
}

int getUndirectWeight(int i, int j) {
    if(adjMat[i][j] == 1) {
        if(adjMat[j][i] == 1) {
            return (weight[i][j] < weight[j][i]) ? weight[j][i] : weight[i][j];
        }
        else {
            return weight[i][j];
        }
    }
    else {
        return weight[j][i];
    }
}

void determineWhichEdge(data& myData, int i, int j) {
    if(adjMat[i][j] == 1) {
        if(adjMat[j][i] == 1) {
            if(weight[i][j] < weight[j][i]) {
                myData.v1 = i;
                myData.v2 = j;
                myData.w = weight[i][j];
            }
            else {
                myData.v1 = j;
                myData.v2 = i;
                myData.w = weight[j][i];
            }
        }
        else {
            myData.v1 = i;
            myData.v2 = j;
            myData.w = weight[i][j];
        }
    }
    else {
        myData.v1 = j;
        myData.v2 = i;
        myData.w = weight[j][i];
    }
}

// -----

void Cycle_Breaking_Undirected_Unweighted(fstream& fout) {
    /*
        We simply use DFS, if back edge is detected, remove it.
        Time complexity is O(V + E)
    */
    int count = 0;
    vector<data> results;
    stack<int> S; // stack to run DFS, store the index of the vertex
    int nowInd;
    data myRes;
    S.push(0);
    
    // run DFS
    while(S.size() != 0) {
        nowInd = S.top();
        // cout << "Now node: " << nowInd << endl;
        vertices[nowInd].color = GRAY;
        if(vertices[nowInd].nowCheck == adjList[nowInd].size()) {
            vertices[nowInd].color = BLACK;
            S.pop();
            // cout << "BYE" << endl;
            continue;
        }
        // cout << "My friend: " << adjList[nowInd][vertices[nowInd].nowCheck] << endl;
        if(vertices[nowInd].p != NULL && adjList[nowInd][vertices[nowInd].nowCheck] == vertices[nowInd].p->index) {
            vertices[nowInd].nowCheck++;
            continue;
        }
        else {
            if(vertices[adjList[nowInd][vertices[nowInd].nowCheck]].color == WHITE) { // tree edge
                vertices[adjList[nowInd][vertices[nowInd].nowCheck]].p = &vertices[nowInd];
                S.push(adjList[nowInd][vertices[nowInd].nowCheck]);
                vertices[nowInd].nowCheck++;
                continue;
            }
            else if(vertices[adjList[nowInd][vertices[nowInd].nowCheck]].color == GRAY){ // back edge
                // cout << "BEdge! " << results.size() << endl;
                myRes.v1 = nowInd;
                myRes.v2 = adjList[nowInd][vertices[nowInd].nowCheck];
                myRes.w = weight[myRes.v1][myRes.v2];
                results.push_back(myRes);
                count++;
                vertices[nowInd].nowCheck++;
                continue;
            }
            else {
                vertices[nowInd].nowCheck++;
                continue;
            }
        }
    }

    // print result
    // cout << "Printing result" << endl;
    fout << count << endl;
    for(auto it = results.begin(); it != results.end(); ++it) {
        fout << (*it).v1 << " " << (*it).v2 << " " << (*it).w << "\n";
    }
}

void Cycle_Breaking_Undirected_Weighted(fstream& fout) {
    /*
        We use Prim's Algorithm
        Time Complexity is O(ElgV)
    */

    // Initialize
    vertices[0].key = 0;
    binary_heap* mHeap = new binary_heap;

    for(int i = 0; i < n; i++) {
        mHeap->insert(&vertices[i]);
    }

    vertex* now;
    while(mHeap->get_size() != 0) {
        now = mHeap->extract_min();
        // cout << "now: " << now->index << endl;
        for(int i = 0; i < adjList[now->index].size(); i++) {
            if((!vertices[adjList[now->index][i]].used) && -weight[now->index][adjList[now->index][i]] < vertices[adjList[now->index][i]].key) {
                vertices[adjList[now->index][i]].p = now;
                mHeap->decrease_key(vertices[adjList[now->index][i]].heapInd, -weight[now->index][adjList[now->index][i]]);
            }
        }
    }

    // collect edges
    long long int count = 0;
    vector<data> results;
    data myRes;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < adjList[i].size(); j++) {
            if(!(vertices[i].p == &vertices[adjList[i][j]] || vertices[adjList[i][j]].p == &vertices[i])) {
                if(i < adjAlledge[i][j]) { // adjMat[i][adjAlledge[i][j]] == 1
                    count += weight[i][adjList[i][j]];
                    myRes.v1 = i;
                    myRes.v2 = adjList[i][j];
                    myRes.w = weight[i][adjList[i][j]];
                    results.push_back(myRes);
                    // adjMat[adjList[i][j]][i] = 0;
                }
            }
        }
    }

    // print result
    // cout << "Printing result" << endl;
    fout << count << endl;
    for(auto it = results.begin(); it != results.end(); ++it) {
        fout << (*it).v1 << " " << (*it).v2 << " " << (*it).w << "\n";
    }
}

void Cycle_Breaking_Directed_Weighted(fstream& fout) {
    // Find_SCC();

    // Find (Undirect) MST First
    // Initialize
    vertices[0].key = 0;
    binary_heap* mHeap = new binary_heap;

    for(int i = 0; i < n; i++) {
        mHeap->insert(&vertices[i]);
    }

    vertex* now;
    while(mHeap->get_size() != 0) {
        now = mHeap->extract_min();
        // cout << "now: " << now->index << endl;
        for(int i = 0; i < adjAlledge[now->index].size(); i++) {
            if((!vertices[adjAlledge[now->index][i]].used) && -getUndirectWeight(now->index, adjAlledge[now->index][i]) < vertices[adjAlledge[now->index][i]].key) {
                vertices[adjAlledge[now->index][i]].p = now;
                mHeap->decrease_key(vertices[adjAlledge[now->index][i]].heapInd, -getUndirectWeight(now->index, adjAlledge[now->index][i]));
            }
        }
    }

    // collect edges
    long long int count = 0;
    vector<data> results;
    data myRes;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < adjAlledge[i].size(); j++) {
            if(!(vertices[i].p == &vertices[adjAlledge[i][j]] || vertices[adjAlledge[i][j]].p == &vertices[i])) {
                if(i < adjAlledge[i][j]) { // adjMat[i][adjAlledge[i][j]] == 1
                    // if(i == 0) cout << i << " " << adjAlledge[i][j] << endl;
                    if(adjMat[i][adjAlledge[i][j]] == 1) {
                        // determineWhichEdge(myRes, i, adjAlledge[i][j]);
                        myRes.v1 = i;
                        myRes.v2 = adjAlledge[i][j];
                        myRes.w = weight[i][adjAlledge[i][j]];
                        count += myRes.w;
                        adjMat[myRes.v1][myRes.v2] = -1;
                        results.push_back(myRes);
                    }
                    if(adjMat[adjAlledge[i][j]][i] == 1) {
                        // determineWhichEdge(myRes, i, adjAlledge[i][j]);
                        myRes.v1 = adjAlledge[i][j];
                        myRes.v2 = i;
                        myRes.w = weight[adjAlledge[i][j]][i];
                        count += myRes.w;
                        adjMat[myRes.v1][myRes.v2] = -1;
                        results.push_back(myRes);
                    }
                }
            }
            else if(adjMat[i][adjAlledge[i][j]] == 1 && adjMat[adjAlledge[i][j]][i] == 1){
                if(i < adjAlledge[i][j]) {
                    determineWhichEdge(myRes, i, adjAlledge[i][j]);
                    count += myRes.w;
                    adjMat[myRes.v1][myRes.v2] = -1;
                    results.push_back(myRes);
                }
            }
        }
    }

    bool canBeOpt = 0;
    // sort(results.begin(), results.end(), cmp);
    while(true) {
        canBeOpt = 0;
        for (auto it = results.begin(); it != results.end();) {
            // if((*it).w <= 0) break;
            // cout << "Size: " << results.size() << ", Checking: " << (*it).v1 << " " << (*it).v2 << endl;
            adjMat[(*it).v1][(*it).v2] = 1;
            if(DFS(results, count, (*it).w) == true) { // edge accepted
                it = results.erase(it);
                canBeOpt = 1;
                // cout << "FIND BETTER " << count << endl;;
            }
            else {
                adjMat[(*it).v1][(*it).v2] = -1;
                ++it;
            }
        }
        if(canBeOpt == 0) break;
    }

    // print result
    fout << count << endl;
    int resSize = results.size();
    for(auto it = results.begin(); it != results.end(); ++it) {
        fout << (*it).v1 << " " << (*it).v2 << " " << (*it).w << "\n";
    }
}

int main(int argc, char* argv[])
{
    // check arguments
    if(argc != 3) {
       help_message();
       return 0;
    }

    // read inputs
    std::ios::sync_with_stdio(false);
    char buffer[200];
    fstream fin(argv[1]);
    fin.tie(nullptr);
    fstream fout;
    fout.open(argv[2], ios::out);
    char type;
    fin >> type;
    fin >> n;
    fin >> m;
    bool isWeighted = 0;

    // cout << "Reading datas..." << endl;

    int v1, v2;
    short w;
    for(int i = 0; i < m; i++) {
        fin >> v1 >> v2 >> w;
        adjMat[v1][v2] = 1;
        adjList[v1].push_back(v2);
        adjAlledge[v1].push_back(v2);
        adjAlledge[v2].push_back(v1);
        weight[v1][v2] = w;
        if(w != 1) {
            isWeighted = 1;
        }
        if(type == 'u') {
            adjMat[v2][v1] = 1;
            adjList[v2].push_back(v1);
            weight[v2][v1] = w;
        }
    }
    int junk;
    fin >> junk;
    for(int i = 0; i < n; i++) {
        vertices[i].index = i;
    }

    // cout << "Finish reading datas" << endl;
    // cout << "Doing algorithm..." << endl;

    // do algorithm
    if(type == 'u') {
        if(!isWeighted) {
            Cycle_Breaking_Undirected_Unweighted(fout);
        }
        else {
            Cycle_Breaking_Undirected_Weighted(fout);
        }
    }
    else {
        Cycle_Breaking_Directed_Weighted(fout);
    }

    fin.close();
    fout.close();

    return 0;
}