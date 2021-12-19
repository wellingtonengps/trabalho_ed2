
#ifndef TRABALHO_BUCKET_H
#define TRABALHO_BUCKET_H
#include "ListaEncad.h"
#include <string>
#include <vector>
#include "Cell.h"

using namespace std;

class Bucket {

private:
    int tam = 4;
    vector<Cell*> itemList;
    ListaEncad overflowArea;
public:
    Bucket(int size);
    ~Bucket();
    void inserir(Cell* cell);
    Cell* busca(string val);
    Cell* get(int k);
    int getTotalSize();
    Cell* getRemove(int k);
};


#endif //TRABALHO_BUCKET_H
