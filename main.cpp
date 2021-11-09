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
    char dados[1000];

    arq.open(path, ios::binary);

    if (!arq) {
        return;
    }
    //char teste[2] = {'a', 'b'};

    arq.read(dados,1000);
    arq.close();

    std::cout.write (dados, 1000);

      //  cout << teste;


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
           // cout << c;

            if (c == '\"') {
                ignoraVirgula = !ignoraVirgula;
            } else if ((c == ',' || c=='\n') && ignoraVirgula == false) {
              //  cout << '\n';

                if (campoAtual == 0) {
                    // review->setReviewId(value);
                    //arqOut.write(value.c_str(),sizeof(char)*89);
                    arqOut.write(value.c_str(),sizeof(char)*89);
                    cout << " - " <<value <<"\n" ;
                    campoAtual++;
                } else if (campoAtual == 1) {
                    // review->setReviewText(value);
                    cout << " - " <<value <<"\n" ;
                    campoAtual++;

                } else if (campoAtual == 2) {
                    //  review->setUpvotes(stoi(value));
                    cout << " - " <<value <<"\n" ;
                    campoAtual++;

                } else if (campoAtual == 3) {
                    //  review->setAppVersion(value);
                    cout << " - " <<value <<"\n" ;
                    campoAtual++;

                } else if (campoAtual == 4) {
                    // review->setPostedDate(value);
                    cout << " - " <<value <<"\n" ;
                    campoAtual = 0;
                    cout<< "";
                }

                value.clear();
                /*if(campoAtual <4){
                     campoAtual++;
                }else{
                    campoAtual = 0;
                }*/

            } else {
                //cout<< c;
                value += c;
                //value.clear();
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
    std::cout << "Trabalho ED2" << std::endl;
    string input_file;

    //conferir("../tiktok_app_reviews.csv");

    //readBin("../data.bin");
    readCharacteres("../data.csv");

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


