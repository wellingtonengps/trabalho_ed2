//
// Created by patri on 15/12/2021.
//

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

/*
void ListaEncad::set(int k, string val)
{
    Node *p = primeiro;
    int i = 0;
    while(i < k && p != NULL)
    {
        i++;
        p = p->getProx();
    }
    if(p == NULL)
        cout << "ERRO: Indice invalido!" << endl;
    else
        p->setInfo(val);
}

void ListaEncad::insereInicio(string val)
{
    Node* p = new Node();
    p->setInfo(val);
    p->setProx(primeiro);

    primeiro = p;

    n++;
    if(n == 1) ultimo = p;
}

void ListaEncad::removeInicio()
{
    Node* p;
    if(primeiro != NULL)
    {
        p = primeiro;
        primeiro = p->getProx();
        delete p;

        n--;
        if(n == 0) ultimo = NULL;
    }
    else
        cout << "ERRO: lista vazia!" << endl;
}

void ListaEncad::removeFinal()
{
    Node* p;
    if(ultimo != NULL)
    {
        if(primeiro == ultimo)
        {
            primeiro = NULL;
            p = NULL;
        }
        else
        {
            p = primeiro;
            while(p->getProx() != ultimo)
                p = p->getProx();
            p->setProx(NULL);
        }
        delete ultimo;
        ultimo = p;
        n--;
    }
    else
        cout << "ERRO: lista vazia!" << endl;
}

void ListaEncad::imprime(){

    Node *p = primeiro;

    while(p != NULL){
        cout << p->getCellInfo() << " ";
        p = p->getProx();
    }

    cout << endl;
}*/



