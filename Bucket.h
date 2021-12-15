
#ifndef TRABALHO_BUCKET_H
#define TRABALHO_BUCKET_H
#include "ListaEncad.h"
#include <string>
#include <vector>

using namespace std;

class Bucket {

private:
    int tam = 10;
    vector<string> itemList;
    ListaEncad overflowArea;
public:
    Bucket();
    ~Bucket();
    void inserir(string val);
    string busca(string val);
};


#endif //TRABALHO_BUCKET_H
