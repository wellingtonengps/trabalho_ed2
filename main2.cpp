//
// Created by welli on 2/12/2022.
//
#include <iostream>
#include "Compression.h"
#include "string"

using namespace std;

int main(int argc, char **argv) {

    string data = "wellingtonpatrick";
    Compression compression = Compression();
    compression.gerarArvore(data);
    compression.gerarTabela();

    cout << compression.compress(data) << endl;

}