#include "Bucket.h"
#include <string>

using namespace std;

Bucket::Bucket() {
    itemList.reserve(4);
}

Bucket::~Bucket() {

}

void Bucket::inserir(string val) {
    if(itemList.size()==this->tam){
        overflowArea.insereFinal(val);
    }else{
        itemList.push_back(val);
    }
}
