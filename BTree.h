//
// Created by patri on 08/01/2022.
//

#ifndef TRABALHO_BTREE_H
#define TRABALHO_BTREE_H


#include "BNode.h"

class BTree {
private:
    BNode* root;
    int ord;
public:
    BTree(int ord);
    ~BTree();
    BNode* getRoot(){return root;}
    void setRoot(BNode* bNode){root=bNode;}
    int getOrd(){return ord;}
    void setOrd(int ord){ this->ord=ord;}
    void insert(string id, int location);
    void insert(ReviewData* reviewData);
    BNode* getInsertionNode(string id);
    void splitNode(BNode* bNode);
    void splitNode(BNode* bNode, BNode* newLeftNode, BNode* newRightNode);
    void printTree();
    void printLevel(BNode* bnode);
    int find(string id);
};


#endif //TRABALHO_BTREE_H
