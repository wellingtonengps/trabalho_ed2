//
// Created by welli on 2/12/2022.
//

#include "FreqNode.h"

FreqNode::FreqNode(char info, int freq) {
    this->info = info;
    this->freq = freq;
}

FreqNode::~FreqNode() {

    if(this->getEsq() != nullptr ){
        delete this->getEsq();
    }

    if(this->getDir() != nullptr) {
        delete this->getDir();
    }
}

FreqNode *FreqNode::getEsq() const {
    return esq;
}

void FreqNode::setEsq(FreqNode *esq) {
    FreqNode::esq = esq;
}

FreqNode *FreqNode::getDir() const {
    return dir;
}

void FreqNode::setDir(FreqNode *dir) {
    FreqNode::dir = dir;
}

char FreqNode::getInfo() const {
    return info;
}

void FreqNode::setInfo(char info) {
    FreqNode::info = info;
}

int FreqNode::getFreq() const {
    return freq;
}

void FreqNode::setFreq(int freq) {
    FreqNode::freq = freq;
}

void FreqNode::incrementaFreq(int i) {
    this->freq += i;
}

