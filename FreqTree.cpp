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

string FreqTree::decodificar(string bin){

    string result;
    FreqNode* next = this->raiz;

    if(bin.size()==1){
        result=next->getInfo();
        return result;
    }

    for(int i=0;i<bin.size();i++){
        if(bin[i]=='0'){
            next = next->getEsq();
        }if(bin[i]=='1'){
            next = next->getDir();
        }

        if(next->getInfo()!='\0'){
            result+=next->getInfo();
            next = this->raiz;
        }

    }

    return result;
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

void auxGeraTabela(FreqNode* node, string cod, vector<pair<char, string>> &v){


    if(node->getInfo()!='\0'){
        pair<char, string> p(node->getInfo(), cod);
        v.push_back(p);
    }
    else{
        auxGeraTabela(node->getEsq(), cod + "0", v);
        auxGeraTabela(node->getDir(), cod + "1", v);
    }

}



vector<pair<char, string>> FreqTree::gerarTabela() {

    vector<pair<char, string>> v;

    if(this->raiz != nullptr){
        auxGeraTabela(this->raiz, "", v);
    }

    for(int i=0; i<v.size(); i++){
        cout << "("<< v[i].first <<", "<<v[i].second << "), ";
    }
    cout << endl;

    return v;
}




