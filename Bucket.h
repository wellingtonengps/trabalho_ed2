
#ifndef TRABALHO_BUCKET_H
#define TRABALHO_BUCKET_H
#include "ListaEncad.h"
#include <string>
#include <vector>

using namespace std;

class Bucket {

private:
    int tam = 4;
    vector<string> itemList;
    ListaEncad overflowArea;
public:
    Bucket(int size);
    ~Bucket();
    void inserir(string val);
    string busca(string val);
    string get(int k);
    int getTotalSize();
};


#endif //TRABALHO_BUCKET_H
