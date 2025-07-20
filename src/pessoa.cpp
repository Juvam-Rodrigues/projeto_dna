#include "../include/pessoa.h"
#include <iostream>

Pessoa::Pessoa()
{
    this->nome = "";
}

void Pessoa::setNome(std::string &nome)
{
    this->nome = nome;
}

void Pessoa::setStrsPessoa(std::string &qtdString, std::string &str)
{
    int qtd = std::stoi(qtdString);
    mapaStrsPessoa.insert({str, qtd});
}

std::string Pessoa::getNome()
{
    return this->nome;
}

std::vector<int> Pessoa::getQuantidadeStrs()
{
    std::map<std::string, int>::iterator it;
    std::vector<int> vetorComQtdStrs;
    int qtd;
    for (it = mapaStrsPessoa.begin(); it != mapaStrsPessoa.end(); ++it)
    {
        qtd = it->second;

        vetorComQtdStrs.push_back(qtd);
    }

    return vetorComQtdStrs;
}

void Pessoa::imprimirStrsComQuantidade()
{
    std::cout << nome << ": " << std::endl;
    std::map<std::string, int>::iterator it;
    for (it = mapaStrsPessoa.begin(); it != mapaStrsPessoa.end(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << std::endl;
}

void Pessoa::imprimirStrs()
{
    std::cout << nome << ", strs: ";

    for (int i = 0; i < (int)this->strs.size(); i++)
    {
        std::cout << strs[i] << " ";
    }

    std::cout << std::endl;
}
