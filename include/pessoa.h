#ifndef PESSOA_H
#define PESSOA_H
#include <string>
#include <map>
#include <vector>
#include "cabecalho.h"

class Pessoa: public Cabecalho{
    private:
    std::string nome;
    std::map<std::string,int> mapaStrsPessoa;

    public:
    Pessoa();
    void setNome(std::string& nome);
    void setStrsPessoa(std::string& qtdString, std::string& str);
    std::string getNome();
    std::vector<int> getQuantidadeStrs();
    void imprimirStrsComQuantidade();
    void imprimirStrs();

};

#endif