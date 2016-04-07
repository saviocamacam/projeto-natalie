BIBNAME = "./lib/mapa"
MAINAME = "./src/main"
BIBOUTPUT = "BIBMAPA"
MAINOUTPUT = "Automatos"

all: bib
	@printf "Compilando o $(MAINAME)... \n"
	@gcc -g $(MAINAME).c $(BIBOUTPUT).o -o $(MAINOUTPUT).out -lm -Wall -Wextra
	@if [ -f ./$(MAINOUTPUT).out ]; then echo "Código compilado com sucesso!"; else echo "Erro ao compilar o código"; exit 2; fi
	@printf "removendo arquivos temporarios... "
	@rm $(BIBOUTPUT).o
	@if [ -f $(BIBOUTPUT).o ]; then printf "\nErro ao remover arquivos temporários\n"; exit 3; else printf "OK\n"; fi

bib:
	@printf "Verificando bibliotecas... \n"
	@if [ -f ./$(BIBNAME).c ] && [ -f ./$(BIBNAME).h ];	then echo "$(BIBNAME)... OK"; else echo "A biblioteca $(BIBNAME) não está na pasta"; exit 1; fi 
	@printf "Compilando bibliotecas..."
	@gcc -c -g $(BIBNAME).c -o $(BIBOUTPUT).o -lm -Wall -Wextra
	@if [ -f $(BIBOUTPUT).o ]; then printf "OK\nBiblioteca compilada com sucesso!\n"; else printf "\nErro ao compilar a biblioteca :(\n"; exit 2; fi

gerasaida:
	@printf "Verificando a saida..."
	@if [ -f ./tmp/saida.jff ]; then echo "OK"; else printf "\nA saida do JFLAP não está na pasta ./tmp";exit 2; fi
	@printf "Gerando Saida..."
	@python automaton2utfpr.py "./tmp/saida.jff" "modelo_2.txt"
	@if [ -f ./modelo_2.txt ]; then printf "Ok\nSaida gerada com sucesso\n"; else printf "Erro ao gerar a saida\n"; exit 2; fi

