#include "ListaEncad.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include "Cell.h"

using namespace std;

ListaEncad::ListaEncad()
{
    primeiro = NULL;
    ultimo = NULL;
    n = 0;
}

ListaEncad::~ListaEncad()
{
    Node *p = primeiro;
    while(p != NULL)
    {
        Node *t = p->getProx();
        delete p;
        p = t;
    }
}

bool ListaEncad::busca(string val)
{
    Node *p;
    for(p = primeiro; p != NULL; p = p->getProx())
        if(p->getInfo()->getCellInfo() == val)
            return true;
    return false;
}

void ListaEncad::insereFinal(Cell* cell)
{
    Node* p = new Node();
    p->setInfo(cell);
    p->setProx(NULL);

    if(ultimo != NULL) ultimo->setProx(p);
    ultimo = p;

    n++;
    if(n == 1) primeiro = p;
}

int ListaEncad::getSize(){
    return n;
}


Cell* ListaEncad::get(int k)
{
    Node *p = primeiro;
    int i = 0;
    while(i < k && p != NULL)
    {
        i++;
        p = p->getProx();
    }
    if(p == NULL)
    {
        cout << "ERRO: Indice invalido!" << endl;
        exit(1);
    }
    else
        return p->getInfo();
}

Node* ListaEncad::getNode(int k)
{
    Node *p = primeiro;
    int i = 0;
    while(i < k && p != NULL)
    {
        i++;
        p = p->getProx();
    }
    if(p == NULL)
    {
        cout << "ERRO: Indice invalido!" << endl;
        exit(1);
    }
    else
        return p;
}

