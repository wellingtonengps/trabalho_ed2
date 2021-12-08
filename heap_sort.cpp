#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "Review.h"
#include "Sorting.h"

using namespace std;



void initialize(int V[], int size){
    srand (time(0));

   // cout<<"Inicializando vetor: ";

    for(int i=0; i<size; i++){
        int numRand = rand() % 10;
        V[i] = numRand;

       // cout << numRand << ", ";
    }

    cout << endl;

}

void trocar(int A[], int a, int b){
    int aux = A[a];
    A[a] = A[b];
    A[b] = aux;
}

void maxHeapify(int A[], int i, int n){
    int left = 2*i+1;
    int right = 2*i+2;
    int m;

    if(left < n && A[left] > A[i]){
        m = left;
    }
    else{
        m=i;
    }

    if(right<n && A[right] > A[m]){
        m =right;
    }

    if(m !=i){
        trocar(A, i, m);
        maxHeapify(A,m,n);
    }
}



void buildHeap(int V[], int n){

    for(int i=n/2; i>= 0; i--){
        maxHeapify(V, i, n);
    }

}

void printList(int V[], int size){
    for(int i=0; i<size; i++){
        cout<< V[i] <<", ";
    }

    cout << endl;
}

void heapSort(int A[], int n){
    buildHeap(A, n);

    printList(A, n);
    cout <<endl;
    for(int i=n-1; i>=0; i--){
        trocar(A, 0, i);
        printList(A, n);
        maxHeapify(A, 0, i-1);
        printList(A, n);
        cout <<endl;

    }
}


int main(){
    int arraySize = 11;
    int listSize = arraySize;
    int keys[11]={7, 4, 2, 6, 7, 5, 8, 9, 3, 1, 4};

    /*printList(keys, arraySize);
    heapSort(keys,  listSize);
    printList(keys, arraySize);*/

    vector<Review*> reviews;

    for(int i=0; i<arraySize; i++ ){
        Review* review = new Review();
        review->setUpvotes(keys[i]);
        reviews.push_back(review);
    }

    Sorting sorting = Sorting();
    sorting.heapSort(reviews);

    for(int i=0; i<reviews.size(); i++ ){
        delete reviews[i];
    }

}
