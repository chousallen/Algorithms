// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
//  Modify     [2024/9/2 Meng-Chen Wu]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>

template <typename T>
T myMin(T x, T y) {
	return x <= y ? x : y;
}

void mySwap(int &x, int &y) {
	int tmp = x;
	x = y;
	y = tmp;
}

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int i = 1; i < data.size(); ++i) {
        int j = i;
		int tmp = data.at(i);
		while(j > 0 && tmp < data.at(j - 1)) {
			data.at(j) = data.at(j - 1);
			j--;
		}
        data.at(j) = tmp;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    if(f == 1)  srand(time(NULL));
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
    if(low >= high)
        return;
    int mid;
    if(flag == 0)
        mid = Partition(data, low, high);
    else
        mid = RandomizedPartition(data, low, high);
    QuickSortSubVector(data, low, mid - 1, flag);
    QuickSortSubVector(data, mid + 1, high, flag);
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int r = low + (rand() % (high - low + 1));
    mySwap(data.at(r), data.at(high));
    return Partition(data, low, high);
}
int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int x = data.at(high);
    int i = low - 1;
    for(int j = low; j <= high - 1; j++){
        if(data.at(j) <= x){
            i++;
        	mySwap(data.at(i), data.at(j));
        }
    }
    mySwap(data.at(i + 1), data.at(high));
    return i + 1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data) {
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high){
        int mid = (low + high) / 2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid + 1, high);
        Merge(data, low, mid, mid + 1, high);
    }  
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int* p = new int[middle1 - low + 2];
    int* q = new int[high - middle2 + 2];
    for(int i = 0; i <= middle1 - low; ++i) {
        p[i] = data.at(low + i);
    }
    for(int i = 0; i <= high - middle2; ++i) {
        q[i] = data.at(middle2 + i);
    }
    p[middle1 - low + 1] = INT_MAX;
    q[high - middle2 + 1] = INT_MAX;
    int i = 0, j = 0;
    for(int k = low; k <= high; ++k) {
        if(i <= middle1 - low && p[i] <= q[j]) {
            data.at(k) = p[i];
            i++;
        }
        else {
            data.at(k) = q[j];
            j++;
        }
    }
    delete p;
    delete q;
}

// bottom-up style implementation of merge sort
void SortTool::BottomUpMergeSort(vector<int>& data) {
  /*TODO :
    Implement merge sort in bottom-up style, in other words,
    without recursive function calls.
    Hint: 
    1. Divide data to n groups of one data each group
    2. Iteratively merge each pair of 2 neighbor groups into one larger group
    3. Finally we obtain exactly one sorted group
  */
    for (int i = 1; i < data.size(); i *= 2) {
        for (int j = 0; j <= data.size() - 1; j += 2 * i) {
			Merge(data, j, 
				  myMin(j + i - 1, (int)data.size() - 1),
				  myMin(j + i, (int)data.size() - 1),
				  myMin(j + 2 * i - 1, (int)data.size() - 1));
		}
    }
}

// Heap sort method, be aware that you are NOT required to implement heap sort in PA1
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; --i) {
        mySwap(data.at(0), data.at(i));
        heapSize--;
        MaxHeapify(data, 0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    int l = (root + 1) * 2 - 1;
    int r = l + 1;
    int largest = root;
    if(l < heapSize && data.at(l) > data.at(root))
        largest = l;
    if(r < heapSize && data.at(r) > data.at(largest))
        largest = r;
    if(largest != root){
        mySwap(data.at(root), data.at(largest));
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    for(int i = (heapSize / 2) - 1; i >= 0; --i)
        MaxHeapify(data, i);
}
