// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
//  Modify     [2024/9/2 Meng-Chen Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<random>
#include <climits>
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int n = data.size();
    for(int i = 1; i < n ; i++){
        int key = data[i];
        int j = i-1;
        while(j >= 0 && data[j] > key ){
            data[j+1] = data[j];
            j = j-1;
        }
        data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data,int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if(low < high){
        if(flag == 0){
            int q = Partition(data, low, high);
            QuickSortSubVector(data, low, q-1,0);
            QuickSortSubVector(data, q+1, high,0);
        }
        if(flag == 1){
            int q = RandomizedPartition(data, low, high);
            QuickSortSubVector(data, low, q-1,1);
            QuickSortSubVector(data, q+1, high,1);
        }
    }

}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> distrib(low, high); 
    int i = distrib(gen);
    int temp = data[i];
    data[i] = data[high];
    data[high] = temp;
    return Partition(data, low, high);
}
int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int x = data[high];
    int i = low-1;
    for(int j = low ; j < high-1 || j == high-1 ; j++){
        if(data[j] < x || data[j] ==x){
            i++;
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    data[high] = data[i+1];
    data[i+1] = x;
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (low < high){
        int q = (low + high)/2;
        MergeSortSubVector(data, low, q);
        MergeSortSubVector(data, q+1, high);
        Merge(data, low, q, q+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1 - low + 1;
    int n2 = high - middle1;
    int l[n1+1] ;
    int r[n2+1] ;
    l[n1] = INT_MAX;
    r[n2] = INT_MAX;

    for(int i = 0; i < n1; i++){
        l[i] = data[low+i];
    }
    for(int j = 0; j< n2; j++){
        r[j] = data[middle1+j+1];
    }
    int i = 0;
    int j = 0;
    for(int k = low; k < high+1; k++){
        if(l[i] <= r[j]&&i != n1){
            data[k] = l[i];
            i++;
        }
        else {
            data[k] = r[j];
            j++;
        }
    }

}

// bottom-up style implementation of merge sort
void SortTool::BottomUpMergeSort(vector<int>& data) 
{
  /*TODO :
    Implement merge sort in bottom-up style, in other words,
    without recursive function calls.
    Hint: 
    1. Divide data to n groups of one data each group
    2. Iteratively merge each pair of 2 neighbor groups into one larger group
    3. Finally we obtain exactly one sorted group
  */
    int  numGroup = data.size();
    int  groupmem = 1;
    while(numGroup > 1){
        int i = 0;
        while(i < data.size()){
            int low = i;
            int middle = min(i + groupmem-1,(int)data.size()-1);
            int high = min((int)data.size()-1,i+2*groupmem-1);
            Merge(data, low , middle, middle+1, high);
            i = i + 2*groupmem;
        }
        numGroup = (numGroup+1)/2 ;
        groupmem = 2 * groupmem;
    }
}

// Heap sort method, be aware that you are NOT required to implement heap sort in PA1
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
}
