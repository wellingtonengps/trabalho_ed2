#include "FileIO.h"
#include "Review.h"
#include "ReviewData.h"
#include "BTree.h"
#include "VPTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

using namespace std;


FileIO::FileIO(){
    //nextChar=0;
    //currentBlock=0;
   // endOfFile=false;
    this->bufferSize = 10000;
    dados = new char[bufferSize];
    //ifstream newInputFile;
    //newInputFile.open(path, ios::binary);
    //this->inputFile = inputFile;
    //this->inputFile->seekg(0, inputFile->end);
    //fileSize = this->inputFile->tellg();
    //this->inputFile->seekg(0, inputFile->beg);
}



FileIO::~FileIO() {
    delete [] dados;
}

void FileIO::bufferChunk(ifstream* inputFile){

    if (!inputFile) {
        return;
    }
    inputFile->seekg(bufferSize*currentBlock);
    inputFile->read(dados, bufferSize);

}

char FileIO::getNextChar(ifstream* inputFile){
    if(currentBlock==0 && nextChar==0){
        bufferChunk(inputFile);
    }

    char c = dados[nextChar];
    // cout << c << "";

    if(nextChar== bufferSize-1){
        currentBlock++;
        nextChar=0;
        bufferChunk(inputFile);
    } else{
        nextChar++;
    }

    if((nextChar+ currentBlock*bufferSize)*sizeof(char) >= fileSize){
        endOfFile=true;
        //inputFile.close();
        delete [] dados;
        //cout << "EOFFFF !!!!!-----"<< endl;
    }

    return c;
}

void FileIO::close() {
   // inputFile->close();
}

void FileIO::initFile(ifstream* inputFile){
    nextChar=0;
    currentBlock=0;
    endOfFile=false;

    //arqI.open(path, ios::binary);
    inputFile->seekg(0, inputFile->end);
    fileSize = inputFile->tellg();
    inputFile->seekg(0, inputFile->beg);
}

void FileIO::readCSVToBinary(string input_path, string binary_output_path) {

    char c;

    ofstream outputFile;
    ifstream inputFile;

    outputFile.open(binary_output_path, ios::binary);
    inputFile.open(input_path, ios::binary);


    initFile(&inputFile);
    bool primeiraLinha=true;


    if (outputFile) {
        bool ignoraVirgula = false;
        int campoAtual = 0;
        string value;

        //lê dados do arquivo de entrada caractere por caractere
        //escrevendo os dados no arquivo de saída
        while (!endOfFile) {
            c= getNextChar(&inputFile);

            //ignorar a primeira linha do arquivo csv
            if(c=='\n' && primeiraLinha){
                primeiraLinha=false;
                continue;
            }
            if(primeiraLinha){
                continue;
            }

            if (c == '\"') {
                ignoraVirgula = !ignoraVirgula;
            } else if ((c == ',' || c == '\n') && ignoraVirgula == false){
                value += '\0';

                if (campoAtual == 0) {
                    outputFile.write(value.c_str(), sizeof(char) * REVIEW_ID_LENGTH);
                    campoAtual++;
                } else if (campoAtual == 1 ) {
                    outputFile.write(value.c_str(), sizeof(char) * REVIEW_TEXT_LENGTH);
                    campoAtual++;
                } else if (campoAtual == 2 ) {
                    outputFile.write(value.c_str(), sizeof(char) * REVIEW_UPVOTES_LENGTH);
                    campoAtual++;
                } else if (campoAtual == 3 ) {
                    outputFile.write(value.c_str(), sizeof(char) * REVIEW_VERSION_LENGTH);
                    campoAtual++;
                } else if (campoAtual == 4 ) {
                    outputFile.write(value.c_str(), sizeof(char) * REVIEW_DATE_LENGTH);
                    campoAtual = 0;
                }

                value.clear();


            } else {
                value += c;
            }
        }

        outputFile.close();
        inputFile.close();
    } else {
        cout << "Erro ao abrir o arquivo"<< endl;
    }
}

Review* FileIO::acessarRegistroTAD(int i, ifstream& arq){

    Review *review = new Review();

    char* review_id = new char[REVIEW_ID_LENGTH];
    char* review_text = new char[REVIEW_TEXT_LENGTH];
    char* upvotes = new char[REVIEW_UPVOTES_LENGTH];
    char* version = new char[REVIEW_VERSION_LENGTH];
    char* date = new char[REVIEW_DATE_LENGTH];


    int recordSize = RECORD_LENGTH*sizeof(char);

    if (arq) {
        arq.seekg(RECORD_LENGTH * i);
        int currentPos= recordSize * i;

        arq.read(review_id,REVIEW_ID_LENGTH);
        currentPos+=REVIEW_ID_LENGTH*sizeof(char);
        arq.seekg(currentPos);

        arq.read(review_text,REVIEW_TEXT_LENGTH);
        currentPos+=REVIEW_TEXT_LENGTH*sizeof(char) ;
        arq.seekg(currentPos);

        arq.read(upvotes,REVIEW_UPVOTES_LENGTH);
        currentPos+=REVIEW_UPVOTES_LENGTH*sizeof(char);
        arq.seekg(currentPos);

        arq.read(version,REVIEW_VERSION_LENGTH);
        currentPos+=REVIEW_VERSION_LENGTH*sizeof(char);
        arq.seekg(currentPos);

        arq.read(date,REVIEW_DATE_LENGTH);

        review->setReviewId(review_id);
        review_text[399]='\0'; //garantir que a string termina
        review->setReviewText(review_text);
        review->setUpvotes(stoi(upvotes));
        review->setAppVersion(version);
        review->setPostedDate(date);

        delete [] review_id;
        delete [] review_text;
        delete [] upvotes;
        delete [] version;
        delete [] date;

    }
    else {
        cout << "Arquivo nao aberto";
    }

    return review;
}

Review* FileIO::acessarRegistroTAD(int i, string binary_input){

    ifstream inputFile;
    inputFile.open(binary_input);
    Review* review = acessarRegistroTAD(i, inputFile);
    inputFile.close();

    return review;
}

vector<Review*> FileIO::importarAleatorios(string path, int num){

    vector<Review*> listaRegistros;
    listaRegistros.reserve(num);
    int numRegistros = 3646476;
    srand (std::chrono::high_resolution_clock::now().time_since_epoch().count());
    ifstream arq;
    arq.open(path, ios::binary);

    for(int i = 0; i < num; i++){
        int numRand = rand() % numRegistros;
        listaRegistros.push_back(acessarRegistroTAD(numRand, arq));

    }
    arq.close();

    return listaRegistros;
}


void FileIO::importarAleatoriosBTree(BTree &bTree, string path, int num){

    //int numRegistros = 3646476;
    int numRegistros = 10;
    srand (std::chrono::high_resolution_clock::now().time_since_epoch().count());
    ifstream arq;
    arq.open(path, ios::binary);

    for(int i = 0; i < num; i++){
        int numRand = rand() % numRegistros;

        Review* review = acessarRegistroTAD(numRand, arq);

        bTree.insert(review->getReviewId(), numRand);

    }
    arq.close();

}

void FileIO::importarAleatoriosVPTree(VPTree &vpTree, string path, int num) {

    int numRegistros = 10;
    srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    ifstream arq;
    arq.open(path, ios::binary);

    for (int i = 0; i < num; i++) {
        int numRand = rand() % numRegistros;

        Review *review = acessarRegistroTAD(numRand, arq);

        vpTree.insere(review->getReviewId() /*"00:" + to_string(i)*/, numRand);

    }
    arq.close();

};