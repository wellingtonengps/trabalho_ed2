//
// Created by patri on 08/01/2022.
//

#include <iostream>
#include <deque>
#include <stack>
#include "BTree.h"

BTree::BTree(int ord) {
    this->root = new BNode();
    this->ord = ord;
    BNode::ord = ord;
}


BTree::~BTree() {
    delete root;
}

void BTree::insert(string id, int location){

}

void BTree::splitNode(BNode* bNode){
    if(bNode== this->root){

        int centralIndex = ord/2;
        BNode* newRoot = new BNode();
        BNode* newLeftNode = new BNode();
        BNode* newRightNode = new BNode();

        for (int i =0; i< bNode->getNumKeys(); i++){
            if(i<centralIndex){
                newLeftNode->insert(bNode->getElement(i));
            }
            else if(i>centralIndex){
                newRightNode->insert(bNode->getElement(i));
            }
        }

        for (int i =0; i< bNode->getNumChildren(); i++){
            if(i<=centralIndex){
                newLeftNode->pushBackChild(bNode->getChild(i));
            }
            else{
                newRightNode->pushBackChild(bNode->getChild(i));;
            }
        }

        newRoot->insert(bNode->getElement(centralIndex));
        newRoot->pushBackChild(newLeftNode);
        newRoot->pushBackChild(newRightNode);

        this->root = newRoot;
        bNode->clear();
        delete bNode;


    }else{

    }
}
/*
void BTree::splitRoot(ReviewData* overflowedElement){
    BNode* newLeftNode = new BNode();
    BNode* newRightNode = new BNode();

}
*/

/*
void BTree::insert(ReviewData* reviewData){

        BNode* insertionNode = getInsertionNode(reviewData->getId());
        insertionNode->insert(reviewData);

        if(insertionNode->overflowed()){
            cout << "Overflow. Fazer split"<<endl;
            splitNode(insertionNode);
        }
}
*/

BNode* BTree::getInsertionNode(string id){
    BNode* current = root;

    while(!current->isLeaf()){
        for(int i=0; i<current->getNumKeys(); i++){
            string currentKey = current->getElement(i)->getId();

            //a.compare(b): -1 significa que a é menor que b
            //a.compare(b):  1 significa que a é maior que b
            if(id.compare(currentKey)<0){
                current = current->getChild(i);
            }
        }

        //pega ultimo filho
        current = current->getChild(current->getNumChildren()-1);
    }

    return current;
}

void BTree::splitNode(BNode* bNode, BNode* newLeftNode, BNode* newRightNode){

        int centralIndex = ord/2;
        //BNode* newRoot = new BNode();
        //BNode* newLeftNode = new BNode();
        //BNode* newRightNode = new BNode();

        for (int i =0; i< bNode->getNumKeys(); i++){
            if(i<centralIndex){
                newLeftNode->insert(bNode->getElement(i));
            }
            else if(i>centralIndex){
                newRightNode->insert(bNode->getElement(i));
            }
        }

        for (int i =0; i< bNode->getNumChildren(); i++){
            if(i<=centralIndex){
                newLeftNode->pushBackChild(bNode->getChild(i));
            }
            else{
                newRightNode->pushBackChild(bNode->getChild(i));;
            }
        }

        //newRoot->insert(bNode->getElement(centralIndex));
       // newRoot->pushBackChild(newLeftNode);
       // newRoot->pushBackChild(newRightNode);

        //this->root = newRoot;
        bNode->clear();
        delete bNode;
}

void BTree::insert(ReviewData* reviewData){
    BNode* current = root;
    stack<BNode*> bNodeStack;
    string id = reviewData->getId();
    bNodeStack.push(root);

    while(!current->isLeaf()){
        for(int i=0; i<current->getNumKeys(); i++){
            string currentKey = current->getElement(i)->getId();

            //a.compare(b): -1 significa que a é menor que b
            //a.compare(b):  1 significa que a é maior que b
            if(id.compare(currentKey)<0){
                //pega o índice do primeiro elemento cujo id é maior que o passado por parâmetro
                bNodeStack.push(current->getChild(i));
                current = current->getChild(i);
                break;
            }else if(i==current->getNumKeys()-1){
                //pega último filho
                bNodeStack.push(current->getChild(i+1));
                current = current->getChild(i+1);
                break;
            }
        }
    }

    //BNode* insertionNode = bNodeStack.top();
    //insertionNode->insert(reviewData);
    bNodeStack.top()->insert(reviewData);
    int centralIndex = ord/2;

    while(bNodeStack.top()->overflowed()){
        cout << "Overflow. Fazer split"<<endl;
        BNode* newLeftNode = new BNode();
        BNode* newRightNode = new BNode();
        ReviewData* centerElement = bNodeStack.top()->getElement(centralIndex);

        splitNode(bNodeStack.top(), newLeftNode, newRightNode);

        if(bNodeStack.top()== this->root){
            //cria novo nó
            BNode* newRoot = new BNode();
            newRoot->setIsLeaf(false);
            //insere elemento central
            newRoot->insert(centerElement);
            //insere novos nós na lista de filhos
            newRoot->pushBackChild(newLeftNode);
            newRoot->pushBackChild(newRightNode);
            //atribui nova raiz à raiz da árvore
            this->root = newRoot;
            //bNodeStack.pop();
        }else{
            bNodeStack.pop();
            //insere elemento central no pai
            int insertedPos = bNodeStack.top()->insert(centerElement);
            //insere novos nós filhos nesse pai, antes e depois do nó que acabou de ser inserido
            bNodeStack.top()->insertReplaceChildAt(newLeftNode, insertedPos);
            bNodeStack.top()->insertChildAt(newRightNode, insertedPos+1);
            bNodeStack.top()->setIsLeaf(false);
        }


    }

}
