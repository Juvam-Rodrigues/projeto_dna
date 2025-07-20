<h1>Projeto DNA Profile 🧬</h1>

<h2>Descrição 🤔</h2>
<p>Este projeto consiste em um sistema em C++ para identificação de perfis genéticos (DNA) a partir de amostras e banco de dados (um arquivo local). Ele realiza:</p>
<ul>
    <li>Leitura e processamento de sequências STRs a partir de arquivos;</li>
    <li>Comparação entre amostras desconhecidas e um banco de dados;</li>
    <li>Destacamento visual das sequências STRs encontradas na amostra;</li>
    <li>Exibição estilizada dos resultados no terminal.</li>
</ul>

<h2>Estruturas e conceitos utilizados 🧑‍💻</h2>
<ul>
    <li><strong>Mapas (std::map):</strong> para contagem de sequências STR;</li>
    <li><strong>Vetores (std::vector):</strong> para armazenamento dinâmico;</li>
    <li><strong>Classes e herança:</strong> organização orientada a objetos;</li>
    <li><strong>Manipulação de arquivos e argumentos de linha de comando;</strong></li>
    <li><strong>Códigos ANSI:</strong> para colorir saída no terminal.</li>
</ul>

<h2>📂 Estrutura de Pastas</h2>
<ul>
    <li>📂 DNA
        <ul>
            <li>📂 data
                <ul>
                    <li>📂 large</li>
                    <li>📂 small</li>
                    <li>📄 data.csv</li>
                    <li>📄 respostas.txt</li>
                    <li>📄 sequence_alice.csv</li>
                    <li>📄 sequence_bob.csv</li>
                    <li>📄 sequence_charlie.csv</li>
                    <li>📄 sequence_nomatch.csv</li>
                </ul>
            </li>
            <li>📂 include
                <ul>
                    <li>📄 amostra.h</li>
                    <li>📄 cabecalho.h</li>
                    <li>📄 interface.h</li>
                    <li>📄 pessoa.h</li>
                    <li>📄 pessoas.h</li>
                </ul>
            </li>
            <li>📂 src
                <ul>
                    <li>📄 amostra.cpp</li>
                    <li>📄 cabecalho.cpp</li>
                    <li>📄 interface.cpp</li>
                    <li>📄 main.cpp</li>
                    <li>📄 pessoa.cpp</li>
                    <li>📄 pessoas.cpp</li>
                </ul>
            </li>
            <li>📄 LICENSE</li>
            <li>📄 Makefile</li>
            <li>📄 README.md</li>
        </ul>
    </li>
</ul>

<h2>🚀 Como usar</h2>
<p>Para executar o programa, utilize o comando no terminal:</p>
<pre><code>.\executavel.exe -d caminho_para_database.csv -s caminho_para_amostra.txt</code></pre>

<p>Exemplo:</p>
<pre><code>.\executavel.exe -d data/large/database.csv -s data/large/5.txt</code></pre>

<p>Onde:</p>
<ul>
    <li><strong>-d</strong> indica o arquivo CSV do banco de dados de perfis;</li>
    <li><strong>-s</strong> indica o arquivo com a amostra de DNA a ser comparada.</li>
</ul>

<h2>Visualização colorida no terminal</h2>
<p>As sequências STR encontradas na amostra são destacadas entre colchetes <code>[]</code> e exibidas com cor usando códigos ANSI para facilitar a leitura.</p>
<p><strong>Exemplo:</strong></p>
<pre><code>[AGATAGATAGAT]AATGAATG[TATCTATCTATC]</code></pre>
<p>Os colchetes e o conteúdo entre eles aparecem destacados em verde se seu terminal suportar ANSI.</p>

<h2>Colaboradores 🤝</h2>
<ul>
    <li><a href="https://github.com/justofernandes">Justo Fernandes de Oliveira Neto</a></li>
    <li><a href="https://github.com/Juvam-Rodrigues">Juvam Rodrigues do Nascimento Neto</a></li>
    <li><a href="https://github.com/KauaRodrigues03">Kaua das Chagas Rodrigues</a></li>
</ul>
