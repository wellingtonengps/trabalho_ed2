#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
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

void conferir(string path){
    ifstream inputFile;
    inputFile.open(path, ios::in);
    string linha;
    while(!inputFile.eof()){
        getline(inputFile, linha);

        //cout << linha << endl;
        if(linha[0]!='g' && linha[1]!='p' && linha[2]!=':'){
            cout <<"Merda!"<<endl;
            cout<<linha<<endl;
        }

    }
}


void readCaracteres(string path){

    FILE *arq;
    char c;

    arq = fopen("../data.csv", "r");

    if(arq != NULL){
         bool ignoraVirgula = false;
         int campoAtual =0;
         string value;

        while((c = fgetc(arq)) != EOF ){
            cout << c;

        if(c=='\"'){
            ignoraVirgula=!ignoraVirgula;
        }
        else if(c==',' && ignoraVirgula==false){
            cout << '\n';

            if(campoAtual==0){
               // review->setReviewId(value);
               cout << value << " - ";
            }else if(campoAtual==1){
               // review->setReviewText(value);
                cout << value << " - ";
            } else if(campoAtual==2){
              //  review->setUpvotes(stoi(value));
                cout << value << " - ";
            } else if(campoAtual==3){
              //  review->setAppVersion(value);
                cout << value << " - ";
            } else if(campoAtual==4){
               // review->setPostedDate(value);
                cout << value << " - ";

            }
            value.clear();
            campoAtual++;
        }else{
            //cout<< c;
            value+=c;
            campoAtual=0;
            value.clear();
        }
    }
        fclose(arq);
    }
    else{
        printf("Error ao abrir o arquivo");
    }


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

    //conferir("../tiktok_app_reviews.csv");

    readCaracteres("../data.csv");

    return 0;

    if(argc == 2) {
        input_file = argv[1];

    }else{
        cout << "Erro: era esperado caminho do arquivo de entrada."<<endl;
        //return 0;
    }

    read("../data.csv");


    return 0;
}


