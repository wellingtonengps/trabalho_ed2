
#include "Sorting.h"
#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

Sorting::Sorting() {

}

Sorting::~Sorting() {

}

void trocar(vector<Review*> &A, int a, int b){
    Review* aux = A[a];
    A[a] = A[b];
    A[b] = aux;
}

int key(Review* r){
    return r->getUpvotes();
}

void maxHeapify(vector<Review*> &A, int i, int n){
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
}



void buildHeap(vector<Review*> &V, int n){

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
    }

    for(i = 0; i < A.size(); i++){
        A[i] = tmp[i];
    }

    printList(A);
}

void Sorting::radixSort(vector<Review *> &V) {

}
