//
// Created by patri on 08/12/2021.
//

#ifndef TRABALHO_SORTING_H
#define TRABALHO_SORTING_H

#include "Review.h"
#include <vector>


class Sorting {
    public:
    Sorting();
    ~Sorting();
    void heapSort(vector<Review*> &V);
    void countingSort(vector<Review*> &V);
    void radixSort(vector<Review*> &V);
};


#endif //TRABALHO_SORTING_H
