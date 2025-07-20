#ifndef PESSOAS_H
#define PESSOAS_H
#include <string>
#include <vector>
#include "pessoa.h"

class Pessoas{
    public:
    std::vector<Pessoa> vetorPessoas;

    public:
    Pessoas();
    void setPessoas(const std::string& nomeArquivo);
    void imprimirPessoas();

};

#endif