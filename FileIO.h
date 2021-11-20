//
// Created by welli on 11/20/2021.
//

#ifndef MAIN_CPP_FILEIO_H
#define MAIN_CPP_FILEIO_H
#include <fstream>
#include <string>

using namespace std;

class FileIO {
private:
    //ifstream* inputFile;
    int nextChar=0;
    int bufferSize; //= 100000;
    char* dados;
    int currentBlock =0;
    int fileSize;
    bool endOfFile = false;
    void bufferChunk();
    int REVIEW_TEXT_LENGTH = 700;
    int REVIEW_ID_LENGTH = 90;
    int REVIEW_UPVOTES_LENGTH = 6;
    int REVIEW_VERSION_LENGTH = 9;
    int REVIEW_DATE_LENGTH = 20;
    int RECORD_LENGTH = REVIEW_TEXT_LENGTH + REVIEW_ID_LENGTH + REVIEW_UPVOTES_LENGTH + REVIEW_VERSION_LENGTH + REVIEW_DATE_LENGTH;


public:
    FileIO(string path, int bufferSize);
    ~FileIO();
    void close();
    char getNextChar();
    void readToBinary(string path);
};


#endif //MAIN_CPP_FILEIO_H
