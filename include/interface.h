#ifndef INTERFACE_H
#define INTERFACE   _H
#include <string>
#include "pessoas.h"
#include "amostra.h"
#include <vector>

class Interface{

    public:
    Interface();
    void percorrerArgumentos(int argc, char *argv[]);
    void mostrarSaida(Pessoas pessoas, Amostra amostra, std::string dataBaseTxt, std::string amostraTxt);

    //Métodos para estilizar a saída
    void imprimirBarra();
    void imprimirLateraisSemTexto();
    void imprimirTextoCentralizado(std::string texto);
    void imprimirTextoComQuebra(std::string texto);
    void imprimirBarraProgresso();

    //Funções auxiliares
    int calcularLarguraTextoFormatacao(const std::string& texto);
    std::vector<std::string> quebrarTexto(const std::string& texto, int larguraMax);
    std::string encontrarNomeComMesmoMapa(Pessoas& pessoas, Amostra& amostra);
    std::string analisarSaida(const std::string& saida) const;
    std::string destacarSTRs(const std::string& dna, const std::map<std::string, int>& mapaStrsComQuantidade);
    std::string marcarVisualmente(const std::string& dnaMarcado);

   
};

#endif