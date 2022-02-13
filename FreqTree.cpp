//
// Created by welli on 2/12/2022.
//

#include "FreqTree.h"
#include <vector>
#include <iostream>


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

void auxDecodificacao(FreqNode* node, string cod, vector<pair<char, string>> &v){


    if(node->getInfo()!='\0'){
        pair<char, string> p(node->getInfo(), cod);
        v.push_back(p);
    }
    else{
        auxDecodificacao(node->getEsq(), cod+"0", v);
        auxDecodificacao(node->getDir(), cod+"1", v);
    }

}

vector<pair<char, string>> FreqTree::gerarTabela() {

    vector<pair<char, string>> v;

    if(this->raiz != nullptr){
        auxDecodificacao(this->raiz, "", v);
    }

    for(int i=0; i<v.size(); i++){
        cout << "("<< v[i].first <<", "<<v[i].second << "), ";
    }
    cout << endl;

    return v;
}




