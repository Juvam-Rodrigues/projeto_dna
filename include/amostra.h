#ifndef AMOSTRA_H
#define AMOSTRA_H
#include <string>
#include <map>
#include <vector>
#include "pessoa.h"

class Amostra : public Pessoa
{
private:
    std::string amostraCompleta;
    std::map<std::string, int> mapaStrsComQuantidade;
    std::vector<std::string> sequenciasRepetidas;
    
public:
    Amostra();
    void setAmostra(const std::string &amostraTxt);
    void calcularStr();
    std::string getAmostra();
    const std::map<std::string, int> &getMapaStrs() const;
    std::vector<int> getQuantidadeStrs();
    void exibirStrsComQuantidade() const;
    
};

#endif