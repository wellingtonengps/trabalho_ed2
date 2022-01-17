
#ifndef MAIN_CPP_FILEIO_H
#define MAIN_CPP_FILEIO_H
#include <fstream>
#include <string>
#include "Review.h"
#include <vector>
#include "BTree.h"
#include "VPTree.h"


class FileIO {
private:
    //ifstream* inputFile;
    int nextChar=0;
    int bufferSize; //= 100000;
    char* dados;
    int currentBlock =0;
    int fileSize;
    bool endOfFile = false;
    int REVIEW_TEXT_LENGTH = 400;
    int REVIEW_ID_LENGTH = 90;
    int REVIEW_UPVOTES_LENGTH = 6;
    int REVIEW_VERSION_LENGTH = 9;
    int REVIEW_DATE_LENGTH = 20;
    int RECORD_LENGTH = REVIEW_TEXT_LENGTH + REVIEW_ID_LENGTH + REVIEW_UPVOTES_LENGTH + REVIEW_VERSION_LENGTH + REVIEW_DATE_LENGTH;


public:
    FileIO();
    ~FileIO();
    void close();
    char getNextChar(ifstream* inputFile);
    void initFile(ifstream* inputFile);
    void readCSVToBinary(string input_path, string binary_output_path);
    Review* acessarRegistroTAD(int i, ifstream& arq);
    Review* acessarRegistroTAD(int i, string binary_input);
    void bufferChunk(ifstream* inputFile);
    vector<Review*> importarAleatorios(string path, int num);
    void importarAleatoriosBTree(BTree &bTree, string path, int num);
    void importarAleatoriosVPTree(VPTree &vpTree, string path, int num);
};


#endif //MAIN_CPP_FILEIO_H
