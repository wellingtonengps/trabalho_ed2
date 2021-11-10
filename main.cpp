#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "Review.h"

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

void readBin(string path) {

    ifstream arq;
    char dados[2621];
    char* review_id = new char[90];
    char* review_text = new char[2500];
    char* upvotes = new char[6];
    char* version = new char[9];
    char* date = new char[20];

    arq.open(path, ios::binary);
    int recordSize = 2625*sizeof(char);

    if (!arq) {
        return;
    }

    arq.seekg(0, arq.end);
    int length = arq.tellg();
    arq.seekg(0, arq.beg);
    int currentPos=0;

    for(int i=1; recordSize*(i-1) < length; i++){
        arq.read(review_id,90);
        currentPos+=90*sizeof(char);
        arq.seekg(currentPos);

        arq.read(review_text,2500);
        currentPos+=2500*sizeof(char);
        arq.seekg(currentPos);

        arq.read(upvotes,6);
        currentPos+=6*sizeof(char);
        arq.seekg(currentPos);

        arq.read(version,9);
        currentPos+=9*sizeof(char);
        arq.seekg(currentPos);

        arq.read(date,20);
        currentPos+=20*sizeof(char);
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

    delete [] review_id;
    delete [] review_text;
    delete [] upvotes;
    delete [] version;
    delete [] date;
}

void readCharacteres(string path) {

    FILE *arq;
    char c;

    ofstream arqOut;

    arqOut.open("../data.bin", ios::binary);

    arq = fopen(path.c_str(), "r");


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
                arqOut.write(value.c_str(), sizeof(char) * 90);
                cout << " - " << value << "\n";
                campoAtual++;
            } else if (campoAtual == 1) {
                arqOut.write(value.c_str(), sizeof(char) * 2500);
                cout << " - " << value << "\n";
                campoAtual++;

            } else if (campoAtual == 2) {

                arqOut.write(value.c_str(), sizeof(char) * 6);
                cout << " - " << value << "\n";
                campoAtual++;

            } else if (campoAtual == 3) {
                //  review->setAppVersion(value);
                arqOut.write(value.c_str(), sizeof(char) * 9);
                cout << " - " << value << "\n";
                campoAtual++;

            } else if (campoAtual == 4) {
                // review->setPostedDate(value);
                arqOut.write(value.c_str(), sizeof(char) * 20);
                cout << " - " << value << "\n";
                campoAtual = 0;
                cout << "";
            }

            value.clear();


        } else {
                value += c;
            }
        }
        arqOut.close();
        fclose(arq);
    } else {
        printf("Error ao abrir o arquivo");
    }


}

void read(string path) {
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


int main(int argc, char **argv) {
    //std::cout << "Trabalho ED2" << std::endl;
    string input_file;

    //conferir("../tiktok_app_reviews.csv");

    readBin("../data.bin");
    //readCharacteres("../data2.csv");

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


