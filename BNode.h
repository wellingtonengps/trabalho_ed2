//
// Created by patri on 08/01/2022.
//

#ifndef TRABALHO_BNODE_H
#define TRABALHO_BNODE_H
#include <string>
#include <vector>
#include "ReviewData.h"

using namespace std;

class BNode {
private:
     vector<ReviewData*> reviewDataVector;
     vector<BNode*> children;
     bool leaf=true;
     //static int ord;
public:
    static int ord;
    BNode();
    ~BNode();
    bool isLeaf(){return leaf;}
    bool isFull(){return reviewDataVector.size() == ord-1;}
    bool overflowed(){return reviewDataVector.size() >= ord;}
    void setIsLeaf(bool isLeaf){this->leaf=isLeaf;}
    int getNumChildren(){return (int)children.size();}
    int getNumKeys(){return (int)reviewDataVector.size();}
    ReviewData* getReviewData(int index){return reviewDataVector[index];}
    BNode* getChild(int index);
    ReviewData* getElement(int index){return reviewDataVector[index];}
    int insert(ReviewData* reviewData);
    void insertAt(ReviewData* reviewData, int index);
    static int getOrd(){return BNode::ord;}
    static void setOrd(int ord){BNode::ord=ord;}
    vector<ReviewData*> getElementsVector(){return  reviewDataVector;}
    vector<BNode*> getChildren(){return children;}
    void clear(){reviewDataVector.clear(); children.clear();}
    void pushBackChild(BNode* bNode){children.push_back(bNode);}
    void insertChildAt(BNode *bNode, int index);
    void insertReplaceChildAt(BNode *bNode, int index);

};


#endif //TRABALHO_BNODE_H
