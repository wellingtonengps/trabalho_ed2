#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Review.h"
#include "Sorting.h"
#include <time.h>
#include <vector>
#include <chrono>
#include <thread>


int REVIEW_TEXT_LENGTH = 400;
int REVIEW_ID_LENGTH = 90;
int REVIEW_UPVOTES_LENGTH = 6;
int REVIEW_VERSION_LENGTH = 9;
int REVIEW_DATE_LENGTH = 20;
int RECORD_LENGTH = REVIEW_TEXT_LENGTH + REVIEW_ID_LENGTH + REVIEW_UPVOTES_LENGTH + REVIEW_VERSION_LENGTH + REVIEW_DATE_LENGTH;

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

// *********************Funções de Buffer********************


int nextChar=0;
int maxBlockSize = 100000;
char* dados = new char[maxBlockSize];
int currentBlock =0;
int fileSize;
bool endOfFile = false;
ifstream arqI;


//inicializa arquivo para leitura no buffer
void initFile(string path){
    nextChar=0;
    currentBlock=0;
    endOfFile=false;

    arqI.open(path, ios::binary);
    arqI.seekg(0, arqI.end);
    fileSize = arqI.tellg();
    arqI.seekg(0, arqI.beg);
}

//armazena bloco do arquivo no buffer
void bufferFile(){

    if (!arqI) {
        return;
    }
    arqI.seekg(maxBlockSize*currentBlock);
    arqI.read(dados, maxBlockSize);
}

//retorna próximo caracter a ser lido no buffer
char getNextChar(){

    //armazena primeiro bloco no buffer
    if(currentBlock==0 && nextChar==0){
        bufferFile();
    }

    char c = dados[nextChar];

    //se no final do bloco, carrega próximo bloco
    //caso contrário, incrementa contador nextChar
    if(nextChar== maxBlockSize-1){
        currentBlock++;
        nextChar=0;
        bufferFile();
    } else{
        nextChar++;
    }

    //se no final do arquivo, desaloca o buffer e fecha o arquivo
    if((nextChar+ currentBlock*maxBlockSize)*sizeof(char) >= fileSize){
        endOfFile=true;
        arqI.close();
        delete [] dados;
    }

    return c;
}

//**********************************************************************

Review* acessarRegistroTAD(int i, string path){

    Review *review = new Review();

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

        arq.close();
    }
    else {
        cout << "Arquivo nao aberto";
    }

    return review;
}

void imprimeListaRegistros(vector<Review*> listaRegistros){
    for(int i = 0; i < listaRegistros.size(); i++){
        cout << listaRegistros[i]->toString()<< endl;
    }
}

void imprimeListaRegistrosArquivo(vector<Review*> listaRegistros, string output_path){

    ofstream saida;
    saida.open(output_path, ios::out);

    if(!saida){
        cout << "Não foi possível gerar arquivo data.txt contendo lista de registros"<< endl;
        return;
    }

    for(int i = 0; i < listaRegistros.size(); i++){
        saida << listaRegistros[i]->toString()<< "\n";
    }
    saida.close();

}

void testeImportacao(string path){

    vector<Review*> listaRegistros;
    int option;
    int numRegistros = 3646476;
    srand (time(0));

    cout << "TesteImportacao, digite:\n1 - saida na tela (10 registros)\n2 - saida no arquivo data.txt (100 registros)" << endl;
    cin >> option;

    for(int i = 0; i < (option == 1 ? 10 : 100); i++){
        int numRand = rand() % numRegistros;
        listaRegistros.push_back(acessarRegistroTAD(numRand, path));
    }

    if(option == 1){
        imprimeListaRegistros(listaRegistros);
    }
    else if(option == 2){
        imprimeListaRegistrosArquivo(listaRegistros, "data.txt");

    }

    for(int i = 0; i < listaRegistros.size(); i++){
        delete listaRegistros[i];
    }
}

