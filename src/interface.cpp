#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <regex>
#include "../include/interface.h"
#include "../include/cabecalho.h"
#include "../include/pessoas.h"
#include "../include/amostra.h"

Interface::Interface()
{
}

// Obtem largura do terminal
#ifdef _WIN32
#include <windows.h>
int getTerminalLargura()
{ // Função responsável por pegar a largura do terminal
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;
}
#else
#include <sys/ioctl.h>
#include <unistd.h>
int getTerminalLargura()
{ // Função responsável por pegar a largura do terminal
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
    {
        return w.ws_col;
    }
    return -1;
}
#endif

//====================================  MÉTODOS DE ESTILIZAÇÃO ======================================

void Interface::imprimirBarra() // Imprime uma linha
{
    int larguraTerminal = getTerminalLargura();

    if (larguraTerminal == -1)
    {
        std::cout << "Erro! Não foi possível obter largura do terminal.";
        return;
    }

    for (int i = 0; i < larguraTerminal; i++)
    { // Largura do terminal
        std::cout << "-";
    }
    std::cout << std::endl;
    return;
}

void Interface::imprimirLateraisSemTexto() // Imprime uma linha de espaços com barras nas pontas
{
    int larguraTerminal = getTerminalLargura() - 2;

    if (larguraTerminal == -1)
    {
        std::cout << "Erro! Não foi possível obter largura do terminal.";
        return;
    }

    std::cout << "|";
    for (int i = 0; i < larguraTerminal; i++)
    { // Largura do terminal
        std::cout << " ";
    }
    std::cout << "|" << std::endl;
    return;
}

int Interface::calcularLarguraTextoFormatacao(const std::string &texto)
{
    std::regex ansiRegex("\033\\[[0-9;]*m");
    std::string textoSemFormatacao = std::regex_replace(texto, ansiRegex, "");
    return (int)textoSemFormatacao.size();
}

std::vector<std::string> Interface::quebrarTexto(const std::string &texto, int larguraMax) // Quebra um texto grande em textos menores que caibam na largura
{
    std::vector<std::string> linhas;
    std::string linhaAtual;
    std::string ansiTemp;
    bool dentroAnsi = false;

    for (size_t i = 0; i < texto.size(); ++i) // Um laço para percorrer char por char da string
    {
        char c = texto[i];

        if (c == '\033') // Verifica se está emcima do código de coloração
        {
            dentroAnsi = true;
            ansiTemp += c; // Vai somando a string código ansi
        }
        else if (dentroAnsi) // Se tiver dentro do código ansi
        {
            ansiTemp += c;
            if (c == 'm') // Final do código ansi
            {
                dentroAnsi = false; 
                linhaAtual += ansiTemp;
                ansiTemp.clear();
            }
        }
        else
        {
            linhaAtual += c;
        }

        if (!dentroAnsi && calcularLarguraTextoFormatacao(linhaAtual) >= larguraMax)
        {
            linhas.push_back(linhaAtual);
            linhaAtual.clear();
        }
    }

    if (!linhaAtual.empty())
    {
        linhas.push_back(linhaAtual);
    }

    return linhas;
}

void Interface::imprimirTextoComQuebra(std::string texto) // Imprime textos grandes alinhados à esquerda
{
    int larguraUtil = getTerminalLargura() - 2; // Largura fora os dois | laterais
    std::vector<std::string> linhas = quebrarTexto(texto, larguraUtil);

    for (int i = 0; i < (int)linhas.size(); i++)
    {
        std::cout << "|";
        std::cout << linhas[i]; // Imprime as linhas quebradas
        for (int j = 0; j < larguraUtil - calcularLarguraTextoFormatacao(linhas[i]); j++)
        {
            // Imprime os espaços à direita
            std::cout << " ";
        }

        std::cout << "|" << std::endl;
    }
}

