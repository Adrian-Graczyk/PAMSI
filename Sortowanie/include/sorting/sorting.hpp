#ifndef SORTING_HPP_
#define SORTING_HPP_

#include <vector>

void bubbleSort(std::vector<int>& tab);
void insertSort(std::vector<int>& tab);
void heapSort(std::vector<int>& tab);
void heapify(std::vector<int>& tab, int size, int root);
void quickSort(std::vector<int>& tab, int left, int right);
void quickSort_worst(std::vector<int>& tab, int left, int right);
void mergeSort(std::vector<int>& tab, int left, int right);
void merge(std::vector<int>& tab, int left, int pivot, int right);
void bucketSort(std::vector<int>& tab);

#endif /* SORTING_HPP_ */
