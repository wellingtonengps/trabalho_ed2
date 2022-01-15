//
// Created by patri on 08/01/2022.
//

#include <iostream>
#include "BNode.h"
#include "ReviewData.h"

int BNode::ord = 0;

BNode::BNode() {
    //this->reviewDataVector.reserve(BNode::ord);
   // this->children.reserve(BNode::ord + 1);
}

BNode::~BNode() {

    for (int i = 0; i < this->getNumKeys(); i++) {
        delete this->getElement(i);
    }
    for (int i = 0; i < this->getNumChildren(); i++) {
        delete this->getChild(i);
    }
    cout << "Delete bnode: " << this << endl;
}


BNode *BNode::getChild(int index) {

    return children[index];
}

int BNode::insert(ReviewData *reviewData) {


    for (int i = 0; i < this->getNumKeys(); i++) {
        //compara ids dos dois reviews, se id do objeto passado por parâmetro for menor
        //que o elemento i, ele é inserido na posição i, movendo o restante para a direita

        //a.compare(b): -1 significa que a é menor que b
        //a.compare(b):  1 significa que a é maior que b
        if (this->reviewDataVector[i]->getId().compare(reviewData->getId()) > 0) {
            //inserir em i
            this->insertAt(reviewData, i);
            return i;
        }
    }
    this->reviewDataVector.push_back(reviewData);

    return (int) reviewDataVector.size() - 1;

}

void BNode::insertAt(ReviewData *reviewData, int index) {

    //move itens depois de index uma unidade para a direita

    this->reviewDataVector.push_back(nullptr);
    for (int i = this->getNumKeys(); i > index; i--) {
        this->reviewDataVector[i] = this->reviewDataVector[i - 1];
    }

    this->reviewDataVector[index] = reviewData;
}

void BNode::insertChildAt(BNode *bNode, int index) {

    //move itens depois de index uma unidade para a direita

    this->children.push_back(nullptr);
    for (int i = this->getNumChildren(); i > index; i--) {
        this->children[i] = this->children[i - 1];
    }

    this->children[index] = bNode;
}

void BNode::insertReplaceChildAt(BNode *bNode, int index) {

    this->children[index] = bNode;
}