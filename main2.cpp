//
// Created by patri on 08/01/2022.
//

#include "BTree.h"
#include "ReviewData.h"
#include "BNode.h"
#include <iostream>
#include "FileIO.h"
#include <chrono>
#include <thread>

int main(){

    cout <<"hello"<<endl;

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

    /*bTree.insert("000:1", 1);
    bTree.insert("000:2", 1);
    bTree.insert("000:3", 1);
    bTree.insert("000:4", 1);
    bTree.insert("000:5", 1);
    bTree.insert("000:6", 1);
    bTree.insert("000:7", 1);
    bTree.insert("000:8", 1);
    bTree.insert("000:9", 1);
    bTree.insert("001:0", 1);*/

    /*bTree.insert("000:1", 1);
    bTree.insert("000:1", 1);
    bTree.insert("000:1", 1);
    bTree.insert("000:1", 1);
    bTree.insert("000:1", 1);*/

    /*FileIO fileIo = FileIO();
    fileIo.importarAleatoriosBTree(bTree, "data.bin", 20);
*/
    bTree.printTree();


    return 0;
}