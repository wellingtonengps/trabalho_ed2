//
// Created by patri on 15/12/2021.
//

#ifndef TRABALHO_LISTAENCAD_H
#define TRABALHO_LISTAENCAD_H
#include <string>
#include "Node.h"

using namespace std;

class ListaEncad {
public:
    ListaEncad();
    ~ListaEncad();
    bool busca(string val);
    string get(int k);
    void set(int k, string val);
    void insereInicio(string val);
    void insereFinal(string val);
    void removeInicio();
    void removeFinal();
    int getSize();

private:
    Node *primeiro; /// primeiro No da lista
    Node *ultimo; /// ultimo No da lista
    int n; /// numero de nos na lista
};


#endif //TRABALHO_LISTAENCAD_H
