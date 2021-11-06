#include <iostream>
#include <string>
#include <fstream>
#include "Review.h"

using namespace std;

void read(string path){
    ifstream inputFile;
    string linha;
    inputFile.open(path, ios::in);
    Review* review;

    if(!inputFile){
        return ;
    }

    getline(inputFile, linha);
    while(!inputFile.eof()){
        getline(inputFile, linha);
        review =readLine(linha);
        cout << linha << endl;
        delete review;
    }

    inputFile.close();

}

int main(int argc, char ** argv) {
    std::cout << "Trabalho ED2" << std::endl;
    string input_file;

    if(argc == 2) {
        input_file = argv[1];

    }else{
        cout << "Erro: era esperado caminho do arquivo de entrada."<<endl;
        return 0;
    }

    read("../data.csv");

    return 0;
}


