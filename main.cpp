#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include "Review.h"
#include "FileIO.h"
#include <memory>
#include <time.h>
#include <vector>


int REVIEW_TEXT_LENGTH = 400;
int REVIEW_ID_LENGTH = 90;
int REVIEW_UPVOTES_LENGTH = 6;
int REVIEW_VERSION_LENGTH = 9;
int REVIEW_DATE_LENGTH = 20;
int RECORD_LENGTH = REVIEW_TEXT_LENGTH + REVIEW_ID_LENGTH + REVIEW_UPVOTES_LENGTH + REVIEW_VERSION_LENGTH + REVIEW_DATE_LENGTH;

using namespace std;

Review *readLine(string line) {
    Review *review = new Review();
    bool ignoraVirgula = false;
    int campoAtual = 0;
    string value;

    for (int i = 0; i < line.length(); i++) {


        if (line[i] == '\"') {
            ignoraVirgula = !ignoraVirgula;
        } else if (line[i] == ',' && ignoraVirgula == false) {
            cout << '\n';

            if (campoAtual == 0) {
                review->setReviewId(value);
            } else if (campoAtual == 1) {
                review->setReviewText(value);
            } else if (campoAtual == 2) {
                review->setUpvotes(stoi(value));
            } else if (campoAtual == 3) {
                review->setAppVersion(value);
            } else if (campoAtual == 4) {
                review->setPostedDate(value);
            }

            value.clear();
            campoAtual++;
        } else {
            cout << line[i];
            value += line[i];
        }

    }
    cout << endl;
    review->setPostedDate(value);
    return review;

}

void conferir(string path) {
    ifstream inputFile;
    inputFile.open(path, ios::in);
    string linha;
    while (!inputFile.eof()) {
        getline(inputFile, linha);

        //cout << linha << endl;
        if (linha[0] != 'g' && linha[1] != 'p' && linha[2] != ':') {
            cout << "Merda!" << endl;
            cout << linha << endl;
        }

    }
}

void readLegacy(string path) {
    ifstream inputFile;
    string linha;
    inputFile.open(path, ios::in);
    Review *review;

    if (!inputFile) {
        return;
    }


    getline(inputFile, linha);
    while (!inputFile.eof()) {
        getline(inputFile, linha);
        review = readLine(linha);
        cout << linha << endl;
        delete review;
    }

    inputFile.close();

}

/////////////*************************************



int nextChar=0;
int maxBlockSize = 100000;
char* dados = new char[maxBlockSize];
int currentBlock =0;
int fileSize;
bool endOfFile = false;
ifstream arqI;


void initFile(string path){
    nextChar=0;
    currentBlock=0;
    endOfFile=false;

    arqI.open(path, ios::binary);
    arqI.seekg(0, arqI.end);
    fileSize = arqI.tellg();
    arqI.seekg(0, arqI.beg);
}

void bufferFile(){
    //char dados[maxBlockSize];
    //ifstream arq;

   // arq.open(path, ios::binary);
    if (!arqI) {
        return;
    }
    arqI.seekg(maxBlockSize*currentBlock);
    arqI.read(dados, maxBlockSize);

    //cout.write (dados, maxBlockSize);

    //arqI.close();
}

char getNextChar(){
    if(currentBlock==0 && nextChar==0){
        bufferFile();
    }

    char c = dados[nextChar];
   // cout << c << "";

    if(nextChar== maxBlockSize-1){
        currentBlock++;
        nextChar=0;
        bufferFile();
    } else{
        nextChar++;
    }

    if((nextChar+ currentBlock*maxBlockSize)*sizeof(char) >= fileSize){
        endOfFile=true;
        arqI.close();
        delete [] dados;
        cout << "EOFFFF !!!!!-----"<<endl;
    }

    return c;
}



void acessarRegistro(int i, string path){
    ifstream arq;


    char* review_id = new char[REVIEW_ID_LENGTH];
    char* review_text = new char[REVIEW_TEXT_LENGTH];
    char* upvotes = new char[REVIEW_UPVOTES_LENGTH];
    char* version = new char[REVIEW_VERSION_LENGTH];
    char* date = new char[REVIEW_DATE_LENGTH];

    arq.open(path, ios::binary);

    int recordSize = RECORD_LENGTH*sizeof(char);

    if (!arq) {
        return;
    }

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


    cout << review_id;
    cout << endl;

    cout << review_text;
    cout <<endl;

    cout << upvotes;
    cout <<endl;

    cout << version;
    cout <<endl;

    cout << date;
    cout << endl;
    cout << endl;


    delete [] review_id;
    delete [] review_text;
    delete [] upvotes;
    delete [] version;
    delete [] date;



    arq.close();
}

