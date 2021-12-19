#ifndef TRABALHO_LINEARHASHTABLE_H
#define TRABALHO_LINEARHASHTABLE_H

#include "Bucket.h"
#include <vector>
#include "Cell.h"

class LinearHashTable {

private:
    int originalBucketCount=3;
    vector<Bucket*> bucketList;
    int bucketSize = 4;
    int splitPointer;
    int g;
    int nChaves;
    float maxFatorCarga;
public:
    LinearHashTable(float maxFatorCarga);
    Cell* busca(string val);
    void reinsert(Cell* val);
    ~LinearHashTable();
    void insert(string val);
    void splitBucket();
    int hash(string val);
    void printTable();
    float fatorCarga();
    int comprimeCaracteres(string val);
    vector<Cell*> getTableAsVector();
};


#endif //TRABALHO_LINEARHASHTABLE_H
