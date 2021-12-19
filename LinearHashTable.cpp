#include "LinearHashTable.h"
#include <string>
#include <math.h>
#include<iostream>
#include<algorithm>

using namespace  std;

LinearHashTable::LinearHashTable(float maxFatorCarga) {
    this->maxFatorCarga=maxFatorCarga;
    g=0;
    splitPointer=0;
    nChaves=0;
    bucketList.reserve(originalBucketCount);

    for(int i=0; i < originalBucketCount; i++){
        bucketList.push_back(new Bucket(bucketSize));
    }

}

LinearHashTable::~LinearHashTable() {
    for(int i=0; i < originalBucketCount; i++){
        delete bucketList[i];
    }

}

void LinearHashTable::insert(string val) {

    int h = hash(val);
   // cout<< "val: "<< val<< " balde: "<<h<<endl;


   //verifica se o valor já está inserido, se não, insere
   Cell* buscaCell = busca(val);
   if (buscaCell!=NULL) {
        buscaCell->incrementCount();
   }
   else{
       Cell* cell = new Cell();
       cell->setCellInfo(val);

       bucketList[h]->inserir(cell);
       nChaves++;

       //cout <<"FC: " << fatorCarga()<<endl;
       if (fatorCarga() >= maxFatorCarga) {
           // cout << "FC: "<< fatorCarga() << " >= "<<maxFatorCarga<<endl;
           splitBucket();
       }
   }
}

void LinearHashTable::reinsert(Cell* cell) {

    int h = hash(cell->getCellInfo());
    //cout<< "reinserindo val: "<< val<< " balde: "<<h<<endl;
    bucketList[h]->inserir(cell);
}

Cell* LinearHashTable::busca(string val){

    int k = comprimeCaracteres(val);
    int h = k % (int)(originalBucketCount * (float)pow(2, 0));
    Cell* encontrado=NULL;

    for(int i=1; encontrado==NULL && h<bucketList.size(); i++){
        encontrado = bucketList[h]->busca(val);
        h = k % (int)(originalBucketCount * (float)pow(2, i));
    }

    return encontrado;
}


void LinearHashTable::splitBucket() {

    if(splitPointer==originalBucketCount*pow(2, g)){
        splitPointer=0;
        g++;
    }

    bucketList.push_back(new Bucket(bucketSize));
    cout << "QNTD de baldes: "  << bucketList.size() << endl;
    Bucket* current = bucketList[splitPointer];
    bucketList[splitPointer] = new Bucket(bucketSize);
    //nChaves-=current->getTotalSize();


    //redistribuindo valores do balde dividido
    cout<< "split balde "<< splitPointer<<endl;
    for(int i=0; i<current->getTotalSize(); i++){
        Cell* cell  =  current->getRemove(i);
        reinsert(cell);
    }

    splitPointer++;

    delete current;

}
float LinearHashTable::fatorCarga(){
    int N = bucketList.size();
    int M = bucketSize;

    float fatorC = nChaves/(float)(N*M);
    return fatorC;
}

int LinearHashTable::comprimeCaracteres(string val){

    val.erase(remove(val.begin(), val.end(), '.'), val.end());
    int res = stoi(val);
    return res;
}

int LinearHashTable::hash(string val) {

   // cout << "val: "<< val<<endl;
   // val.erase(remove(val.begin(), val.end(), '.'), val.end());

    int k = comprimeCaracteres(val);
    int n = originalBucketCount /** pow(2, g)*/;

    int h = k % (int)(n * pow(2, this->g));

    if(h<splitPointer){
        //todo: isso pode dar um número maior q o total de baldes
        h = k % (int)(n * pow(2, this->g+1));
    }

    return h;
}

void LinearHashTable::printTable(){
    for(int i=0; i < bucketList.size(); i++){
        cout << i << ": ";
        for(int j=0; j<bucketList[i]->getTotalSize(); j++){
            string text =  bucketList[i]->get(j)->getCellInfo();
            int count =  bucketList[i]->get(j)->getCount();
            cout << bucketList[i]->get(j)->getCellInfo() << " ["<<count<<"]" << ", ";
        }
        cout << endl;
    }
}

vector<Cell*> LinearHashTable::getTableAsVector(){

    vector<Cell*> cells;
    cells.reserve(nChaves);
    for(int i=0; i < bucketList.size(); i++){
        for(int j=0; j<bucketList[i]->getTotalSize(); j++){
            Cell* cell = bucketList[i]->get(j);
            cells.push_back(cell);
        }
        cout << endl;
    }

    return cells;
}

