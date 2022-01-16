#include <iostream>
#include "VPTree.h"
#include <cmath>

using namespace std;

VPTree::VPTree()
{
    raiz = NULL;
}

bool VPTree::vazia()
{
    return raiz == NULL;
}

VPNode* getAvo(VPNode *p){
    if((p != NULL) && (p->getPai() != NULL)){
        return p->getPai()->getPai();
    }
    else {
        return NULL;
    }
}

VPNode* getTio(VPNode *p){
    VPNode *avo = getAvo(p);

    if(avo == NULL){
        return NULL;
    }
    else if(p->getPai() == avo->getEsq()){
        return avo->getDir();
    }
    else {
        return avo->getEsq();
    }
}

void VPTree::rotacaoSimplesEsq(VPNode *p){

    VPNode *q = p->getDir();
    VPNode *paiAnterior = p->getPai();
    p->setDir(q->getEsq());
    q->setEsq(p);

    //****
    if(paiAnterior!=NULL){
        if(paiAnterior->getDir()==p){
            paiAnterior->setDir(q);
        }else{
            paiAnterior->setEsq(q);
        }
    }
    //****

    if(p == raiz){
        raiz = q;
    }

    /*
    VPNode *q = p->getDir();

    p->setDir(q->getEsq());

    if (p->getDir() != NULL)
        p->getDir()->setPai(p);

    q->setPai(p->getPai());

    if (p->getPai() == NULL)
        raiz = q;

    else if (p == p->getPai()->getEsq())
        p->getPai()->setEsq(q);

    else
        p->getPai()->setDir(q);

    q->setEsq(p);
    p->setPai(q);
    */
}

void VPTree::rotacaoSimplesDir(VPNode *p){


    VPNode *q = p->getEsq();
    VPNode *paiAnterior = p->getPai();
    p->setEsq(q->getDir());
    q->setDir(p);

    //*****
    if(paiAnterior!=NULL){
        if(paiAnterior->getDir()==p){
            paiAnterior->setDir(q);
        }else{
            paiAnterior->setEsq(q);
        }
    }
    //*****

    if(p == raiz){
        raiz = q;
    }

    /*

    VPNode *q = p->getEsq();

    p->setEsq(q->getDir());

    if (p->getEsq() != NULL)
        p->getEsq()->setPai(p);

    q->setPai(p->getPai());

    if (p->getPai() == NULL)
        raiz = q;

    else if (p == p->getPai()->getDir())
        p->getPai()->setDir(q);

    else
        p->getPai()->setEsq(q);

    q->setDir(p);
    p->setPai(q);
 */
}


void swapCor(VPNode *x, VPNode *y){
    bool aux;

    aux = x->getCor();
    x->setCor(y->getCor());
    y->setCor(aux);
}

VPNode* VPTree::auxInsere(VPNode *raiz, VPNode *p)
{
    if(raiz == NULL)
    {
        return p;
    }

    if(p->getInfo() < raiz->getInfo()) { //se for menor que a raiz, vai para a esquerda
         raiz->setEsq(auxInsere(raiz->getEsq(),p));
         raiz->getEsq()->setPai(raiz);
    }
    else { //se for menor que a raiz, vai para a direita
        raiz->setDir(auxInsere(raiz->getDir(), p));
        raiz->getDir()->setPai(raiz);

    }

    return raiz;
}



void VPTree::balancemento(VPNode *p){

    VPNode *pai_p = p->getPai();
    VPNode *avo_p = NULL;
    VPNode *tio_p = NULL;

    avo_p = getAvo(p);
    tio_p = getTio(p);

    //caso 2:
    if((pai_p != NULL && tio_p != NULL)){
        if(pai_p->getCor() == true && tio_p->getCor() == true){
            pai_p->setCor(!pai_p->getCor());
            tio_p->setCor(!tio_p->getCor());
            avo_p->setCor(!avo_p->getCor());
        }
    }

    //caso 3:
    if((pai_p != NULL && avo_p != NULL && tio_p == NULL && pai_p->getCor())){


        if(pai_p==avo_p->getDir() && p == pai_p->getEsq()){

            p->setCor(!p->getCor());
            avo_p->setCor(!avo_p->getCor());

            rotacaoSimplesDir(pai_p);
            rotacaoSimplesEsq(avo_p);
        }
        else if(pai_p==avo_p->getEsq() && p == pai_p->getDir()){

            p->setCor(!p->getCor());
            avo_p->setCor(!avo_p->getCor());

            rotacaoSimplesEsq(pai_p);
            rotacaoSimplesDir(avo_p);
        }
        else{
            pai_p->setCor(!pai_p->getCor());
            avo_p->setCor(!avo_p->getCor());

            if(tio_p == avo_p->getEsq()){ //caso A: rotacao esquerda
                rotacaoSimplesEsq(avo_p);
                //balancemento(raiz, p);
            }else{
                rotacaoSimplesDir(avo_p); //caso B: rotacao direita
                //balancemento(raiz, p);
            }
        }

    }

    //caso 4: rotacao dupla esquerda ou direita
    //dupla esquerda: pai vermelho e tio preto;
   /* if(pai_p != NULL && tio_p == NULL ){

        if(pai_p->getCor() == true && tio_p == NULL){
            p->setCor(!p->getCor());
            avo_p->setCor(!avo_p->getCor());

            rotacaoSimplesDir(avo_p);
            rotacaoSimplesEsq(avo_p);
        }
    }*/

    //caso 1:
    raiz->setCor(false);
}

void VPTree::insere(int val)
{
    VPNode *p = new VPNode(val);

    raiz = auxInsere(raiz, p);

    balancemento(p);

    imprime();
}

bool VPTree::busca(int val)
{
    return auxBusca(raiz, val);
}

bool VPTree::auxBusca(VPNode *p, int val)
{
    //casos base
    if(p == NULL)
        return false;
    else if(p->getInfo() == val)
        return true;

        //casos recurivos
    else if(val < p->getInfo())
        return auxBusca(p->getEsq(), val);
    else
        return auxBusca(p->getDir(), val);
}

void VPTree::imprime()
{
    imprimePorNivel(raiz, 0);
    cout << endl;
    imprimePorNivelCor(raiz, 0);

}

void VPTree::imprimePorNivel(VPNode *p, int nivel) //pre-ordem
{
    ///imprir a arvore em-oderm faz com que a impress�o fique em ordem crescente.

    if(p != NULL)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->getInfo() << endl;
        imprimePorNivel(p->getEsq(), nivel+1);
        imprimePorNivel(p->getDir(), nivel+1);
    }
}

void VPTree::imprimePorNivelCor(VPNode *p, int nivel) //pre-ordem
{
    ///imprir a arvore em-oderm faz com que a impress�o fique em ordem crescente.

    if(p != NULL)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->getCor() << endl;
        imprimePorNivelCor(p->getEsq(), nivel+1);
        imprimePorNivelCor(p->getDir(), nivel+1);
    }
}

VPTree::~VPTree()
{
    raiz = libera(raiz);
}

VPNode* VPTree::libera(VPNode *p)
{
    if(p != NULL)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = NULL;
    }
    return p;
}

VPNode* VPTree::getRaiz(){
    return raiz;
}