vector<Review*> importarAleatorios(string path, int num){

    vector<Review*> listaRegistros;
    int numRegistros = 3646476;
    srand (std::chrono::high_resolution_clock::now().time_since_epoch().count());

    for(int i = 0; i < num; i++){
        int numRand = rand() % numRegistros;
        listaRegistros.push_back(acessarRegistroTAD(numRand, path));
    }

    /*for(int i = 0; i < listaRegistros.size(); i++){
        delete listaRegistros[i];
    }*/
    return listaRegistros;
}


string testaFuncao(vector<Review*> &reviews, Sorting sorting){
    string res = "";
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    sorting.heapSort(reviews);
    high_resolution_clock::time_point fim = high_resolution_clock::now();

    double time = duration_cast<duration<double>>(fim - inicio).count();
    int comparisons = sorting.getLastAlgorithmComparisonCount();
    int swaps = sorting.getlastAlgorithmSwapCount();

    res += "tempo: " + to_string(time) + ", trocas: " + to_string(swaps) + ", comparações: " + to_string(comparisons);
    
    return res;
}


void testePerformaceOrdenacao(string path, int num){

    Sorting sorting = Sorting();

    vector<Review*> reviews;

    //10000 - 0

    //50000 - 1

    //100000 - 2

    //500000 - 3

    //1000000 - 4

    int quantidades[5] = {10000, 50000, 100000, 500000, 1000000};

    for(int i = 0; i < 3; i++){
        reviews = importarAleatorios(path, quantidades[num]);
        cout << testaFuncao(reviews,sorting) << "\n";

        for(int i = 0; i < reviews.size(); i++){
            delete reviews[i];
        }

       // sleep_for(seconds(1));
    }


}


void readCSVToBinary(string path, string binaryOut) {

    char c;

    ofstream arqOut;
    arqOut.open(binaryOut, ios::binary);

    initFile(path);
    bool primeiraLinha=true;


    if (arqOut) {
        bool ignoraVirgula = false;
        int campoAtual = 0;
        string value;

        //lê dados do arquivo de entrada caractere por caractere
        //escrevendo os dados no arquivo de saída
        while (!endOfFile) {
            c= getNextChar();

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
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_ID_LENGTH);
                    campoAtual++;
                } else if (campoAtual == 1 ) {
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_TEXT_LENGTH);
                    campoAtual++;
                } else if (campoAtual == 2 ) {
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_UPVOTES_LENGTH);
                    campoAtual++;
                } else if (campoAtual == 3 ) {
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_VERSION_LENGTH);
                    campoAtual++;
                } else if (campoAtual == 4 ) {
                    arqOut.write(value.c_str(), sizeof(char) * REVIEW_DATE_LENGTH);
                    campoAtual = 0;
                }

                value.clear();


            } else {
                value += c;
            }
        }

        arqOut.close();
    } else {
        cout << "Error ao abrir o arquivo"<< endl;
    }
}

void menu(string input_file_path, string output_file_path){
    int option;
    int i;
    cout << "1 - Funcao acessarRegistro (i)\n2 - Funcao testeImportacao " << endl;
    cin >> option;

    if(option == 1){
        cout << "Informe i: ";
        cin >> i;
        Review* review = acessarRegistroTAD(i, output_file_path);
        cout << review->toString();

        delete review;
    }
    else if(option == 2){
        testeImportacao(output_file_path);
    }
    else {
        cout << "Opcao invalida" << endl;
    }
}

int main(){
    testePerformaceOrdenacao("data.bin", 0);

    return 0;
}

int main2(int argc, char **argv) {
    string input_dir;
    string input_file_path;
    string output_file_path;

    if (argc == 2) {
        input_dir = argv[1];
        input_file_path = input_dir + "/tiktok_app_reviews.csv";
        output_file_path = input_dir + "/data.bin";

    } else {
        cout << "Erro: era esperado caminho do arquivo de entrada." << endl;
        return 0;
    }

    ifstream binFile(output_file_path);
    if(binFile.fail()){
        cout << "Binario nao encontrado. Gerando arquivo binario..." << endl;
        readCSVToBinary(input_file_path, output_file_path);

        menu(input_file_path, output_file_path);
    }else{
       // testeImportacao(output_file_path);
        menu(input_file_path, output_file_path);
    }

    return 0;
}

