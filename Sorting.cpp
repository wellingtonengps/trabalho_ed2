
#include "Sorting.h"
#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

Sorting::Sorting() {
    this->lastAlgorithmComparisonCount=0;
    this->lastAlgorithmSwapCount=0;

}

Sorting::~Sorting() {

}

int Sorting::getLastAlgorithmComparisonCount(){
    return this->lastAlgorithmComparisonCount;
}

int Sorting::getlastAlgorithmSwapCount() {
    return this->lastAlgorithmSwapCount;
}

void Sorting::resetCount(){
    this->lastAlgorithmComparisonCount=0;
    this->lastAlgorithmSwapCount=0;
}

void Sorting::trocar(vector<Review*> &A, int a, int b){
    Review* aux = A[a];
    A[a] = A[b];
    A[b] = aux;

    lastAlgorithmSwapCount++;
}

int key(Review* r){
    return r->getUpvotes();
}

void Sorting::maxHeapify(vector<Review*> &A, int i, int n){
    int left = 2*i+1;
    int right = 2*i+2;
    int m;

    if(left < n && key(A[left]) > key(A[i])){
        m = left;
    }
    else{
        m=i;
    }

    if(right<n && key(A[right]) > key(A[m])){
        m =right;
    }

    if(m !=i){
        trocar(A, i, m);
        maxHeapify(A,m,n);
    }

    lastAlgorithmComparisonCount+=2;
}



void Sorting::buildHeap(vector<Review*> &V, int n){

    for(int i=n/2; i>= 0; i--){
       maxHeapify(V, i, n);
    }

}

void printList(vector<Review*> &A){
    for(int i=0; i<A.size(); i++){
        cout<< key(A[i]) <<", ";
    }

    cout << endl;
}

void Sorting::heapSort(vector<Review*> &A){
    resetCount();
    int n = A.size();
    printList(A);
    buildHeap(A, n);

    //printList(A);
    //cout <<endl;
    for(int i=n-1; i>=0; i--){
        trocar(A, 0, i);
       // printList(A);
        maxHeapify(A, 0, i-1);
        //printList(A);
        //cout <<endl;

    }

    printList(A);

}

void Sorting::countingSort(vector<Review*> &A){
    int i;
    int largest = A[0]->getUpvotes();

    vector<Review*> tmp(A.size());

    for(i = 1; i < A.size(); i++){
        if(largest < A[i]->getUpvotes()){
            largest = A[i]->getUpvotes();
        }
        lastAlgorithmComparisonCount++;
    }

    vector<int> count(largest+1, 0);

    for(i = 0; i < A.size(); i++){
        count [A[i]->getUpvotes()]++;
        lastAlgorithmComparisonCount++;
    }

    for(i = 1; i <= largest; i++){
        count[i] = count[i-1] + count[i];
        lastAlgorithmComparisonCount++;
    }

    for(i = A.size()-1; i >= 0; i--){
        tmp[count[A[i]->getUpvotes()]-1] = A[i];
        count[A[i]->getUpvotes()]--;
        lastAlgorithmSwapCount++;
    }

    for(i = 0; i < A.size(); i++){
        A[i] = tmp[i];
    }
}

void Sorting::countingSortRadix(vector<Review*> &A){
    /*int i;
}
    int maxNumb = 10;
    int count[maxNumb];

    vector<Review*> tmp(A.size());

    for (int i = 0; i < maxNumb; ++i)
        count[i] = 0

    for(i = 1; i < A.size(); i++){
        count[(A[i]->getUpvotes() / place) % 10]++;

        vector<int> count(largest+1, 0);

        for(i = 0; i < maxNumb; i++){
            count[i] += count [A[i]->getUpvotes() - 1];
        }

        for(i = A.size() - 1; i >= 0; i--){
            tmp[count[(A[i]->getUpvotes() / place)%10 ] -1] = A[i];
            count[(A[i]->getUpvotes() / place ) % 10]--;
        }

        for(i = 0; i < A.size(); i++){
            A[i] = tmp[i];
        }

        printList(A);*/
}

void Sorting::radixSort(vector<Review*> &V) {
    int max = V[0]->getUpvotes();

    for(int i ;i<max;i++){
        if(V[i]->getUpvotes()>max){
            max = V[i]->getUpvotes();
        }

    }
    for (int place = 1; max / place > 0; place *= 10){}
        //countingSortRadix(V,place);
}

int Sorting::particiona(vector<Review*> &B, int min, int max)
{
    Review* pivot = B[max];
    int i = (min - 1);

    for (int j = min; j <= max - 1; j++)
    {
        lastAlgorithmComparisonCount++;
        if (key(B[j]) < key(pivot))
        {
            i++;
            trocar(B, i, j);

        }

    }
    trocar(B, i+1, max);
    return (i + 1);
}


void Sorting::quickSort(vector<Review*> &B, int min, int max)
{
    lastAlgorithmComparisonCount++;
    if (min < max)
    {

        int pivot = particiona(B, min, max);

        quickSort(B, min, pivot - 1);
        quickSort(B, pivot + 1, max);
    }

}

void Sorting::quickSort(vector<Review *> &B) {
    resetCount();
    quickSort(B, 0, B.size()-1);
    printList(B);
}