//
// Created by patri on 08/01/2022.
//

#include "BTree.h"
#include "ReviewData.h"
#include "BNode.h"
#include "VPTree.h"
#include <iostream>
#include "FileIO.h"
#include <chrono>
#include <thread>

int main(){

    /*cout <<"hello"<<endl;

    ReviewData rd1 = ReviewData("0:001", 1);
    ReviewData rd2 = ReviewData("0:003", 2);
    ReviewData rd3 = ReviewData("0:000", 3);
    ReviewData rd4 = ReviewData("0:002", 4);
    ReviewData rd5 = ReviewData("0:009", 4);
    ReviewData rd6 = ReviewData("0:00a", 4);
    ReviewData rd7 = ReviewData("0:00b", 4);
    ReviewData rd8 = ReviewData("0:00c", 4);

    BNode::setOrd(5);
    BNode bNode = BNode();
    bNode.insert(&rd1);
    bNode.insert(&rd2);
    bNode.insert(&rd3);
    //bNode.insert(&rd4);
    //bNode.insert(&rd5);
    //bNode.insert(&rd6);
    //bNode.insert(&rd7);

    BTree bTree = BTree(5);
    bTree.insert("0001", 1);
    bTree.insert("0003", 1);
    bTree.insert("0000", 1);
    bTree.insert("0002", 1);

   */

    cout << "Criando arv!!!" << endl;

    VPTree arv;

    arv.insere(40);
    arv.insere(60);
    arv.insere(80);
    arv.insere(90);
    arv.insere(85);

    cout << "Raiz: " << arv.getRaiz()->getInfo() << endl;


    arv.imprime();
    cout << endl;

return 0;
}