//
// Created by patri on 21/02/2022.
//

#include <iostream>
#include "Compression.h"

int main(){
    string data = "abcdeeeeefgaaaaagrirorpf";
    Compression compression = Compression();
    compression.gerarArvore(data);
    compression.gerarTabela();

    string compressedData = compression.compress(data);
    cout << compressedData << endl;

    string codedString = compression.readBinaryString(compressedData);
    cout << codedString << " ("<<codedString.size() <<")" << endl;

    string convertedBack = compression.readCompressedText(codedString);

    string textOriginal = compression.decompress(convertedBack);

    cout <<textOriginal <<endl;
    cout << compression.codedCharsToBynaryString(codedString) << endl;

}