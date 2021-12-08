
#include "Sorting.h"
#include <iostream>


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

void printList(vector<Review*> A){
    for(int i=0; i<A.size(); i++){
        cout<< key(A[i]) <<", ";
    }

    cout << endl;
}

void Sorting::heapSort(vector<Review*> &A){
    int n = A.size();
    printList(A);
    buildHeap(A, n);

    printList(A);
    cout <<endl;
    for(int i=n-1; i>=0; i--){
        trocar(A, 0, i);
        printList(A);
        maxHeapify(A, 0, i-1);
        printList(A);
        cout <<endl;

    }

    printList(A);

}
