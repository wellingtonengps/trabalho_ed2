#ifndef TRABALHO_LINEARHASHTABLE_H
#define TRABALHO_LINEARHASHTABLE_H

#include "Bucket.h"
#include <vector>

class LinearHashTable {

private:
    int bucketCount=3;
    vector<Bucket*> bucketList;
    int splitPointer;
    int g;
public:
    LinearHashTable();
    ~LinearHashTable();
    void insert(string val);
    void splitBucket();
    int hash(string val);

};


#endif //TRABALHO_LINEARHASHTABLE_H
