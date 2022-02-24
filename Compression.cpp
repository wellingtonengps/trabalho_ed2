//
// Created by welli on 2/12/2022.
//

#include "Compression.h"
#include "FreqTree.h"
#include "FileIO.h"
#include "Metricas.h"
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
    //incrementa comparações
    Metricas::incrementComparisonCount(1);

    return i->getRaiz()->getFreq() > j->getRaiz()->getFreq();
}

void Compression::gerarArvore(string data) {

    vector<FreqTree*> trees;
    this->dataSize = data.size();

    for(int i=0; i<data.size(); i++){
        FreqTree* busca = auxBusca(trees, data[i]);

        if(busca== nullptr){
            trees.push_back(new FreqTree(data[i]));
        }else{
            busca->getRaiz()->incrementaFreq(1);
        }
    }

    sort(trees.begin(), trees.end(), comparaArvores);
    //print(trees);

    //FreqTree* primeira = trees.back();
    //trees.pop_back();
    while (trees.size()>1){
        FreqTree* primeira = trees.back();
        trees.pop_back();
        FreqTree* segunda = trees.back();
        //trees.pop_back();
        segunda->unir(primeira->getRaiz());
        primeira->setRaiz(nullptr);
        delete primeira;

        sort(trees.begin(), trees.end(), comparaArvores);
       // print(trees);

    }

    this->freqTree = trees.front();
    //imprime(primeira->getRaiz());
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

string Compression::decompress(string bin){
    return this->freqTree->decodificar(bin);
}


string Compression::intToBinaryString(unsigned int number){
    string result(32, '0');
    unsigned int num = number;
    for(int i=31; i>= 0; i--){
        result.replace(i, 1, to_string(num%2));
        num = num/2;
    }
    return result;
}

int Compression::readBinaryStringToInt(string bin){
    unsigned int result=0;
    int size = (int)bin.size();

    for(int i= size; i>0; i--){
        int active = (bin[i-1] == '1');
        result += active*(int)pow(2, size-i);
    }
    return result;
}

char Compression::readBinaryStringToChar(string bin){
    int result=0;
    int size = (int)bin.size();

    for(int i= size; i>0; i--){
        int active = (bin[i-1] == '1');
        result += active*(int)pow(2, size-i);
    }
    return (unsigned char)result;
}

string Compression::charToBinaryString(unsigned char c){
    string result(8, '0');
    int num = (int)c;
    for(int i=7; i>= 0; i--){
        result.replace(i, 1, to_string(num%2));
        num = num/2;
    }

    return result;
}

string Compression::codedCharsToBynaryString(string codedString){
    string result;

    for(int i=0; i<codedString.size(); i++){
        result+= charToBinaryString(codedString[i]);
    }

    return result;
}

string Compression::readCompressedText(string codedString){
    string compressedText = codedString.substr(4, codedString.size()-4);
    string sizeHeader = codedString.substr(0,4);
    int size = readBinaryStringToInt(codedCharsToBynaryString(sizeHeader));
    string result = codedCharsToBynaryString(compressedText).substr(0, size);
    return result;
}

//codifica uma string com 1 e 0 em caracteres e coloca em outra string
string Compression::readBinaryString(string bin){
    string result;
    int numCompletar = ((bin.size()/8)+1)*8 - bin.size();
    string padding(numCompletar, '0');
    string sizeHeader = intToBinaryString(bin.size());
    string paddedString = sizeHeader + bin + padding;
    // cout << "padded string: "<< paddedString<<endl;

    for(int i= 0; i<paddedString.size(); i+=8){
        result+= readBinaryStringToChar(paddedString.substr(i, 8));
    }
    return result;
}

float Compression::taxaCompressao(string data){

    float taxa = ((this->dataSize - data.size() ) / (float)this->dataSize) * 100;

    return taxa;
}