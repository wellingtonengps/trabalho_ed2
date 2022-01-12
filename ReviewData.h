//
// Created by patri on 08/01/2022.
//

#ifndef TRABALHO_REVIEWDATA_H
#define TRABALHO_REVIEWDATA_H

#include <string>

using namespace std;

class ReviewData {

private:
    string id;
    int location;

public:
    ReviewData(string id, int location) {
        this->id = id;
        this->location = location;
    }

    ~ReviewData() {}
    string getId() { return this->id; }
    int getLocation() { return this->location; }
    void setId(string id) { this->id = id; }
    void setLocation(int location) { this->location = location; }
    /* int operator>(const ReviewData &r){
         return id.compare(r.id);
     }*/
};


#endif //TRABALHO_REVIEWDATA_H