unique_ptr<Review> acessarRegistroTAD(int i, string path){

    //Review *review = new Review();
    unique_ptr<Review>  review = unique_ptr<Review>(new Review());

    ifstream arq;

    char* review_id = new char[REVIEW_ID_LENGTH];
    char* review_text = new char[REVIEW_TEXT_LENGTH];
    char* upvotes = new char[REVIEW_UPVOTES_LENGTH];
    char* version = new char[REVIEW_VERSION_LENGTH];
    char* date = new char[REVIEW_DATE_LENGTH];

    arq.open(path, ios::binary);

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
        review->setReviewText(review_text);
        review->setUpvotes(stoi(upvotes));
        review->setAppVersion(version);
        review->setPostedDate(date);

        delete [] review_id;
        delete [] review_text;
        delete [] upvotes;
        delete [] version;
        delete [] date;

        arq.close();

        return review;
    }
    else {
        cout << "Arquivo nao aberto";
    }
}

void testeImportacao(string path){

    vector<unique_ptr<Review>> listaRegistros;

    int option;
    int numRegistros = 3646476;
    srand (time(0));

    ofstream saida;
    saida.open("../saida_teste.txt", ios::out);

    cout << "Tecle 1 - para saida na tela ou 2 - para saida em um arquivo txt: ";
    cin >> option;

    if(option == 1){
        for(int i = 0; i < 10; i++){
            int numRand = rand() % numRegistros;
            listaRegistros.push_back(acessarRegistroTAD(numRand, path));
        }

        for(int i = 0; i < listaRegistros.size(); i++){
            cout << listaRegistros[i]->toString();
        }

    }
    else if(option == 2){
        for(int i = 0; i < 100; i++){
            int numRand = rand() % numRegistros;
            listaRegistros.push_back(acessarRegistroTAD(numRand, path));
        }

        for(int i = 0; i < listaRegistros.size(); i++){
            saida << listaRegistros[i]->toString();
            cout << endl;
        }

        cout << "Arquido saida.txt gerado" << endl;
    }
    else {
        cout << "Opcao invalida";
    }

    //imprimir no arquivo usando
    //saida.write("", 123);
    saida.close();

}

/////////////*************************************

void readBin(string path) {


    ifstream arq;
    //char* dados = new char[2621];
    char* review_id = new char[REVIEW_ID_LENGTH];
    char* review_text = new char[REVIEW_TEXT_LENGTH];
    char* upvotes = new char[REVIEW_UPVOTES_LENGTH];
    char* version = new char[REVIEW_VERSION_LENGTH];
    char* date = new char[REVIEW_DATE_LENGTH];

    arq.open(path, ios::binary);
    int recordSize = RECORD_LENGTH*sizeof(char);

    if (!arq) {
        return;
    }

    arq.seekg(0, arq.end);
    int length = arq.tellg();
    arq.seekg(0, arq.beg);
    int currentPos=0;

    for(int i=1; recordSize*(i-1) < length; i++){
        arq.read(review_id,REVIEW_ID_LENGTH);
        currentPos+=REVIEW_ID_LENGTH*sizeof(char);
        arq.seekg(currentPos);

        arq.read(review_text,REVIEW_TEXT_LENGTH);
        currentPos+=REVIEW_TEXT_LENGTH*sizeof(char);
        arq.seekg(currentPos);

        arq.read(upvotes,REVIEW_UPVOTES_LENGTH);
        currentPos+=REVIEW_UPVOTES_LENGTH*sizeof(char);
        arq.seekg(currentPos);

        arq.read(version,REVIEW_VERSION_LENGTH);
        currentPos+=REVIEW_VERSION_LENGTH*sizeof(char);
        arq.seekg(currentPos);

        arq.read(date,REVIEW_DATE_LENGTH);
        currentPos+=REVIEW_DATE_LENGTH*sizeof(char);
        arq.seekg(currentPos);


        cout << review_id;
        cout << endl;

        cout << review_text;
        cout <<endl;

        cout << upvotes;
        cout <<endl;

        cout << version;
        cout <<endl;

        cout << date;
        cout << endl;
        cout << endl;

        //arq.seekg(recordSize*i);
    }

    //char teste[2] = {'a', 'b'};

    //arq.read(dados,2621);
    arq.close();

    //std::cout.write (dados, 2621);

      //  cout << teste;

    //delete [] dados;
    delete [] review_id;
    delete [] review_text;
    delete [] upvotes;
    delete [] version;
    delete [] date;
}


