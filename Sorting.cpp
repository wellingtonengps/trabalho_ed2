
#include "Sorting.h"
#include "Cell.h"
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

string Sorting::printCellList(vector<Cell*> &A){

    string res = "";
    for(int i=A.size()-1; i>=0; i--){
        res+= A[i]->getCellInfo() +" [" + to_string(A[i]->getCount())+ "]" +"\n";
    }
    return res;
}

void Sorting::heapSort(vector<Review*> &A){
    resetCount();
    int n = A.size();
    buildHeap(A, n);

    for(int i=n-1; i>=0; i--){
        trocar(A, 0, i);
        maxHeapify(A, 0, i-1);

    }

}

void Sorting::countingSort(vector<Review*> &A){
    resetCount();
    int i;
    int largest = A[0]->getUpvotes();

    vector<Review*> tmp(A.size());

    for(i = 1; i < A.size(); i++){
        if(largest < A[i]->getUpvotes()){
            largest = A[i]->getUpvotes();
        }
    }

    vector<int> count(largest+1, 0);

    for(i = 0; i < A.size(); i++){
        count [A[i]->getUpvotes()]++;
    }

    for(i = 1; i <= largest; i++){
        count[i] = count[i-1] + count[i];
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

void Sorting::countingSortCells(vector<Cell*> &A){
    resetCount();
    int i;
    int largest = A[0]->getCount();

    vector<Cell*> tmp(A.size());

    for(i = 1; i < A.size(); i++){
        if(largest < A[i]->getCount()){
            largest = A[i]->getCount();
        }
    }

    vector<int> count(largest+1, 0);

    for(i = 0; i < A.size(); i++){
        count [A[i]->getCount()]++;
    }

    for(i = 1; i <= largest; i++){
        count[i] = count[i-1] + count[i];
    }

    for(i = A.size()-1; i >= 0; i--){
        tmp[count[A[i]->getCount()]-1] = A[i];
        count[A[i]->getCount()]--;
        lastAlgorithmSwapCount++;
    }

    for(i = 0; i < A.size(); i++){
        A[i] = tmp[i];
    }

}

int Sorting::particiona(vector<Review*> &B, int min, int max)
{
    Review* pivot = B[(min+max)/2];
    int iPivot = (min+max)/2;
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
    return (iPivot + 1);
}


void Sorting::quickSort(vector<Review*> &B, int min, int max)
{
    lastAlgorithmComparisonCount++;

    if (min < max)
    {
        cout<<min <<"-"<< max<<endl;

        int pivot = particiona(B, min, max);

        quickSort(B, min, pivot - 1);
        quickSort(B, pivot + 1, max);
        return;
    }

}

void Sorting::quickSort(vector<Review *> &B) {
    resetCount();
    quickSort(B, 0, (int)B.size()-1);
}