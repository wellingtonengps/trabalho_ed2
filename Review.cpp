#include <iostream>
#include "Review.h"
#include <string>

using namespace std;

Review::Review(){

};

Review::~Review() {};

string Review::getReviewId(){
    return review_id;
};

string Review::getReviewText(){
    return review_text;
};

int Review::getUpvotes(){
    return upvotes;
};

string Review::getAppVersion(){
    return app_version;
};

string Review::getPostedDate(){
    return posted_date;
};

void Review::setReviewId(string id){
    this->review_id = id;
};

void Review::setReviewText(string text){
    this->review_text = text;
};

void Review::setUpvotes(int upvotes){
    this->upvotes = upvotes;
};

void Review::setAppVersion(string version){
    this->app_version = version;
};

void Review::setPostedDate(string date){
   this->posted_date = date;
};

string Review::toString() {
    string reviewString;

    reviewString.append("Id: " + this->getReviewId() + "\n");
    reviewString.append("Text: " + this->getReviewText() + "\n");
    reviewString.append("Upvotes: " + to_string(this->getUpvotes()) + "\n");
    reviewString.append("Version: " + this->getAppVersion() + "\n");
    reviewString.append("Posted date: " + this->getPostedDate() + "\n");

    return reviewString;
}