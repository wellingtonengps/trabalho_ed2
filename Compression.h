//
// Created by welli on 2/12/2022.
//

#ifndef TRABALHO_ED2_COMPRESSION_H
#define TRABALHO_ED2_COMPRESSION_H
#include <string>
#include "FreqTree.h"

using namespace std;

class Compression {

private:
    FreqTree* freqTree;
    vector<pair<char, string>> tabela;
public:
    ~Compression(){if(freqTree!= nullptr)delete freqTree;}
    void gerarArvore(string data);
    string compress(string data);
    string decompress(string bin);
    void gerarTabela();
};


#endif //TRABALHO_ED2_COMPRESSION_H
