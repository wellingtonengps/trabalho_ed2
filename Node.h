//
// Created by patri on 15/12/2021.
//

#ifndef TRABALHO_NODE_H
#define TRABALHO_NODE_H
#include <string>

using namespace std;

class Node {
private:
    string info; // valor armazenado no No
    Node *prox; // ponteiro para o proximo No
public:
    Node() { };
    ~Node() { };
    string getInfo() { return info; };
    Node* getProx() { return prox; };
    void setInfo(string val) { info = val; };
    void setProx(Node *p) { prox = p; };
};


#endif //TRABALHO_NODE_H
