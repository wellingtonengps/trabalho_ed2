//
// Created by welli on 2/12/2022.
//

#ifndef TRABALHO_ED2_FREQTREE_H
#define TRABALHO_ED2_FREQTREE_H
#include "FreqNode.h"
#include <string>
#include <vector>

using namespace std;

class FreqTree {

private:
    FreqNode* raiz;
public:
    FreqTree(char raizInicial);
    FreqTree(){};

    ~FreqTree();

    FreqNode *getRaiz() const;

    void setRaiz(FreqNode *raiz);

    void unir(FreqNode* raiz);
    vector<pair<char, string>> gerarTabela();
};


#endif //TRABALHO_ED2_FREQTREE_H
