#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Review.h"
#include "Sorting.h"
#include "LinearHashTable.h"
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

Review* acessarRegistroTAD(int i, ifstream& arq){

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

void imprimeListaRegistros(vector<Review*> listaRegistros){
    for(int i = 0; i < listaRegistros.size(); i++){
        cout << listaRegistros[i]->toString()<< endl;
    }
}

string imprimeListaRegistrosStr(vector<Review*> listaRegistros){
    string listaStr = "";
    for(int i = 0; i < listaRegistros.size(); i++){
       listaStr += listaRegistros[i]->toString() + "\n";
    }

    return listaStr;
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
    ifstream arq;

    arq.open(path, ios::binary);
    srand (time(0));


    cout << "TesteImportacao, digite:\n1 - saida na tela (10 registros)\n2 - saida no arquivo data.txt (100 registros)" << endl;
    cin >> option;

    for(int i = 0; i < (option == 1 ? 10 : 100); i++){
        int numRand = rand() % numRegistros;
        listaRegistros.push_back(acessarRegistroTAD(numRand, arq));
    }

    arq.close();

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

void appendArquivo(string output_path, string data){

    ofstream saida;
    saida.open(output_path, ios::app);
    saida << data;
    saida.close();
}

double geraMetricasFuncao(vector<Review*> &reviews, Sorting &sorting, int n){
    string res = "";
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    if(n == 0){
        res+="quicksort, ";
        //sorting.quickSort(reviews);
    }
    else if(n == 1){
        res+= "countingSort, ";
        sorting.countingSort(reviews);
    }
    else {
        res+="heapsort, ";
        sorting.heapSort(reviews);
    }

    high_resolution_clock::time_point fim = high_resolution_clock::now();

    double time = duration_cast<duration<double>>(fim - inicio).count();
    int comparisons = sorting.getLastAlgorithmComparisonCount();
    int swaps = sorting.getlastAlgorithmSwapCount();

    res += "tempo: " + to_string(time)
            + ", trocas: " + to_string(swaps)
            + ", comparações: " + to_string(comparisons)
            + ", tamanho lista: " + to_string(reviews.size());
    
    return time;
}


string tabelaHashN(string bin_file_path, int n){

    vector<Review*> reviews = importarAleatorios(bin_file_path, n);
    LinearHashTable linHT = LinearHashTable(0.7f);
    Sorting sorting =  Sorting();

    for(int i=0; i<reviews.size(); i++){
        if(!reviews[i]->getAppVersion().empty()){
            linHT.insert(reviews[i]->getAppVersion());
        }
    }

    vector<Cell*> cellVector = linHT.getTableAsVector();
    sorting.countingSortCells(cellVector);
    string ordFrequencia = sorting.printCellList(cellVector);
    ordFrequencia= "Versoes ordenadas por frequencia: \n" +ordFrequencia;


    for (int i = 0; i < reviews.size(); i++) {
        delete reviews[i];
    }
    return  ordFrequencia;
}

vector<Review*> trucateVector(vector<Review*> &v, int n){

    vector<Review*> res;
    for(int i=0; i< n && i< v.size(); i++){
        res.push_back(v[i]);
    }

    return res;
}

void simulacaoPerformaceOrdenacao(string output_file_path, string bin_file_path, string input_dir){

    Sorting sorting = Sorting();
    vector<Review*> reviews;
    string res;


    ///pega tamanho dos conjuntos de dados do arquivo .dat
    ifstream input;
    input.open(input_dir+"/input.dat", ios::in);

    if(!input){
        cout << "Nao foi encontrado o arquivo input.dat" << endl;
        return;
    }

    int quantidades[5];
    string line;
    for(int i = 0; i < 5; i++){

        getline(input, line);
        quantidades[i] = stoi(line);
    }

    input.close();
    ///********************


    cout<<"Importando registros aleatórios..."<<endl;
    reviews = importarAleatorios(bin_file_path, 1000000);

    int totalSwapCountSum=0, totalCompCountSum=0;
    double totalTimeSum=0;

    vector<string> nomesAlgoritmos = {"Quick sort", "Counting sort", "Heap sort"};
    for(int k=0; k<3; k++) {


        for (int j = 0; j < 5; j++) {
            int numReviews = quantidades[j];
            int swapCountSum=0, compCountSum=0;
            double timeSum=0;

            for (int i = 0; i < 3; i++) {

                vector<Review*> reviewsCopia = trucateVector(reviews, numReviews);
                double time = geraMetricasFuncao(reviewsCopia, sorting, k);

                res += nomesAlgoritmos[k]+ " - tempo: " + to_string(time)
                       + ", trocas: " + to_string(sorting.getlastAlgorithmSwapCount())
                       + ", comparações: " + to_string(sorting.getLastAlgorithmComparisonCount())
                       + ", tamanho lista: " + to_string(numReviews)+"\n";

                timeSum+=time;
                swapCountSum+=sorting.getlastAlgorithmSwapCount();
                compCountSum+=sorting.getLastAlgorithmComparisonCount();

            }
            res+="Medias- tempo: "+ to_string(timeSum/3)+", trocas: "+ to_string(swapCountSum/3) +", comparacoes: "+ to_string(compCountSum/3)+"\n\n";
            totalCompCountSum+=compCountSum;
            totalSwapCountSum+=swapCountSum;
            totalTimeSum+=timeSum;
        }

    }

    res+="Media geral - tempo: "+ to_string(totalTimeSum/10)+", trocas: "+ to_string(totalSwapCountSum/10) +", comparacoes: "+ to_string(totalCompCountSum/10)+"\n";
    res+= "(média feita considerando apenas os algoritmos heapsort e countingsort)\n";


    for (int i = 0; i < reviews.size(); i++) {
        delete reviews[i];
    }

    appendArquivo(output_file_path, res);
    cout << "Resultado gerado em " <<output_file_path << endl;
}


void deleteVectorItems(vector<Review*> &items){
    for (int i = 0; i < items.size(); i++) {
        delete items[i];
    }
}



string ordenaVetorN(string bin_file_path, int n){

    string resultado="";

    Sorting sorting = Sorting();
    vector<Review*> reviews = importarAleatorios(bin_file_path, n);

    vector<Review*> copiaReviews = reviews;
    sorting.quickSort(copiaReviews);
    resultado+= "-----------QUICKSORT-----------\n";
    resultado += imprimeListaRegistrosStr(copiaReviews);

    copiaReviews = reviews;
    sorting.heapSort(copiaReviews);
    resultado += "-----------HEAPSORT-----------\n";
    resultado += imprimeListaRegistrosStr(copiaReviews);

    copiaReviews = reviews;
    sorting.countingSort(copiaReviews);
    resultado += "-----------COUNTINGSORT-----------\n";
    resultado += imprimeListaRegistrosStr(copiaReviews);

    deleteVectorItems(reviews);

    //cout << "Saida do teste de ordenacao gerada ao final do arquivo " << result_output_path<<endl;
    //appendArquivo(result_output_path, resultado);
    return resultado;
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
        cout << "Erro ao abrir o arquivo"<< endl;
    }
}

void menu(string input_dir, string bin_file_path){
    int option;
    int i;
    cout << "1 - Funcao acessarRegistro (i)\n";
    cout << "2 - Funcao testeImportacao \n";
    cout << "3 - Gerar metricas dos algoritmos de ordenacao \n";
    cout << "4 - Ordenacao \n";
    cout << "5 - Hash \n";
    cout << "6 - Modulo de Teste \n";

    cin >> option;

    if(option == 1){
        cout << "Informe i: ";
        cin >> i;

        ifstream arq;
        arq.open(bin_file_path, ios::binary);

        Review* review = acessarRegistroTAD(i, arq);
        cout << review->toString();
        arq.close();

        delete review;
    }
    else if(option == 2){
        testeImportacao(bin_file_path);
    }
    else if(option == 3){
        simulacaoPerformaceOrdenacao("saida.txt", bin_file_path, input_dir);
    }
    else if(option == 4){

        int n;
        cout << "Informe n: " ;
        cin >> n;

        cout << ordenaVetorN(bin_file_path, n);
    }
    else if(option == 5){
        int n;
        cout << "Informe n: " ;
        cin >> n;

        cout << tabelaHashN(bin_file_path, n);
    }
    else if(option == 6){

        string resultadoOrdenacao = "Teste Ordenacao: \n" + ordenaVetorN(bin_file_path, 100) + "\n\n";
        string resultadoHash = "Teste Hash: \n" + tabelaHashN(bin_file_path, 100);

        appendArquivo("teste.txt", resultadoOrdenacao+ resultadoHash);

        cout << "Resultado escrito ao final do arquivo teste.txt" << endl;
    }
    else {
        cout << "Opcao invalida" << endl;
    }
}


int main(int argc, char **argv) {
    string input_dir;
    string input_file_path;
    string bin_file_path;

    if (argc == 2) {
        input_dir = argv[1];
        input_file_path = input_dir + "/tiktok_app_reviews.csv";
        bin_file_path = input_dir + "/data.bin";

    } else {
        cout << "Erro: era esperado caminho do arquivo de entrada." << endl;
        return 0;
    }

    ifstream binFile(bin_file_path);
    if(binFile.fail()){
        cout << "Binario nao encontrado. Gerando arquivo binario..." << endl;
        readCSVToBinary(input_file_path, bin_file_path);

        menu(input_dir, bin_file_path);
    }else{

        menu(input_dir, bin_file_path);
    }

    return 0;
}

