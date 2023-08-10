compile:
	g++ -g -c main.cpp neighbours.cpp utils.cpp grasp.cpp greedy.cpp

# Comando para linkar os arquivos compilados e gerar o executável
link: compile
	g++ -g -o cmb main.o neighbours.o utils.o grasp.o greedy.o -Wall

# Comando para limpar os arquivos gerados
	rm -f main.o neighbours.o utils.o grasp.o greedy.o

test: 
	g++ -g -c test.cpp neighbours.cpp utils.cpp grasp.cpp greedy.cpp
	g++ -g -o cmb_test test.o neighbours.o utils.o grasp.o greedy.o -Wall
	rm -f test.o neighbours.o utils.o grasp.o greedy.o

# Comando padrão do Makefile, executa o alvo "run" por padrão
.DEFAULT_GOAL := link
