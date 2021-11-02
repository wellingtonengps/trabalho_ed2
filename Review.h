//
// Created by welli on 11/2/2021.
//

#ifndef MAIN_CPP_REVIEW_H
#define MAIN_CPP_REVIEW_H
#include <string>

using namespace std;

class Review{
    private:
        string review_id;
        string review_text;
        int upvotes;
        string app_version;
        string posted_date;
    public:
        Review();
        ~Review();
        string getReviewId();
        string getReviewText();
        int getUpvotes();
        string getAppVersion();
        string getPostedDate();
        void setReviewId(string id);
        void setReviewText(string text);
        void setUpvotes(int upvotes);
        void setAppVersion(string version);
        void setPostedDate(string date);
};

#endif //MAIN_CPP_REVIEW_H
