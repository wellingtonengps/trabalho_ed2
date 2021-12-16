#include "LinearHashTable.h"
#include <string>
#include <math.h>
#include<iostream>
#include<algorithm>

using namespace  std;

LinearHashTable::LinearHashTable() {
    g=0;
    splitPointer=0;
    bucketList.reserve(bucketCount);

    for(int i=0; i<bucketCount; i++){
        bucketList.push_back(new Bucket());
    }

}

LinearHashTable::~LinearHashTable() {
//todo: destruir componentes alocados dinamicamente
}

void LinearHashTable::insert(string val) {

    bucketList[hash(val)]->inserir(val);

}

void LinearHashTable::splitBucket() {

    bucketList.push_back(new Bucket());

    //todo: redistribuir valores do balde dividido

    if(splitPointer==bucketList.size()/2){
        splitPointer=0;
        g++;
    }
}

int LinearHashTable::hash(string val) {


    val.erase(remove(val.begin(), val.end(), '.'), val.end());
    int k = stoi(val);
    int n = bucketCount*pow(2, g+1);

    int h = k % (int)(n * pow(2, this->g));

    if(h<splitPointer){
        h = k % (int)(n * pow(2, this->g+1));
    }

    return h;
}
