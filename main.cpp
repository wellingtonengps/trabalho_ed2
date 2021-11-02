#include <iostream>
#include <string>
#include "Review.h"

using namespace std;

void read(string path){
    
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

    return 0;
}


