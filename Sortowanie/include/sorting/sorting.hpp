#ifndef SORTING_HPP_
#define SORTING_HPP_

#include <vector>

void heapSort(std::vector<int>& tab);
void heapify(std::vector<int>& tab, int size, int root);
void quickSort(std::vector<int>& tab, int left, int right);
void mergeSort(std::vector<int>& tab, int left, int right);
void merge(std::vector<int>& tab, int left, int pivot, int right);


#endif /* SORTING_HPP_ */
