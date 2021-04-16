#include "sorting/sorting.hpp"
#include <iostream>

void bubbleSort(std::vector<int>& tab)
{
    // TODO: implement
}

void insertSort(std::vector<int>& tab)
{
    // TODO: implement
}

void heapSort(std::vector<int>& tab)
{
   for (int i = tab.size()/2-1; i >= 0; i--)
   heapify(tab, tab.size(), i);
  
   for (int i=tab.size()-1; i>=0; i--)
    {
      std::swap(tab[0], tab[i]);
  
      heapify(tab, i, 0);
    }
}

void heapify(std::vector<int>& tab, int size, int root)
{
    int child_left, child_right, largest;
    child_left = 2*root; 
    child_right = 2*root+1;
    

    if(child_left < size && tab[child_left] > tab[root])
    largest=child_left;
    else
    largest=root;
    
    if(child_right < size && tab[child_right] > tab[largest])
    largest=child_right;

    if(largest!=root)
    {
      std::swap(tab[root], tab[largest]);
      heapify(tab, size, largest);
    }

}


void quickSort(std::vector<int>& tab, int left, int right)
{
    auto pivot=tab[(left+right)/2];
    int i = left;
    int j = right;
    do
    {
        while(tab[i] < pivot)
        i++;
       
        while(tab[j] > pivot)
        j--;
       
        if(i <= j)
        {
            std::swap(tab[i], tab[j]); 
            i++;
            j--;
        }

    } while(i <= j);
   
    if(left < j) 
    quickSort(tab, left, j);
   
    if(right > i) 
    quickSort(tab, i, right);
}

void quickSort_worst(std::vector<int>& tab, int left, int right)
{
    auto pivot=tab[left];
    int i = left;
    int j = right;
    do
    {
        while(tab[i] < pivot)
        i++;
       
        while(tab[j] > pivot)
        j--;
       
        if(i <= j)
        {
            std::swap(tab[i], tab[j]); 
            i++;
            j--;
        }

    } while(i <= j);
   
    if(left < j) 
    quickSort(tab, left, j);
   
    if(right > i) 
    quickSort(tab, i, right);
}

void mergeSort(std::vector<int>& tab, int left, int right)
{
    if(right <= left) 
    return;

    int pivot = (left+right)/2;

    mergeSort(tab, left, pivot);
    mergeSort(tab, pivot+1, right);
    merge(tab, left, pivot, right);
}

void merge(std::vector<int>& tab, int left, int pivot, int right)
{
    int size_left, size_right;
    size_left = pivot-left+1;
    size_right = right-pivot;

    std::vector<int> left_tab(size_left), right_tab(size_right);

    for (int i = 0; i < size_left; i++)
    left_tab[i] = tab[left+i];

    for (int i = 0; i < size_right; i++)
    right_tab[i] = tab[pivot+1+i];

    int i=0, j=0, k=left;

    while(i < size_left && j < size_right) 
    { 
        if(left_tab[i] <= right_tab[j]) 
        {
            tab[k] = left_tab[i];
            i++;
        }
        else
        {
            tab[k] = right_tab[j];
            j++;
        }
        k++;
    }

    while (i < size_left) 
    {
        tab[k] = left_tab[i];
        i++;
        k++;
    }

    while (j < size_right) 
    {
        tab[k] = right_tab[j];
        j++;
        k++;
    }
}

void bucketSort(std::vector<int>& tab)
{
    // TODO: implement
}
