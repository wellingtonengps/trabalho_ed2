#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Review.h"
#include "Sorting.h"
#include "LinearHashTable.h"
#include "BTree.h"
#include "VPTree.h"
#include "FileIO.h"
#include <time.h>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include "Metricas.h"


using namespace std;
using namespace std::chrono;
//using namespace std::this_thread;


void testeImportacao(string path) {

    vector<Review *> listaRegistros;
    int option;
    int numRegistros = 3646476;
    ifstream arq;
    FileIO fileIo = FileIO();


    arq.open(path, ios::binary);
    srand(time(0));


    cout << "TesteImportacao, digite:\n1 - saida na tela (10 registros)\n2 - saida no arquivo data.txt (100 registros)"
         << endl;
    cin >> option;

    for (int i = 0; i < (option == 1 ? 10 : 100); i++) {
        int numRand = rand() % numRegistros;
        listaRegistros.push_back(fileIo.acessarRegistroTAD(numRand, arq));
    }

    arq.close();

    if (option == 1) {
        fileIo.imprimeListaRegistros(listaRegistros);
    } else if (option == 2) {
        fileIo.imprimeListaRegistrosArquivo(listaRegistros, "data.txt");

    }

    for (int i = 0; i < listaRegistros.size(); i++) {
        delete listaRegistros[i];
    }
}


