#include "../include/cabecalho.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

std::vector<std::string> Cabecalho::strs = {};

Cabecalho::Cabecalho()
{
}

int Cabecalho::setCabecalho(const std::string &nomeArquivo)
{
    std::string substringData;
    std::string substringDataLarge;
    std::string substringDataSmall;

#ifdef _WIN32
    substringData = "data\\data";
    substringDataLarge = "data\\large\\data";
    substringDataSmall = "data\\small\\data";
#else
    substringData = "./data/data";
    substringDataLarge = "./data/large/data";
    substringDataSmall = "./data/small/data";
#endif

    if ((nomeArquivo.find(substringData) == std::string::npos) &&
        (nomeArquivo.find(substringDataLarge) == std::string::npos) &&
         (nomeArquivo.find(substringDataSmall) == std::string::npos))
    {
        std::cerr << "Erro! o caminho especificado para data é inválido.";
        return -1;
    }
    std::string strInput;
    std::ifstream fin(nomeArquivo);
    if (!fin)
    {
        // Imprime erro e sai do programa
        std::cerr << "Oops!" << nomeArquivo << " não pode ser aberto para leitura!\n";
        return -1;
    }

    std::getline(fin, strInput); // Passando o texto da primeira linha do arquivo para strInput
    fin.close();

    std::string palavra;            // string auxiliar para percorrer
    std::stringstream ss(strInput); // transforma a string em stream

    while (std::getline(ss, palavra, ','))
    {
        this->strs.push_back(palavra);
    }

    this->strs.erase(this->strs.begin());
    return 0;
}
