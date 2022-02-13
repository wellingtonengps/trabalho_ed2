//
// Created by welli on 2/12/2022.
//

#include "Compression.h"
#include "FreqTree.h"
#include <vector>
#include <iostream>
#include <bits/stdc++.h>



FreqTree* auxBusca(vector<FreqTree*> v, char data){

    for(int i = 0; i < v.size(); i++){
        if(v[i]->getRaiz()->getInfo() == data){
            return v[i];
        }
    }

    return nullptr;
}

void imprimePorNivel(FreqNode *p, int nivel) //pre-ordem
{
    ///imprir a arvore em-oderm faz com que a impress�o fique em ordem crescente.

    if(p != nullptr)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->getInfo() << " ("<< p->getFreq()<<") "<< endl;
        imprimePorNivel(p->getEsq(), nivel+1);
        imprimePorNivel(p->getDir(), nivel+1);
    }
}

void imprime(FreqNode* raiz)
{
    imprimePorNivel(raiz, 0);
    cout << endl;

}

void print(vector<FreqTree*> v){
    for(int i=0; i<v.size(); i++){
        cout<< v[i]->getRaiz()->getInfo() << " ( " <<v[i]->getRaiz()->getFreq() << "), ";
    }
    cout <<endl;
}

bool comparaArvores(FreqTree* i, FreqTree* j){
    return i->getRaiz()->getFreq() > j->getRaiz()->getFreq();
}

void Compression::gerarArvore(string data) {

    vector<FreqTree*> trees;
    FreqTree* novaArvore;
    for(int i=0; i<data.size(); i++){
        FreqTree* busca = auxBusca(trees, data[i]);

        if(busca== nullptr){
            trees.push_back(new FreqTree(data[i]));
        }else{
            busca->getRaiz()->incrementaFreq(1);
        }
    }

    //todo: anular a raiz das arvores que não são donas da raiz após a união e deletar

    print(trees);

    sort(trees.begin(), trees.end(), comparaArvores);

    FreqTree* primeira = trees.back();
    trees.pop_back();
    while (!trees.empty()){
        FreqTree* segunda = trees.back();
        trees.pop_back();
        primeira->unir(segunda->getRaiz());
        segunda->setRaiz(nullptr);
        delete segunda;
    }

    this->freqTree = primeira;
    imprime(primeira->getRaiz());
}

void Compression::gerarTabela() {
    this->tabela=this->freqTree->gerarTabela();
}

string Compression::compress(string data) {

    string compressedData;
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < this->tabela.size(); j++){
            if(data[i] == tabela[j].first){
               compressedData.append(tabela[j].second);
            }
        }
    }

    return compressedData;
}

