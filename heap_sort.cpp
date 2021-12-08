#include <iostream>
#include <cstdlib>
#include <time.h>

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
    int left = 2*i;
    int right = 2*i+1;
    int m;

    if(left <= n && A[left] > A[i]){
        m = left;
    }
    else{
        m=i;
    }

    if(right<=n && A[right] > A[m]){
        m =right;
    }

    if(m !=i){
        trocar(A, i, m);
        maxHeapify(A,m,n);
    }
}



void buildHeap(int V[], int n){

    for(int i=n/2; i>= 1; i--){
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

    printList(A, n+1);
    cout <<endl;
    for(int i=n; i>=2; i--){
        trocar(A, 1, i);
        printList(A, n+1);
        maxHeapify(A, 1, i-1);
        printList(A, n+1);
        cout <<endl;

    }
}


/*int main(){
    int arraySize = 11;
    int listSize = arraySize-1;
    int keys[11]={0, 4, 2, 6, 7, 5, 8, 9, 3, 1, 4};
    keys[0]=0;
    printList(keys, arraySize);
    heapSort(keys,  listSize);
    printList(keys, arraySize);

}*/
