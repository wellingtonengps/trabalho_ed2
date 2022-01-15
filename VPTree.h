#ifndef TRABALHO_ED2_VPTREE_H
#define TRABALHO_ED2_VPTREE_H
#include "VPNode.h"

class VPTree {
public:
    VPTree();
    ~VPTree();
    bool vazia(); // verifica se a �rvore est� vazia
    bool busca(int val);
    void insere(int val);
    void remove(int val);
    void imprime();
    VPNode* getRaiz();
private:
    void balancemento(VPNode *p);
    void rotacaoSimplesEsq(VPNode *p);
    void rotacaoSimplesDir(VPNode *p);
    VPNode* raiz; // ponteiro para o No raiz da �rvore
    bool auxBusca(VPNode *p, int val);
    VPNode* auxInsere(VPNode *raiz, VPNode *p);
    VPNode* auxRemove(VPNode *p, int val);
    VPNode* menorSubArvDireita(VPNode *p);
    void imprimePorNivel(VPNode* p, int nivel);
    void imprimePorNivelCor(VPNode *p, int nivel);
    VPNode* libera(VPNode *p);
};


#endif //TRABALHO_ED2_VPTREE_H
