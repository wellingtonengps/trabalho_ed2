#include "Bucket.h"
#include <string>

using namespace std;

Bucket::Bucket(int size) {
    this->tam = size;
    itemList.reserve(size);
}

Bucket::~Bucket() {

}

void Bucket::inserir(string val) {

    if(itemList.size()>=this->tam){
        overflowArea.insereFinal(val);
    }else{
        itemList.push_back(val);
    }
}

int Bucket::getTotalSize() {
    return itemList.size() + overflowArea.getSize();
}

string Bucket::get(int k){
    if(k<tam){
        return itemList[k];
    }
    else{
       return overflowArea.get(k-tam);
    }
}