void Interface::imprimirTextoCentralizado(std::string texto) // Imprime textos pequenos centralizados no centro
{                                                            //-2 é para caber as duas | nas pontas
    int larguraUtil = getTerminalLargura() - 2;
    int totalEspacos = larguraUtil - calcularLarguraTextoFormatacao(texto);

    if (totalEspacos < 0)
    {
        std::cerr << "Erro de tamanho de espaços.";
        return;
    }

    int espacosEsquerda = totalEspacos / 2;
    int espacosDireita = totalEspacos - espacosEsquerda;

    std::cout << "|";
    for (int i = 0; i < espacosEsquerda; i++) // espaços esquerda
    {
        std::cout << " ";
    }

    std::cout << texto;

    for (int i = 0; i < espacosDireita; i++) // espaços direita
    {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;
}

void Interface::imprimirBarraProgresso() // Imprime barra de progresso
{
    for (int i = 0; i <= 100; ++i)
    {
        int blocosPreenchidos = i;                  // de 0 a 100
        int blocosVazios = 100 - blocosPreenchidos; // Para saber quantos blocos estarão vazios na barra

        std::cout << "\r\033[36mProgresso: [" << std::string(blocosPreenchidos, '#')
                  << std::string(blocosVazios, ' ') // Vai imprindo e sobrescrevendo a mesma linha
                  << "] " << i << "%\033[0m" << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    std::cout << std::endl;
}
//=============================================================================================================

//==========================================  MÉTODO DE IMPRESSÃO =============================================
void Interface::mostrarSaida(Pessoas pessoas, Amostra amostra, std::string dataBaseTxt, std::string amostraTxt) // Bom passar por referência
{
    std::string comparacao = encontrarNomeComMesmoMapa(pessoas, amostra);
    std::string resultado = analisarSaida(comparacao);

    imprimirBarra();
    imprimirLateraisSemTexto();
    imprimirTextoCentralizado("\033[1mBem vindo ao DNA Profile, v1.0!\033[0m");
    imprimirTextoCentralizado("\033[1mDireitos reservados a JUSTO FERNANDES, JUVAM RODRIGUES e KAUA DAS CHAGAS.\033[0m");
    imprimirLateraisSemTexto();
    imprimirBarra();
    imprimirLateraisSemTexto();
    imprimirTextoComQuebra("[+] Carregando DNA da database file [\033[35m" + dataBaseTxt + "\033[0m] ... [\033[32mOK\033[0m]");

    std::this_thread::sleep_for(std::chrono::milliseconds(1400)); // Delay entre um carregamento e outro

    imprimirTextoComQuebra("[+] Carregando o DNA da amostra desconhecida [\033[35m" + amostraTxt + "\033[0m] ... [\033[32mOK\033[0m]");
    imprimirLateraisSemTexto();

    std::this_thread::sleep_for(std::chrono::milliseconds(800)); // Delay entre um carregamento e outro

    imprimirTextoComQuebra("[+] Procurando a amostra no database... Aguarde.");
    imprimirBarraProgresso();
    imprimirLateraisSemTexto();
    imprimirTextoComQuebra(resultado);
    imprimirLateraisSemTexto();


    if (comparacao != "no match")
    {
        std::string dnaComStrsDestacados = destacarSTRs(amostra.getAmostra(), amostra.getMapaStrs());
        imprimirTextoComQuebra(dnaComStrsDestacados);
        imprimirLateraisSemTexto();
    }

    imprimirBarra();
}
//=============================================================================================================

//====================================  MÉTODO DE LEITURA DOS ARGUMENTOS ======================================
void Interface::percorrerArgumentos(int argc, char *argv[])
{
    std::string dataBaseTxt; // As string passadas no argumento
    std::string amostraTxt;

    if (argc != 5)
    {
        std::cerr << "Quantidade de elementos informadas errada.";
        return;
    }

    for (int i = 1; i < argc; ++i) // A contagem começa após ./executavel
    {
        std::string arg = argv[i]; // Converte um ponteiro de char para string

        if (arg == "-d")
        {
            dataBaseTxt = argv[i + 1];
        }
        else if (arg == "-s")
        {
            amostraTxt = argv[i + 1];
        }
    }

    Cabecalho cabecalho;
    if (cabecalho.setCabecalho(dataBaseTxt) == -1)
    {
        return;
    }

    Pessoas pessoas;
    pessoas.setPessoas(dataBaseTxt);
    Amostra amostra;
    amostra.setAmostra(amostraTxt);
    amostra.calcularStr();
    mostrarSaida(pessoas, amostra, dataBaseTxt, amostraTxt);
}

//===================================================================================================

//==================================== MÉTODO DE COMPARAR MAPS ======================================
std::string Interface::encontrarNomeComMesmoMapa(Pessoas &pessoas, Amostra &amostra)
{
    std::vector<int> amostraVetorStrs = amostra.getQuantidadeStrs();
    int qtdTotalDeStrsCabecalho = amostra.strs.size();
    int contador = 0;

    for (size_t i = 0; i < pessoas.vetorPessoas.size(); i++)
    {
        contador = 0;
        std::vector<int> pessoaVetorStrs = pessoas.vetorPessoas[i].getQuantidadeStrs();
        for (int j = 0; j < qtdTotalDeStrsCabecalho; j++)
        {
            if (pessoaVetorStrs[j] == amostraVetorStrs[j])
            {
                contador++; //tá batendo a quantidade
            }
            if (contador == qtdTotalDeStrsCabecalho)
            {
                return pessoas.vetorPessoas[i].getNome();
            }
        }
    }
    return "no match";
}

//==================================== MÉTODO DAS SAÍDAS ======================================

std::string Interface::analisarSaida(const std::string &saida) const
{
    if (saida == "no match")
    {
        return ">>>> \033[31mDesculpa, a amostra nao foi encontrada no banco de dados.\033[0m"; // Imprime em vermelho
    }
    else
    {
        return ">>>> \033[32mMatch ID (99.9%): " + saida + "\033[0m"; // Imprime em verde
    }
}

// Insere colchetes em torno das STRs encontradas
std::string Interface::destacarSTRs(const std::string &dna, const std::map<std::string, int> &mapaStrsComQuantidade)
{
    std::string dnaCopia = dna; // Faz a cópia da string original
    std::map<std::string, int>::const_iterator it;

    for (it = mapaStrsComQuantidade.begin(); it != mapaStrsComQuantidade.end(); ++it)
    {
        std::string str = it->first;
        int qtd = it->second;

        std::string repeticao = "";
        for (int i = 0; i < qtd; ++i)
        {
            repeticao += str;
        }

        size_t pos = 0;
        while ((pos = dnaCopia.find(repeticao, pos)) != std::string::npos)
        {
            dnaCopia.insert(pos, "\033[1;42m[");
            pos += 8; // conta 8, pois "\033" conta 1 e "[1;42m" conta 6 + 1 do colchete "["
            pos += repeticao.size();
            dnaCopia.insert(pos, "]\033[0m");
            pos += 5; // conta 5, pois "\033" conta 1 e "[0m" conta 3 + 1 do colchete "["
        }
    }

    return dnaCopia; // Retorna a string modificada, sem afetar a original
}
