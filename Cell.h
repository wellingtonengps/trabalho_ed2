//
// Created by patri on 19/12/2021.
//

#ifndef TRABALHO_CELL_H
#define TRABALHO_CELL_H
#include <string>

using namespace std;

class Cell {
private:
    int count;
    string info;
public:
    Cell();
    ~Cell();
    void setCellInfo(string info);
    string getCellInfo();
    int getCount();
    void incrementCount();
};


#endif //TRABALHO_CELL_H
