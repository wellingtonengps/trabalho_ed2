//
// Created by patri on 15/12/2021.
//

#ifndef TRABALHO_LISTAENCAD_H
#define TRABALHO_LISTAENCAD_H
#include <string>
#include "Node.h"
#include "Cell.h"

using namespace std;

class ListaEncad {
public:
    ListaEncad();
    ~ListaEncad();
    bool busca(string val);
    Cell* get(int k);
    void insereFinal(Cell* cell);
    int getSize();
    Node* getNode(int k);


    //void removeInicio();
    //void removeFinal();
    //void set(int k, string val);
    //void insereInicio(string val);
private:
    Node *primeiro; /// primeiro No da lista
    Node *ultimo; /// ultimo No da lista
    int n; /// numero de nos na lista
};


#endif //TRABALHO_LISTAENCAD_H
