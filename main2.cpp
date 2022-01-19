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


    BTree bTree = BTree(5);
   /* bTree.insert("0001", 1);
    bTree.insert("0003", 1);
    bTree.insert("0000", 1);
    bTree.insert("0002", 1);

    // bTree.printTree();
    bTree.insert("0009", 1);
    // bTree.printTree();

    bTree.insert("000a", 1);
    bTree.insert("000b", 1);
    bTree.insert("000c", 1);
    bTree.insert("000h", 1);
    bTree.insert("000o", 1);
    bTree.insert("001a", 1);
    bTree.insert("001b", 1);
    bTree.insert("001c", 1);
    bTree.insert("001h", 1);
    bTree.insert("001o", 1);
    bTree.insert("002a", 1);
    bTree.insert("002b", 1);
    bTree.insert("002c", 1);
    bTree.insert("002d", 1);
    bTree.insert("002e", 1);
    bTree.insert("002f", 1);
    bTree.insert("002g", 1);

    //std::this_thread::sleep_for(chrono::nanoseconds(10));

    bTree.insert("000:1", 1);
    bTree.insert("000:2", 1);
    bTree.insert("000:3", 1);
    bTree.insert("000:4", 1);
    bTree.insert("000:5", 1);
    bTree.insert("000:6", 1);
    bTree.insert("000:7", 1);
    bTree.insert("000:8", 1);
    bTree.insert("000:9", 1);
    bTree.insert("001:0", 1);

    bTree.insert("000:1", 1);
    bTree.insert("000:1", 1);
    bTree.insert("000:1", 1);
    bTree.insert("000:1", 1);
    bTree.insert("000:1", 1);*/

    //FileIO fileIo = FileIO();
    //fileIo.importarAleatoriosBTree(bTree, "data.bin", 20);


   // int find = bTree.find("gp:AOqpTOGSsGv5rOA79ttW2LE0FeMYvkdUuXRMTfbyMk00pJ0uDDj4XRvR5b2fVE4EIG19EdKBF0pZzb7g0NYYMg");

    VPTree vpTree = VPTree();

    vpTree.insere("0", 1);
    vpTree.insere("1", 1);
    vpTree.insere("2", 1);
    vpTree.insere("3", 1);
    vpTree.insere("4", 1);
    vpTree.insere("5", 1);
    vpTree.insere("6", 1);
    vpTree.insere("7", 1);

    //FileIO fileIo = FileIO();
    //fileIo.importarAleatoriosVPTree(vpTree, "data.bin", 8);

    cout << "Raiz: " << vpTree.getRaiz()->getInfo()->getId() << endl;

    vpTree.imprime();

   // cout << "Busca: " <<  vpTree.busca("00:1") << endl;

    cout << endl;

    return 0;
}






