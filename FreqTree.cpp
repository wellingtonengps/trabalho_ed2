//
// Created by welli on 2/12/2022.
//

#include "FreqTree.h"


FreqTree::FreqTree(char raizInicial){
    this->raiz = new FreqNode(raizInicial, 1);

}

FreqTree::~FreqTree() {
    delete raiz;
}

void FreqTree::unir(FreqNode* raiz){
    FreqNode* novaRaiz = new FreqNode('\0', raiz->getFreq() + this->raiz->getFreq());
    if(raiz->getFreq() >= this->raiz->getFreq()){
        novaRaiz->setDir(raiz);
        novaRaiz->setEsq(this->raiz);
    }else{
        novaRaiz->setDir(this->raiz);
        novaRaiz->setEsq(raiz);
    }

    this->raiz = novaRaiz;
}

FreqNode *FreqTree::getRaiz() const {
    return raiz;
}

void FreqTree::setRaiz(FreqNode *raiz) {
    FreqTree::raiz = raiz;
}



