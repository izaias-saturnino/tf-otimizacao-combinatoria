compile:
	g++ -g -c main.cpp neighbours.cpp utils.cpp grasp.cpp greedy.cpp
	g++ -g -o cmb main.o neighbours.o utils.o grasp.o greedy.o -Wall -O3

# Comando para linkar os arquivos compilados e gerar o executável
clean: compile

# Comando para limpar os arquivos gerados
	rm -f main.o neighbours.o utils.o grasp.o greedy.o

test: 
	g++ -g -c test.cpp utils.cpp
	g++ -g -o cmb_test test.o utils.o -Wall -O3
	rm -f test.o utils.o

local_search:
	g++ -g -c local_search.cpp neighbours.cpp utils.cpp
	g++ -g -o cmb_local_search local_search.o neighbours.o utils.o -Wall -O3
	rm -f local_search.o neighbours.o utils.o

# Comando padrão do Makefile, executa o alvo "run" por padrão
.DEFAULT_GOAL := compile
