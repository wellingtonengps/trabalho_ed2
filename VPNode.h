#ifndef TRABALHO_ED2_VPNODE_H
#define TRABALHO_ED2_VPNODE_H

class VPNode {
private:
    VPNode *esq;
    VPNode *dir;
    VPNode *pai;
    bool cor;
    int info;
public:
    VPNode(int info);
    ~VPNode();
    void setEsq(VPNode *p);
    void setInfo(int info);
    void setDir(VPNode *p);
    void setCor(bool infoCor);
    void setPai(VPNode *p);
    VPNode* getPai();
    VPNode* getEsq();
    int getInfo();
    VPNode* getDir();
    bool getCor();
};

#endif //TRABALHO_ED2_VPNODE_H
