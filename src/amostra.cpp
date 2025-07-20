#include "../include/amostra.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Amostra::Amostra()
{
    this->amostraCompleta = "";
}

void Amostra::setAmostra(const std::string &amostraTxt)
{
    std::string amostra;
    std::ifstream fin(amostraTxt);
    if (!fin)
    {
        // Imprime erro e sai do programa
        std::cerr << "Oops!" << amostraTxt << " não pode ser aberto para leitura!\n";
        return;
    }

    std::getline(fin, amostra); // Passando o texto da primeira linha do arquivo para amostra
    fin.close();

    this->amostraCompleta = amostra;
}

std::string Amostra::getAmostra()
{
    return this->amostraCompleta;
}

const std::map<std::string, int>& Amostra::getMapaStrs() const
{
    return this->mapaStrsComQuantidade;
}

void Amostra::calcularStr()
{
    std::string sequenciaRepetida;
    // Percorre cada STR no vetor 'strs'
    for (const std::string &str : strs)
    { // Analisando o loop com Range Based For Loops, só uma maneira simplificada de fazer a lógica do for

        int maxRepeticoes = 0; // Armazena a maior repetição consecutiva encontrada pra o STR que ta sendo analisado

        // Percorre toda a sequência de DNA (amostraCompleta)
        for (std::string::size_type i = 0; i < amostraCompleta.size(); ++i)
        {

            int repeticoesAtuais = 0;
            int j = i; // Índice auxiliar

            while (amostraCompleta.substr(j, str.size()) == str) // Realiza a procura da substring
            {
                repeticoesAtuais++;
                j += str.size(); // Se achou, avança quantidade referente ao tamanho da substring procurada para ver se há mais.
            }

            if (repeticoesAtuais > maxRepeticoes)
            {
                maxRepeticoes = repeticoesAtuais;
            }
        }

        // Constrói a string com todas as repetições juntas (ex: "AGATAGATAGAT" para 3 repetições)
        std::string sequencia = "";
        for (int k = 0; k < maxRepeticoes; ++k)
        {
            sequencia += str;
        }

        // Armazena a sequência repetida no vetor paralelo
        sequenciasRepetidas.push_back(sequenciaRepetida);

        // Armazena apenas a quantidade no map
        mapaStrsComQuantidade[str] = maxRepeticoes;
    }
}

std::vector<int> Amostra::getQuantidadeStrs()
{
    std::map<std::string, int>::iterator it;
    std::vector<int> vetorComQtdStrs;
    int qtd;
    for (it = mapaStrsComQuantidade.begin(); it != mapaStrsComQuantidade.end(); ++it)
    {
        qtd = it->second;

        vetorComQtdStrs.push_back(qtd);
    }

    return vetorComQtdStrs;
}

void Amostra::exibirStrsComQuantidade() const
{
    std::cout << "----- STRs e suas maiores repetições consecutivas -----\n";

    std::map<std::string, int>::const_iterator it;

    for (it = mapaStrsComQuantidade.begin(); it != mapaStrsComQuantidade.end(); ++it)
    {
        std::string str = it->first;
        int qtd = it->second;

        std::cout << "STR: " << str << " | Repetições: " << qtd << "\n";
    }
}