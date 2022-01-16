//
// Created by patri on 08/01/2022.
//

#include "ReviewData.h"

ReviewData::ReviewData(string id, int location) {
this->id = id;
this->location = location;
}

ReviewData::~ReviewData() {
   // cout << "Delete ReviewData: "<<  this << endl;
}