double geraMetricasFuncao(vector<Review *> &reviews, Sorting &sorting, int n) {
    string res = "";
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    if (n == 0) {
        res += "quicksort, ";
        //sorting.quickSort(reviews);
    } else if (n == 1) {
        res += "countingSort, ";
        sorting.countingSort(reviews);
    } else {
        res += "heapsort, ";
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


string tabelaHashN(string bin_file_path, int n) {

    FileIO fileIo = FileIO();
    vector<Review *> reviews = fileIo.importarAleatorios(bin_file_path, n);
    LinearHashTable linHT = LinearHashTable(0.7f);
    Sorting sorting = Sorting();

    for (int i = 0; i < reviews.size(); i++) {
        if (!reviews[i]->getAppVersion().empty()) {
            linHT.insert(reviews[i]->getAppVersion());
        }
    }

    vector<Cell *> cellVector = linHT.getTableAsVector();
    sorting.countingSortCells(cellVector);
    string ordFrequencia = sorting.printCellList(cellVector);
    ordFrequencia = "Versoes ordenadas por frequencia: \n" + ordFrequencia;


    for (int i = 0; i < reviews.size(); i++) {
        delete reviews[i];
    }
    return ordFrequencia;
}

vector<Review *> trucateVector(vector<Review *> &v, int n) {

    vector<Review *> res;
    for (int i = 0; i < n && i < v.size(); i++) {
        res.push_back(v[i]);
    }

    return res;
}

void simulacaoPerformaceOrdenacao(string output_file_path, string bin_file_path, string input_dir) {

    Sorting sorting = Sorting();
    vector<Review *> reviews;
    string res;
    FileIO fileIo = FileIO();


    ///pega tamanho dos conjuntos de dados do arquivo .dat
    ifstream input;
    input.open(input_dir + "/input.dat", ios::in);

    if (!input) {
        cout << "Nao foi encontrado o arquivo input.dat" << endl;
        return;
    }

    int quantidades[5];
    string line;
    for (int i = 0; i < 5; i++) {

        getline(input, line);
        quantidades[i] = stoi(line);
    }

    input.close();
    ///********************


    cout << "Importando registros aleatórios..." << endl;
    reviews = fileIo.importarAleatorios(bin_file_path, 1000000);

    int totalSwapCountSum = 0, totalCompCountSum = 0;
    double totalTimeSum = 0;

    vector<string> nomesAlgoritmos = {"Quick sort", "Counting sort", "Heap sort"};
    for (int k = 0; k < 3; k++) {


        for (int j = 0; j < 5; j++) {
            int numReviews = quantidades[j];
            int swapCountSum = 0, compCountSum = 0;
            double timeSum = 0;

            for (int i = 0; i < 3; i++) {

                vector<Review *> reviewsCopia = trucateVector(reviews, numReviews);
                double time = geraMetricasFuncao(reviewsCopia, sorting, k);

                res += nomesAlgoritmos[k] + " - tempo: " + to_string(time)
                       + ", trocas: " + to_string(sorting.getlastAlgorithmSwapCount())
                       + ", comparações: " + to_string(sorting.getLastAlgorithmComparisonCount())
                       + ", tamanho lista: " + to_string(numReviews) + "\n";

                timeSum += time;
                swapCountSum += sorting.getlastAlgorithmSwapCount();
                compCountSum += sorting.getLastAlgorithmComparisonCount();

            }
            res += "Medias- tempo: " + to_string(timeSum / 3) + ", trocas: " + to_string(swapCountSum / 3) +
                   ", comparacoes: " + to_string(compCountSum / 3) + "\n\n";
            totalCompCountSum += compCountSum;
            totalSwapCountSum += swapCountSum;
            totalTimeSum += timeSum;
        }

    }

    res += "Media geral - tempo: " + to_string(totalTimeSum / 10) + ", trocas: " + to_string(totalSwapCountSum / 10) +
           ", comparacoes: " + to_string(totalCompCountSum / 10) + "\n";
    res += "(média feita considerando apenas os algoritmos heapsort e countingsort)\n";


    for (int i = 0; i < reviews.size(); i++) {
        delete reviews[i];
    }

    fileIo.appendArquivo(output_file_path, res);
    cout << "Resultado gerado em " << output_file_path << endl;
}


void deleteVectorItems(vector<Review *> &items) {
    for (int i = 0; i < items.size(); i++) {
        delete items[i];
    }
}


string ordenaVetorN(string bin_file_path, int n) {

    string resultado = "";
    FileIO fileIo = FileIO();

    Sorting sorting = Sorting();
    vector<Review *> reviews = fileIo.importarAleatorios(bin_file_path, n);

    vector<Review *> copiaReviews = reviews;
    sorting.quickSort(copiaReviews);
    resultado += "-----------QUICKSORT-----------\n";
    resultado += fileIo.imprimeListaRegistrosStr(copiaReviews);

    copiaReviews = reviews;
    sorting.heapSort(copiaReviews);
    resultado += "-----------HEAPSORT-----------\n";
    resultado += fileIo.imprimeListaRegistrosStr(copiaReviews);

    copiaReviews = reviews;
    sorting.countingSort(copiaReviews);
    resultado += "-----------COUNTINGSORT-----------\n";
    resultado += fileIo.imprimeListaRegistrosStr(copiaReviews);

    deleteVectorItems(reviews);

    //cout << "Saida do teste de ordenacao gerada ao final do arquivo " << result_output_path<<endl;
    //appendArquivo(result_output_path, resultado);
    return resultado;
}

void metricasCompressao(string binary_input_file, string output_file){

    FileIO fileIo = FileIO();
    float somaTaxaCompressao=0;
    string res;
    res += "Médias Compressão:\n";

    int n[3] = {1,2,3};

    for(int i = 0; i < 3; i++){
        string data = fileIo.importarAleatoriosCompression(binary_input_file, n[i]);

        for(int j = 0; j < 3; j++){
            Compression compression = Compression();
            compression.gerarArvore(data);
            compression.gerarTabela();

            string compressedData = compression.compress(data);
            string codedString = compression.readBinaryString(compressedData);

            ///teste
            //string convertedBack = compression.readCompressedText(codedString);
            //cout << compression.decompress(convertedBack)<<endl;

            somaTaxaCompressao += compression.taxaCompressao();
            cout << "Taxa de compressao: " << compression.taxaCompressao() << endl;
        }

        float mediaTaxa = somaTaxaCompressao/3;
        cout << mediaTaxa << endl;

        res += "Iteracao-" + to_string(n[i]) + ": " + to_string(mediaTaxa);
        res += "\n";

        somaTaxaCompressao=0;
    }

    fileIo.appendArquivo(output_file, res);
    cout << "saida.txt gerado" << endl;
}

void metricasArvoreVP(string binary_input_file, string output_file, int n, int b) {


    FileIO fileIo = FileIO();
    string res;

    //vector<Review*> data =  fileIo.importarAleatorios(binary_input_file, 100);

    res += "Arvore Vermelho e Preto\n";

    VPTree vpTree = VPTree();

    high_resolution_clock::time_point inicio;
    high_resolution_clock::time_point fim;
    double time;


    for(int i = 0; i < 3; i++){

        inicio = high_resolution_clock::now();
        fileIo.importarAleatoriosVPTree(vpTree, binary_input_file, n);
        fim = high_resolution_clock::now();

        time = duration_cast<duration<double>>(fim - inicio).count();

        Metricas::setTime(time);

        res += "Inserção-";
        res += "Iteração " + to_string(i) +
               ", n= " + to_string(n) +
               " - comparações: " + to_string(Metricas::getComparisonCount()) +
               ", tempo: " + to_string(time) + "\n";

        Metricas::incrementMedia();
        Metricas::clearMetrics();
    }

    res += "Media time: " + to_string(Metricas::getMediaTime());
    res += ", Media coparacoes: " + to_string(Metricas::getMediaComparison()) + "\n";

    Metricas::clearMedia();
    Metricas::clearMetrics();
    Metricas::enable();

    for (int i = 0; i < 3; i++) {
        vector<Review*> reviews =  fileIo.importarAleatorios(binary_input_file, b);


        inicio = high_resolution_clock::now();
        for(int i = 0; i < reviews.size(); i++){
            vpTree.busca(reviews[i]->getReviewId());
        }
        fim = high_resolution_clock::now();

        time = duration_cast<duration<double>>(fim - inicio).count();

        Metricas::setTime(time);

        res += "Busca-";
        res += "Iteração " + to_string(i) +
               ", b= " + to_string(b) +
               " - comparações: " + to_string(Metricas::getComparisonCount()) +
               ", tempo: " + to_string(time) + "\n";

        Metricas::incrementMedia();
        Metricas::clearMetrics();
        deleteVectorItems(reviews);
    }

    res += "Media time: " + to_string(Metricas::getMediaTime());
    res += ", Media coparacoes: " + to_string(Metricas::getMediaComparison()) + "\n\n";

    fileIo.appendArquivo(output_file, res);
}

void metricasArvoreB(string binary_input_file, string output_file, int n, int b) {
    Metricas::enable();
    FileIO fileIo = FileIO();

    string res;
   // vector<Review*> reviews = fileIo.importarAleatorios(binary_input_file, 100);

    high_resolution_clock::time_point inicio;
    high_resolution_clock::time_point fim;
    double time;

    BTree bTree = BTree(20); ///pode ser aqui?

    //int somaComparacoesInsercao=0;
    //int somaComparacoesBusca=0;
    //double somaTempoInsercao=0;
    //double somaTempoBusca=0;

    res += "Arvore B, ordem m =20\n";
    for (int i = 0; i < 3; i++) {


        inicio = high_resolution_clock::now();
        fileIo.importarAleatoriosBTree(bTree, binary_input_file, n);
        fim = high_resolution_clock::now();

        time = duration_cast<duration<double>>(fim - inicio).count();

        res += "Inserção-";
        res += "Iteração " + to_string(i) +
               ", n= " + to_string(n) +
               "- comparações: " + to_string(Metricas::getComparisonCount()) +
               ", tempo: " + to_string(time) + "\n";

        Metricas::setTime(time);
        Metricas::incrementMedia();
        Metricas::clearMetrics();
    }

    res += "Media time: " + to_string(Metricas::getMediaTime());
    res += ", Media coparacoes: " + to_string(Metricas::getMediaComparison()) + "\n";

    Metricas::clearMedia();
    Metricas::clearMetrics();
    Metricas::enable();

    for (int i = 0; i < 3; i++){
        vector<Review*> reviews =  fileIo.importarAleatorios(binary_input_file, b);


        inicio = high_resolution_clock::now();

        for(int i=0; i<reviews.size(); i++){
            bTree.find(reviews[i]->getReviewId());
        }
        fim = high_resolution_clock::now();

        time = duration_cast<duration<double>>(fim - inicio).count();

        res += "Busca-";
        res += "Iteração " + to_string(i) +
               ", b= " + to_string(b) +
               "- comparações: " + to_string(Metricas::getComparisonCount()) +
               ", tempo: " + to_string(time) + "\n";

        Metricas::setTime(time);
        Metricas::incrementMedia();
        Metricas::clearMetrics();

        deleteVectorItems(reviews);
    };

    res += "Media time: " + to_string(Metricas::getMediaTime());
    res += ", Media coparacoes: " + to_string(Metricas::getMediaComparison()) + "\n\n";

    Metricas::clearMedia();
    Metricas::clearMetrics();
    Metricas::enable();

    BTree bTree2 = BTree(200);

    res += "Arvore B, ordem m =200\n";
    for (int i = 0; i < 3; i++) {

        inicio = high_resolution_clock::now();
        fileIo.importarAleatoriosBTree(bTree2, binary_input_file, n);
        fim = high_resolution_clock::now();

        time = duration_cast<duration<double>>(fim - inicio).count();

        res += "Inserção-";
        res += "Iteração " + to_string(i) +
               ", n= " + to_string(n) +
               "- comparações: " + to_string(Metricas::getComparisonCount()) +
               ", tempo: " + to_string(time) + "\n";

        Metricas::setTime(time);
        Metricas::incrementMedia();
        Metricas::clearMetrics();
    }

    res += "Media time: " + to_string(Metricas::getMediaTime());
    res += ", Media coparacoes: " + to_string(Metricas::getMediaComparison()) + "\n";

    Metricas::clearMedia();
    Metricas::clearMetrics();
    Metricas::enable();

    for(int i = 0; i < 3; i++){
        vector<Review*> reviews =  fileIo.importarAleatorios(binary_input_file,  b);


        inicio = high_resolution_clock::now();
        for(int i=0; i<reviews.size(); i++){
            bTree2.find(reviews[i]->getReviewId());
        }
        fim = high_resolution_clock::now();

        time = duration_cast<duration<double>>(fim - inicio).count();

        res += "Busca-";
        res += "Iteração " + to_string(i) +
               ", b= " + to_string(b) +
               "- comparações: " + to_string(Metricas::getComparisonCount()) +
               ", tempo: " + to_string(time) + "\n";

        Metricas::setTime(time);
        Metricas::incrementMedia();
        Metricas::clearMetrics();

        deleteVectorItems(reviews);
    }

    res += "Media time: " + to_string(Metricas::getMediaTime());
    res += ", Media coparacoes: " + to_string(Metricas::getMediaComparison())+"\n\n";

    fileIo.appendArquivo(output_file, res);

}


void menu(string input_dir, string bin_file_path) {

    bool saida = false;
    int option, modo;
    string id;
    int i;
    FileIO fileIo = FileIO();
    Compression compression = Compression();

    while(option != 12){

        cout << "\n";
        cout << "----------- MENU -----------\n";
        cout << "1 - Funcao Acessar Registro (i)\n";
        cout << "2 - Funcao Teste Importacao \n";
        cout << "3 - Gerar metricas dos algoritmos de ordenacao \n";
        cout << "4 - Ordenacao \n";
        cout << "5 - Hash \n";
        cout << "6 - Modulo de Teste \n";
        cout << "7 - Arvore Vermelho-Preto \n";
        cout << "8 - Arvore B \n";
        cout << "9 -  Comprimir N registros para reviewComp.bin \n";
        cout << "10 - reviewComp.bin para reviewOrig.bin\n";
        cout << "11 - Modulo de teste compressao\n";
        cout << "12 - Sair \n";
        cout << "\n";
        cout << "Opcao: ";
        cin >> option;
        cout << "\n";

        if (option == 1) {
            cout << "Informe i: ";
            cin >> i;

            ifstream arq;
            arq.open(bin_file_path, ios::binary);

            Review *review = fileIo.acessarRegistroTAD(i, arq);
            cout << review->toString();
            arq.close();

            delete review;
        } else if (option == 2) {
            testeImportacao(bin_file_path);
        } else if (option == 3) {
            simulacaoPerformaceOrdenacao("saida.txt", bin_file_path, input_dir);
        } else if (option == 4) {

            int n;
            cout << "Informe n: ";
            cin >> n;

            cout << ordenaVetorN(bin_file_path, n);
        } else if (option == 5) {
            int n;
            cout << "Informe n: ";
            cin >> n;

            cout << tabelaHashN(bin_file_path, n);
        } else if (option == 6) {

            string resultadoOrdenacao = "Teste Ordenacao: \n" + ordenaVetorN(bin_file_path, 100) + "\n\n";
            string resultadoHash = "Teste Hash: \n" + tabelaHashN(bin_file_path, 100);

            fileIo.appendArquivo("teste.txt", resultadoOrdenacao + resultadoHash);

            cout << "Resultado escrito ao final do arquivo teste.txt" << endl;
        } else if (option == 7) {


            cout << "Digite 1 para Modo de Analise (gera relatorio) \n";
            cout << "Digite 2 para Modo de Teste (buscar avaliacao por id) \n";


            cout << "\n";
            cout << "Modo: ";
            cin >> modo;
            cout << "\n";

            VPTree vpTree = VPTree();

            if (modo == 1) {
                metricasArvoreVP(bin_file_path, "saida.txt", 100, 100);
                cout << "\nArquivo de saida gerado.";
            } else if (modo == 2) {
                int n;
                cout << "Digite numero de reviews aleatorias para importacao: \n";
                cin >> n;

                FileIO fileIo = FileIO();
                fileIo.importarAleatoriosVPTree(vpTree, "data.bin", n);

                cout << "Digite o ID da avaliacao que deseja buscar: ";
                cin >> id;
                int find = vpTree.busca(id);

                if (find == -1) {
                    cout << "\n ID nao encontrado." << endl;
                } else {
                    cout << fileIo.acessarRegistroTAD(find, "data.bin")->toString();
                }
            } else {
                cout << "\n Opcao invalida" << endl;
            }
        } else if (option == 8) {

            cout << "Digite 1 para Modo de Analise (gera relatorio) \n";
            cout << "Digite 2 para Modo de Teste (buscar avaliacao por id) \n";

            cout << "\n";
            cout << "Modo: ";
            cin >> modo;
            cout << "\n";

            if (modo == 1) {
                metricasArvoreB(bin_file_path, "saida.txt", 100, 100);
                cout << "\nArquivo de saida gerado.\n";
            } else if (modo == 2) {
                int ordem;

                cout << "\n Digite a ordem da arvore B: ";

                cin >> ordem;
                BTree bTree = BTree(ordem);

                int n;
                cout << "Digite numero de reviews aleatorias para importacao: \n";
                cin >> n;

                FileIO fileIo = FileIO();
                fileIo.importarAleatoriosBTree(bTree, "data.bin", n);

                cout << "\n Digite o ID da avaliacao que deseja buscar: ";
                cin >> id;
                int find = bTree.find(id);
                if (find == -1) {
                    cout << "\n ID nao encontrado." << endl;
                } else {
                    cout << fileIo.acessarRegistroTAD(find, "data.bin")->toString();
                }
            } else {
                cout << "\n Opcao invalida." << endl;
            }

        } else if (option == 9) {

            int n;
            cout << "Informe N: ";
            cin >> n;

            string data = fileIo.importarAleatoriosCompression("data.bin", n);

            compression.gerarArvore(data);
            compression.gerarTabela();

            string compressedData = compression.compress(data);
            string codedString = compression.readBinaryString(compressedData);

            fileIo.writeReviewComp("reviewsComp.bin", codedString);

            ///teste
            //string convertedBack = compression.readCompressedText(codedString);
            //cout << compression.decompress(convertedBack)<<endl;


            cout << "Taxa de compressao: " << compression.taxaCompressao() << endl;

            cout << "reviewsComp.bin gerado" << endl;

        } else if (option == 10) {

            string dataBin = fileIo.readReviewComp("reviewsComp.bin");
            string convertedBack = compression.readCompressedText(dataBin);

            string textOriginal = compression.decompress(convertedBack);

            fileIo.writeReviewComp("reviewsOrig.bin", textOriginal);

            cout << "reviewsOrig.bin gerado" << endl;

            cout << fileIo.readReviewComp("reviewsOrig.bin");

        } else if (option == 11) {
            metricasCompressao("data.bin", "saida.txt");
        } else if (option == 12) {
            cout << "Encerrando o programa...";
            sleep(2);
            return;
        }
        else {
            cout << "Opcao invalida" << endl;
        }
    }
}


int main(int argc, char **argv) {
    string input_dir;
    string input_file_path;
    string bin_file_path = "data.bin";

    if (argc == 2) {
        input_dir = argv[1];
        input_file_path = input_dir + "/tiktok_app_reviews.csv";
        bin_file_path = input_dir + "/data.bin";

    } else {
        cout << "Erro: era esperado caminho do arquivo de entrada." << endl;
        return 0;
    }


    ifstream binFile(bin_file_path);
    if (binFile.fail()) {
        cout << "Binario nao encontrado. Gerando arquivo binario..." << endl;
        FileIO fileIO = FileIO();
        fileIO.readCSVToBinary(input_file_path, bin_file_path);

        menu(input_dir, bin_file_path);
    } else {
        menu(input_dir, bin_file_path);
    }

    return 0;
}