void readTeste(string path) {

   // FILE *arq;
    char c;

    ofstream arqOut;
    arqOut.open("../teste2.bin", ios::binary);

    //arq = fopen(path.c_str(), "r");
    initFile(path);


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
                    //cout << " - " << value << "\n";
                    campoAtual++;
                } else if (campoAtual == 1) {
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_TEXT_LENGTH);
                    //cout << " - " << value << "\n";
                    campoAtual++;

                } else if (campoAtual == 2) {

                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_UPVOTES_LENGTH);
                    //cout << " - " << value << "\n";
                    campoAtual++;

                } else if (campoAtual == 3) {
                    //  review->setAppVersion(value);
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_VERSION_LENGTH);
                    //cout << " - " << value << "\n";
                    campoAtual++;

                } else if (campoAtual == 4) {
                    // review->setPostedDate(value);
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_DATE_LENGTH);
                    //cout << " - " << value << "\n";
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


void read(string path) {

    FILE *arq;
    char c;

    ofstream arqOut;

    arqOut.open("../teste700v2.bin", ios::binary);

    arq = fopen(path.c_str(), "r");
    int numRegistros=0;


    if (arq != NULL && arqOut) {
        bool ignoraVirgula = false;
        int campoAtual = 0;
        string value;
        string teste = "ab";


        while ((c = fgetc(arq)) != EOF) {

            if (c == '\"') {
                ignoraVirgula = !ignoraVirgula;
            } else if ((c == ',' || c == '\n') && ignoraVirgula == false){
                value += '\0';

            if (campoAtual == 0) {
                arqOut.write(value.c_str(), sizeof(char) * REVIEW_ID_LENGTH);
                //cout << " - " << value << "\n";
                campoAtual++;
            } else if (campoAtual == 1) {
                arqOut.write(value.c_str(), sizeof(char) * REVIEW_TEXT_LENGTH);
                //cout << " - " << value << "\n";
                campoAtual++;

            } else if (campoAtual == 2) {

                arqOut.write(value.c_str(), sizeof(char) * REVIEW_UPVOTES_LENGTH);
                //cout << " - " << value << "\n";
                campoAtual++;

            } else if (campoAtual == 3) {
                //  review->setAppVersion(value);
                arqOut.write(value.c_str(), sizeof(char) * REVIEW_VERSION_LENGTH);
                //cout << " - " << value << "\n";
                campoAtual++;

            } else if (campoAtual == 4) {
                // review->setPostedDate(value);
                arqOut.write(value.c_str(), sizeof(char) * REVIEW_DATE_LENGTH);
                //cout << " - " << value << "\n";
                campoAtual = 0;
                //cout << "";
                numRegistros++;
            }

            value.clear();


        } else {
                value += c;
            }
        }

        //TODO: gravar o último campo do último registro:
         //value += '\0';
         //arqOut.write(value.c_str(), sizeof(char) * REVIEW_DATE_LENGTH);
         //numRegistros++;
        cout << "Registros lidos: " << numRegistros << endl;
        arqOut.close();
        fclose(arq);
    } else {
        printf("Error ao abrir o arquivo");
    }


}



int main(int argc, char **argv) {
    //std::cout << "Trabalho ED2" << std::endl;
    string input_file;

    //conferir("../tiktok_app_reviews.csv");

    //FileIO fileIo =  FileIO("../tiktok_app_reviews.csv", 100000);
    //fileIo.readToBinary("../teste.bin");
    //fileIo.close();

    //readTeste("../data.csv");
    //readTeste("../tiktok_app_reviews.csv");
    //readBin("../teste2.bin");
    //read("../tiktok_app_reviews.csv");
    //read("../data.csv");
    //acessarRegistro(3646476, "../teste2.bin"); //1908874

    //cout << acessarRegistroTAD(3646476, "../teste2.bin")->toString() << endl;

    testeImportacao("../teste2.bin");


    //system("pause");

    return 0;

    if (argc == 2) {
        input_file = argv[1];

    } else {
        cout << "Erro: era esperado caminho do arquivo de entrada." << endl;
        //return 0;
    }

    read("../data.csv");


    return 0;
}


