//
// Created by patri on 19/12/2021.
//

#include "Cell.h"

Cell::Cell() {
    this->count = 0;
};

Cell::~Cell() {};

int Cell::getCount() {
    return this->count;
};

void Cell::setCellInfo(string info){
    this->info = info;
}

string Cell::getCellInfo() {
    return this->info;
};

void Cell::incrementCount(){
    this->count++;
}