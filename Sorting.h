//
// Created by patri on 08/12/2021.
//

#ifndef TRABALHO_SORTING_H
#define TRABALHO_SORTING_H

#include "Review.h"
#include "Cell.h"
#include <vector>


class Sorting {

private:
    int lastAlgorithmComparisonCount;
    int lastAlgorithmSwapCount;

public:
    Sorting();
    ~Sorting();
    void heapSort(vector<Review*> &V);
    void countingSortRadix(vector<Review*> &V);
    void countingSort(vector<Review*> &V);
    void countingSortCells(vector<Cell*> &A);
    void radixSort(vector<Review*> &V);
    void quickSort(vector<Review*> &B, int min, int max);
    void quickSort(vector<Review*> &B);
    int getLastAlgorithmComparisonCount();
    int getlastAlgorithmSwapCount();
    void incrementComparisonCount();
    void incrementSwapCount();
    void maxHeapify(vector<Review*> &A, int i, int n);
    void trocar(vector<Review*> &A, int a, int b);
    void buildHeap(vector<Review*> &V, int n);
    int particiona(vector<Review*> &B, int min, int max);
    void resetCount();
    string printCellList(vector<Cell*> &A);
};


#endif //TRABALHO_SORTING_H
