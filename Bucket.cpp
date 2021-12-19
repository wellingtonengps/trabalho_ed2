#include "Bucket.h"
#include <string>

using namespace std;

Bucket::Bucket(int size) {
    this->tam = size;
    itemList.reserve(size);
}

Bucket::~Bucket() {
    Cell *cell;
    for(int i = 0; i < this->getTotalSize(); i++){
        cell =  this->get(i);
        if(cell!=NULL){
            delete cell;
        }
    }
}

void Bucket::inserir(Cell* cell) {

    if(itemList.size()>=this->tam){
        overflowArea.insereFinal(cell);
    }else{
        itemList.push_back(cell);
    }
}

int Bucket::getTotalSize() {
    return itemList.size() + overflowArea.getSize();
}

Cell* Bucket::get(int k){
    if(k<tam){
        return itemList[k];
    }
    else{
       return overflowArea.get(k-tam);
    }
}

Cell* Bucket::getRemove(int k){
    Cell* cell=NULL;

    if(k<tam){
        cell = itemList[k];
        itemList[k]=NULL;
    }
    else{
        Node* node = overflowArea.getNode(k-tam);
        cell=node->getInfo();
        node->setInfo(NULL);
    }

    return cell;
}

Cell* Bucket::busca(string val){
    Cell *cell;
    for(int i = 0; i < this->getTotalSize(); i++){
        cell =  this->get(i);
        if(val == cell->getCellInfo()){
            return cell;
        }
    }
    return NULL;
}

