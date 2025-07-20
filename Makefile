# Nome do compilador
COMPILADOR = g++

#flags boa prática
FLAGS = -Wall -pedantic -std=c++17

# Nome do executável final
EXECUTAVEL = dnaprofiler

# Lista de arquivos fonte (caminho completo)
FONTES = src/main.cpp \
         src/interface.cpp \
         src/amostra.cpp \
         src/cabecalho.cpp \
         src/pessoa.cpp \
         src/pessoas.cpp

# Lista de arquivos objeto (gerados a partir dos .cpp)
OBJETOS = main.o interface.o amostra.o cabecalho.o pessoa.o pessoas.o

# Regra principal: compilar tudo
all: $(EXECUTAVEL)

# Como gerar o executável a partir dos objetos
$(EXECUTAVEL): $(OBJETOS)
	$(COMPILADOR) $(FLAGS) main.o interface.o amostra.o cabecalho.o pessoa.o pessoas.o -o $(EXECUTAVEL)

# Como compilar cada arquivo .cpp para .o
main.o:
	$(COMPILADOR) $(FLAGS) -c src/main.cpp -o main.o

interface.o:
	$(COMPILADOR) $(FLAGS) -c src/interface.cpp -o interface.o

amostra.o:
	$(COMPILADOR) $(FLAGS) -c src/amostra.cpp -o amostra.o

cabecalho.o:
	$(COMPILADOR) $(FLAGS) -c src/cabecalho.cpp -o cabecalho.o

pessoa.o:
	$(COMPILADOR) $(FLAGS) -c src/pessoa.cpp -o pessoa.o

pessoas.o:
	$(COMPILADOR) $(FLAGS) -c src/pessoas.cpp -o pessoas.o

# Regra de limpeza
clean:
ifeq ($(OS),Windows_NT)
	cmd /c del /f /q $(subst /,\,$(OBJETOS)) $(subst /,\,$(EXECUTAVEL).exe)
else
	rm -f $(OBJETOS) $(EXECUTAVEL)
endif
