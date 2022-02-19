//
// Created by welli on 2/12/2022.
//
#include <iostream>
#include "Compression.h"
#include "string"
#include <cmath>
#include <fstream>
#include "FileIO.h"

using namespace std;

string intToBinaryString(unsigned int number){
    string result(32, '0');
    unsigned int num = number;
    for(int i=31; i>= 0; i--){
        result.replace(i, 1, to_string(num%2));
        num = num/2;
    }
    return result;
}

unsigned int readBinaryStringToInt(string bin){
    unsigned int result=0;
    int size = (int)bin.size();

    for(int i= size; i>0; i--){
        int active = (bin[i-1] == '1');
        result += active*(int)pow(2, size-i);
    }
    return result;
}

unsigned char readBinaryStringToChar(string bin){
    int result=0;
    int size = (int)bin.size();

    for(int i= size; i>0; i--){
        int active = (bin[i-1] == '1');
        result += active*(int)pow(2, size-i);
    }
    return (unsigned char)result;
}

string charToBinaryString(unsigned char c){
    string result(8, '0');
    int num = (int)c;
    for(int i=7; i>= 0; i--){
        result.replace(i, 1, to_string(num%2));
        num = num/2;
    }

    return result;
}

string codedCharsToBynaryString(string codedString){
    string result;

    for(int i=0; i<codedString.size(); i++){
        result+= charToBinaryString(codedString[i]);
    }

    return result;
}

string readCompressedText(string codedString){
    string compressedText = codedString.substr(4, codedString.size()-4);
    string sizeHeader = codedString.substr(0,4);
    int size = readBinaryStringToInt(codedCharsToBynaryString(sizeHeader));
    string result = codedCharsToBynaryString(compressedText).substr(0, size);
    return result;
}

//codifica uma string com 1 e 0 em caracteres e coloca em outra string
string readBinaryString(string bin){
    string result;
    int numCompletar = ((bin.size()/8)+1)*8 - bin.size();
    string padding(numCompletar, '0');
    string sizeHeader = intToBinaryString(bin.size());
    string paddedString = sizeHeader + bin + padding;
   // cout << "padded string: "<< paddedString<<endl;

    for(int i= 0; i<paddedString.size(); i+=8){
        result+= readBinaryStringToChar(paddedString.substr(i, 8));
    }
    return result;
}

void writeReviewComp(string path, string bin){

    ofstream arq;
    arq.open(path, ios::binary);

    arq << bin;
    arq.close();
}

string readReviewComp(string path){

    ifstream arq;
    arq.open(path, ios::binary);

    Compression compression = Compression();

    string bin;

    getline(arq, bin);

    arq.close();

    return bin;
}



int main(int argc, char **argv) {


    //string data = "abacateabafabafofojaofjaojfojafojfojafojsofjaofjaofjsaofjaofjasofjaofjasofjaosfjaosjfaojfao[fojqw[pqjf[wpqjf[w";

    //Compression compression = Compression();
    //compression.gerarArvore(data);
    //compression.gerarTabela();
    //string compressedData = compression.compress(data);
    //string codedString = readBinaryString(compressedData);
    //string convertedBack = readCompressedText(codedString);
    //string convertedBackFullCode = codedCharsToBynaryString(codedString);

    //cout << compressedData << endl;
    //cout << codedString << endl;
    //cout << convertedBack << endl;
    //cout << convertedBackFullCode << endl;
   //cout << compression.decompress(convertedBack)<<endl;

    //escreve binario
    //writeReviewComp("reviewsComp.bin", codedString);

    //le binario
    //string dataBin = readReviewComp("reviewsComp.bin");
    //string convertedBack = readCompressedText(dataBin);

    //cout << compression.decompress(convertedBack);

    int n;
    cout << "Informe N: ";
    cin >> n;

    FileIO fileIo = FileIO();

    Compression compression = Compression();

    string data = fileIo.importarAleatoriosCompression("data.bin", n);

    cout << data;

    compression.gerarArvore(data);
    compression.gerarTabela();
    string compressedData = compression.compress(data);
    string codedString = compression.readBinaryString(compressedData);

    //escreve binario
    cout << codedString << endl;
    fileIo.writeReviewComp("reviewsComp.bin", codedString);

    //le binario
    string dataBin = fileIo.readReviewComp("reviewsComp.bin");
    string convertedBack = compression.readCompressedText(dataBin);

    string textOriginal = compression.decompress(convertedBack);

    fileIo.appendArquivo("reviewsOrig.bin", textOriginal);
}