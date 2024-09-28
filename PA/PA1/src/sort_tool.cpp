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
#include <string.h>

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int curr_idx = 1; curr_idx < data.size(); curr_idx++)
    {
        int key = data[curr_idx];
        for(int i = curr_idx - 1; i >= 0; i--)
        {
            if(data[i] > key)
            {
                data[i + 1] = data[i];
                if(i == 0)
                {
                    data[i] = key;
                }
            }
            else
            {
                data[i + 1] = key;
                break;
            }
        }
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
    srand(time(NULL));
    if(low < high)
    {
        int pivot;
        if(flag == 0)
        {
            pivot = Partition(data, low, high);
        }
        else
        {
            pivot = RandomizedPartition(data, low, high);
        }
        QuickSortSubVector(data, low, pivot - 1, flag);
        QuickSortSubVector(data, pivot + 1, high, flag);
    }
}

int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int random = low + rand() % (high - low + 1);
    swap(data[random], data[high]);
    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int pivot = data[high];
    int left = low - 1;
    for(int curr = low; curr < high; curr++)
    {
        if(data[curr] < pivot)
        {
            swap(data[++left], data[curr]);
        }
    }
    swap(data[++left], data[high]);
    return left;
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
    if(low < high)
    {
        int middle = (low + high) / 2;
        MergeSortSubVector(data, low, middle);
        MergeSortSubVector(data, middle + 1, high);
        Merge(data, low, middle, middle + 1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    vector<int> tmp;
    tmp.resize(high - low + 1);
    int left_curr = low, right_curr = middle2, idx = 0;
    
    while(left_curr <= middle1 && right_curr <= high)
    {
        if(data[left_curr] < data[right_curr])
        {
            tmp[idx++] = data[left_curr++];
        }
        else
        {
            tmp[idx++] = data[right_curr++];
        }
    }
    if(left_curr <= middle1)
    {
        memcpy(&tmp[idx], &data[left_curr], sizeof(int) * (middle1 - left_curr + 1));
        idx += middle1 - left_curr + 1;
    }
    if(right_curr <= high)
    {
        memcpy(&tmp[idx], &data[right_curr], sizeof(int) * (high - right_curr + 1));
        idx += high - right_curr + 1;
    }
    /*while(left_curr <= middle1)
    {
        tmp[idx++] = data[left_curr++];
    }
    while(right_curr <= high)
    {
        tmp[idx++] = data[right_curr++];
    }*/
    memcpy(&data[low], &tmp[0], sizeof(int) * idx);
    /*for(int i = 0; i < idx; i++)
    {
        data[low + i] = tmp[i];
    }*/
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
    for(int width = 1; width < data.size(); width *= 2)
    {
        for(int i = 0; i < data.size(); i += 2 * width)
        {
            int low = i;
            int middle = min(i + width - 1, (int)data.size() - 1);
            int high = min(i + 2 * width - 1, (int)data.size() - 1);
            Merge(data, low, middle, middle + 1, high);
        }
    }
}

// Heap sort method, be aware that you are NOT required to implement heap sort in PA1
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--)
    {
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
