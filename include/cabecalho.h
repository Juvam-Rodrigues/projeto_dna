#ifndef CABECALHO_H
#define CABECALHO_H
#include <string>
#include <vector>

class Cabecalho{
    public:
    static std::vector<std::string> strs;

    public:
    Cabecalho();
    int setCabecalho(const std::string& nomeArquivo);
   
};

#endif