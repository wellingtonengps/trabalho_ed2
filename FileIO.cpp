//
// Created by welli on 11/20/2021.
//

#include "FileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ifstream inputFile;

FileIO::FileIO(string path, int bufferSize){
    nextChar=0;
    currentBlock=0;
    endOfFile=false;
    this->bufferSize = bufferSize;
    dados = new char[bufferSize];
    ifstream newInputFile;
    newInputFile.open(path, ios::binary);
    inputFile.seekg(0, inputFile.end);
    fileSize = inputFile.tellg();
    inputFile.seekg(0, inputFile.beg);
}



FileIO::~FileIO() {
    delete [] dados;
}

void FileIO::bufferChunk(){

    if (!inputFile) {
        return;
    }
    inputFile.seekg(bufferSize*currentBlock);
    inputFile.read(dados, bufferSize);

}

char FileIO::getNextChar(){
    if(currentBlock==0 && nextChar==0){
        bufferChunk();
    }

    char c = dados[nextChar];
    // cout << c << "";

    if(nextChar== bufferSize-1){
        currentBlock++;
        nextChar=0;
        bufferChunk();
    } else{
        nextChar++;
    }

    if((nextChar+ currentBlock*bufferSize)*sizeof(char) >= fileSize){
        endOfFile=true;
        //inputFile.close();
        delete [] dados;
        cout << "EOFFFF !!!!!-----"<< endl;
    }

    return c;
}

void FileIO::close() {
    inputFile.close();
}

void FileIO::readToBinary(string path) {

    char c;

    ofstream arqOut;
    arqOut.open(path, ios::binary);


    if (arqOut) {
        bool ignoraVirgula = false;
        int campoAtual = 0;
        string value;
        string teste = "ab";


        while (!endOfFile) {

            c= getNextChar();

            if (c == '\"') {
                ignoraVirgula = !ignoraVirgula;
            } else if ((c == ',' || c == '\n') && ignoraVirgula == false){
                value += '\0';

                if (campoAtual == 0) {
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_ID_LENGTH);
                    cout << " - " << value << "\n";
                    campoAtual++;
                } else if (campoAtual == 1) {
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_TEXT_LENGTH);
                    cout << " - " << value << "\n";
                    campoAtual++;

                } else if (campoAtual == 2) {

                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_UPVOTES_LENGTH);
                    cout << " - " << value << "\n";
                    campoAtual++;

                } else if (campoAtual == 3) {
                    //  review->setAppVersion(value);
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_VERSION_LENGTH);
                    cout << " - " << value << "\n";
                    campoAtual++;

                } else if (campoAtual == 4) {
                    // review->setPostedDate(value);
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_DATE_LENGTH);
                    cout << " - " << value << "\n";
                    campoAtual = 0;
                    //cout << "";
                }

                value.clear();


            } else {
                value += c;
            }
        }

        // value += '\0';
        // arqOut.write(value.c_str(), sizeof(char) * REVIEW_DATE_LENGTH);
        arqOut.close();
        //fclose(arq);
    } else {
        printf("Error ao abrir o arquivo");
    }


}