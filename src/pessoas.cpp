#include "../include/pessoas.h"
#include "../include/pessoa.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>


Pessoas::Pessoas(){

}

void Pessoas::setPessoas(const std::string& nomeArquivo)
{
    std::string strInput;
    std::ifstream fin(nomeArquivo);
    if (!fin) {
       // Imprime erro e sai do programa
       std::cerr << "Oops!" << nomeArquivo << " não pode ser aberto para leitura!\n";
       return;
   }


    std::getline(fin, strInput); // Ignora a primeira linha
    int contador = 0;

    while (std::getline(fin, strInput)) //percorre linha por linha
    {
        std::stringstream ss(strInput); // transforma a string em stream
        std::string palavra;

        std::getline(ss, palavra, ','); // Pegando o nome da pessoa
        Pessoa p;
        p.setNome(palavra);
        while (std::getline(ss, palavra, ',')) // enquanto houver coisa na linha
        {
            p.setStrsPessoa(palavra, p.strs[contador]);
            contador++;
        }
        this->vetorPessoas.push_back(p);
        contador = 0;
    }
    fin.close();
}

void Pessoas::imprimirPessoas(){
    for (int i = 0; i < (int)vetorPessoas.size(); i++)
    {
        this->vetorPessoas[i].imprimirStrsComQuantidade();
    }
}