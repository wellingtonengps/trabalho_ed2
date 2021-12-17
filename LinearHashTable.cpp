#include "LinearHashTable.h"
#include <string>
#include <math.h>
#include<iostream>
#include<algorithm>

using namespace  std;

LinearHashTable::LinearHashTable(float maxFatorCarga) {
    this->maxFatorCarga=maxFatorCarga;
    g=0;
    splitPointer=0;
    nChaves=0;
    bucketList.reserve(originalBucketCount);

    for(int i=0; i < originalBucketCount; i++){
        bucketList.push_back(new Bucket(bucketSize));
    }

}

LinearHashTable::~LinearHashTable() {
    for(int i=0; i < originalBucketCount; i++){
        delete bucketList[i];
    }

}

void LinearHashTable::insert(string val) {

    int h = hash(val);
    cout<< "val: "<< val<< " balde: "<<h<<endl;
    bucketList[h]->inserir(val);
    nChaves++;

    //cout <<"FC: " << fatorCarga()<<endl;
    if(fatorCarga()>=maxFatorCarga){
        cout << "FC: "<< fatorCarga() << " >= "<<maxFatorCarga<<endl;
        splitBucket();
    }

}

void LinearHashTable::reinsert(string val) {

    int h = hash(val);
    cout<< "reinserindo val: "<< val<< " balde: "<<h<<endl;
    bucketList[h]->inserir(val);
}



void LinearHashTable::splitBucket() {

    if(splitPointer==bucketList.size()/2){
        splitPointer=0;
        g++;
    }

    bucketList.push_back(new Bucket(bucketSize));
    cout << "QNTD de baldes: "  << bucketList.size() << endl;
    Bucket* current = bucketList[splitPointer];
    bucketList[splitPointer] = new Bucket(bucketSize);
    //nChaves-=current->getTotalSize();


    //redistribuindo valores do balde dividido
    cout<< "split balde "<< splitPointer<<endl;
    for(int i=0; i<current->getTotalSize(); i++){
        string str  =  current->get(i);
        reinsert(str);
    }

    splitPointer++;

    delete current;

}
float LinearHashTable::fatorCarga(){
    int N = bucketList.size();
    int M = bucketSize;

    float fatorC = nChaves/(float)(N*M);
    return fatorC;
}

int LinearHashTable::hash(string val) {

   // cout << "val: "<< val<<endl;
    val.erase(remove(val.begin(), val.end(), '.'), val.end());

    int k = stoi(val);
    int n = originalBucketCount /** pow(2, g)*/;

    int h = k % (int)(n * pow(2, this->g));

    if(h<splitPointer){
        h = k % (int)(n * pow(2, this->g+1));
    }

    return h;
}

void LinearHashTable::printTable(){
    for(int i=0; i < bucketList.size(); i++){
        cout << i << ": ";
        for(int j=0; j<bucketList[i]->getTotalSize(); j++){
            cout << bucketList[i]->get(j) << ", ";
        }
        cout << endl;
    }
}
