//
// Created by patri on 15/12/2021.
//

#ifndef TRABALHO_NODE_H
#define TRABALHO_NODE_H
#include <string>
#include "Cell.h"

using namespace std;

class Node {
private:
    Cell* info;
    Node *prox;
public:
    Node() { };
    ~Node() { };
    Cell* getInfo() { return info; };
    Node* getProx() { return prox; };
    void setInfo(Cell* cell) { info = cell; };
    void setProx(Node *p) { prox = p; };
};


#endif //TRABALHO_NODE_H
