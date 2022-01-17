#ifndef TRABALHO_ED2_VPNODE_H
#define TRABALHO_ED2_VPNODE_H
#include "ReviewData.h"

using namespace std;

class VPNode {
public:
    VPNode(ReviewData *data)               {cor = true; info = data; esq = dir = pai = NULL; };
    ~VPNode()              { };
    void setEsq(VPNode *p) { esq = p; if(p!=NULL)p->setPai(this);};
    void setInfo(ReviewData *data) { info = data; };
    void setDir(VPNode *p) { dir = p; if(p!=NULL)p->setPai(this);};
    VPNode* getEsq()       { return this->esq; };
    ReviewData* getInfo()         { return info; };
    VPNode* getDir()       { return this->dir; };
    void setPai(VPNode *paiInfo){pai = paiInfo;};
    VPNode* getPai(){return pai;};
    void setCor(bool corInfo){cor = corInfo;};
    bool getCor(){return cor;};
private:
    VPNode* esq; // ponteiro para o filho a esquerda
    ReviewData *info;   // informa��o do No (int)
    VPNode* dir; // ponteiro para o filho a direita
    VPNode* pai;
    bool cor;
};

#endif //TRABALHO_ED2_VPNODE_H
