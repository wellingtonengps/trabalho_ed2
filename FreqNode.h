//
// Created by welli on 2/12/2022.
//

#ifndef TRABALHO_ED2_FREQNODE_H
#define TRABALHO_ED2_FREQNODE_H


class FreqNode {
private:
    FreqNode* esq= nullptr;
    FreqNode* dir= nullptr;
    char info;
    int freq;
public:
    FreqNode(char info, int freq);
    ~FreqNode();
    FreqNode *getEsq() const;
    void setEsq(FreqNode *esq);
    FreqNode *getDir() const;
    void setDir(FreqNode *dir);
    char getInfo() const;
    void setInfo(char info);
    int getFreq() const;
    void setFreq(int freq);
    void incrementaFreq(int i);
};


#endif //TRABALHO_ED2_FREQNODE_H
