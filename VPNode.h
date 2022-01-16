#ifndef TRABALHO_ED2_VPNODE_H
#define TRABALHO_ED2_VPNODE_H

class VPNode {
public:
    VPNode(int data)               {cor = true; info = data; esq = dir = pai = NULL; };
    ~VPNode()              { };
    void setEsq(VPNode *p) { esq = p; if(p!=NULL)p->setPai(this);};
    void setInfo(int val) { info = val; };
    void setDir(VPNode *p) { dir = p; if(p!=NULL)p->setPai(this);};
    VPNode* getEsq()       { return this->esq; };
    int getInfo()         { return info; };
    VPNode* getDir()       { return this->dir; };
    void setPai(VPNode *paiInfo){pai = paiInfo;};
    VPNode* getPai(){return pai;};
    void setCor(bool corInfo){cor = corInfo;};
    bool getCor(){return cor;};
private:
    VPNode* esq; // ponteiro para o filho a esquerda
    int info;   // informa��o do No (int)
    VPNode* dir; // ponteiro para o filho a direita
    VPNode* pai;
    bool cor;
};

#endif //TRABALHO_ED2_VPNODE_H
