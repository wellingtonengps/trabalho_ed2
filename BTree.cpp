//
// Created by patri on 08/01/2022.
//

#include <iostream>
#include <stack>
#include "BTree.h"

BTree::BTree(int ord) {
    this->root = new BNode();
    this->ord = ord;
    //todo: tornar ord não estático. Vai dar problema se existir outra àrvore de ordem diferente
    BNode::ord = ord;
}


BTree::~BTree() {
    delete root;
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
                newRightNode->pushBackChild(bNode->getChild(i));
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
                newRightNode->pushBackChild(bNode->getChild(i));
            }
        }

        newRightNode->setIsLeaf(bNode->isLeaf());
        newLeftNode->setIsLeaf(bNode->isLeaf());
        //newRoot->insert(bNode->getElement(centralIndex));
       // newRoot->pushBackChild(newLeftNode);
       // newRoot->pushBackChild(newRightNode);

        //this->root = newRoot;
        //bNode->clear();
        //delete bNode;
}


void printNode(BNode *bNode){

    cout << "|";
    for(int i=0; i<bNode->getNumKeys(); i++){
        cout<<bNode->getElement(i)->getId() << " | ";
    }
}

int BTree::find(string id){
    BNode* current = this->root;

    while(!current->isLeaf()){
        for(int i=0; i<current->getNumKeys(); i++){
            string currentKey = current->getElement(i)->getId();

            //a.compare(b): -1 significa que a é menor que b
            //a.compare(b):  1 significa que a é maior que b
            if(id.compare(currentKey)<0){
                //pega o índice do primeiro elemento cujo id é maior que o passado por parâmetro
                current = current->getChild(i);
                break;
            }else if(id.compare(currentKey)==0){
                return  current->getElement(i)->getLocation();

            }else if(i==current->getNumKeys()-1){
                //pega último filho
                current = current->getChild(i+1);
                break;
            }
        }
    }

    return -1;

}

void BTree::insert(string id, int location){
    ReviewData* reviewData = new ReviewData(id, location);
    BNode* current = this->root;
    stack<BNode*> bNodeStack;
    bNodeStack.push(this->root);

    //cout << "inserir: "<< id <<endl;
    while(!current->isLeaf()){
        for(int i=0; i<current->getNumKeys(); i++){
            string currentKey = current->getElement(i)->getId();

            //a.compare(b): -1 significa que a é menor que b
            //a.compare(b):  1 significa que a é maior que b
            if(id.compare(currentKey)<0){
                //pega o índice do primeiro elemento cujo id é maior que o passado por parâmetro
                bNodeStack.push(current->getChild(i));
                current = current->getChild(i);
                //printNode(current->getChild(i));
                break;
            }else if(i==current->getNumKeys()-1){
                //pega último filho
                bNodeStack.push(current->getChild(i+1));
                current = current->getChild(i+1);
                break;
            }
        }
    }

    bNodeStack.top()->insert(reviewData);
    int centralIndex = ord/2;


    //todo: porque tem um nó folha acima do último nível?
    while(!bNodeStack.empty() && bNodeStack.top()->overflowed()){
       // cout << "Overflow. Fazer split"<<endl;
        BNode* nodeToBeSplit = bNodeStack.top();
        bNodeStack.pop();

        BNode* newLeftNode = new BNode();
        BNode* newRightNode = new BNode();
        ReviewData* centerElement = nodeToBeSplit->getElement(centralIndex);

        splitNode(nodeToBeSplit, newLeftNode, newRightNode);

        if(nodeToBeSplit== this->root){
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

        }else{
            //insere elemento central no pai
            int insertedPos = bNodeStack.top()->insert(centerElement);
            //insere novos nós filhos nesse pai, antes e depois do nó que acabou de ser inserido
            bNodeStack.top()->insertReplaceChildAt(newLeftNode, insertedPos);
            bNodeStack.top()->insertChildAt(newRightNode, insertedPos+1);
            bNodeStack.top()->setIsLeaf(false);
        }

        nodeToBeSplit->clear();
        //cout << "delete " << nodeToBeSplit << endl;
        delete nodeToBeSplit;

    }

    //printTree();

}

/*
void BTree::printLevel(BNode* bnode){

    vector<BNode*> v;

    if(bnode->isLeaf()){
        return;
    }

    if(bnode==this->root){
        printNode(bnode);
        for(int i=0; i<bnode->getNumChildren(); i++){
            printLevel(bnode->getChild(i));
        }
    }else{
        for(int i=0;i<bnode->getNumChildren(); i++){
            v.push_back(bnode->getChild(i));
            printNode(bnode->getChild(i));
            cout << " + ";
        }
        for(int i=0; i<bnode->getNumChildren(); i++){
            printLevel(bnode->getChild(i));
        }

    }
    cout <<"\n";

}*/

void BTree::printTree(){


    //printLevel(this->root);
    vector<vector<BNode*>> nodeVector;
    vector<BNode*> v;
    nodeVector.push_back(v);
    nodeVector[0].push_back(this->root);
    bool loop = true;

    int i=0;
    while(loop){
        for(int j=0; j< nodeVector[i].size(); j++){
            vector<BNode*> vecToInsert;

            if(nodeVector[i][j]->isLeaf()){
                loop=false;
                break;
            }
            for(int k=0; k<nodeVector[i][j]->getNumChildren(); k++){
                vecToInsert.push_back(nodeVector[i][j]->getChild(k));
            }

            nodeVector.push_back(vecToInsert);

        }
        i++;
    }

    for(int i=0; i< nodeVector.size(); i++){
        for(int j=0; j< nodeVector[i].size(); j++){
            printNode(nodeVector[i][j]);
            cout << "----";
        }
        cout << endl;
    }

}


