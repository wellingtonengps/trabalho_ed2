#include <iostream>
#include <string>
#include <fstream>
#include "Review.h"

using namespace std;


Review* readLine(string line){
    Review* review = new Review();
    bool ignoraVirgula = false;
    int campoAtual =0;
    string value;

    for(int i=0; i<line.length(); i++){


        if(line[i]=='\"'){
            ignoraVirgula=!ignoraVirgula;
        }
        else if(line[i]==',' && ignoraVirgula==false){
             cout << '\n';

             if(campoAtual==0){
                 review->setReviewId(value);
             }else if(campoAtual==1){
                 review->setReviewText(value);
             } else if(campoAtual==2){
                 review->setUpvotes(stoi(value));
             } else if(campoAtual==3){
                 review->setAppVersion(value);
             } else if(campoAtual==4){
                 review->setPostedDate(value);
             }

             value.clear();
             campoAtual++;
        }else{
            cout<< line[i] ;
            value+=line[i];
        }

    }
    cout << endl;
    review->setPostedDate(value);
    return  review;

}

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
        //return 0;
    }

    read("../data.csv");

    return 0;
}


