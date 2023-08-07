compile:
	gcc -g -c main.c neighbours.c utils.c grasp.c greedy.c

# Comando para linkar os arquivos compilados e gerar o executável
link: compile
	gcc -g -o cmb main.o neighbours.o utils.o grasp.o greedy.o -Wall

# Comando para limpar os arquivos gerados
	rm -f main.o neighbours.o utils.o grasp.o greedy.o

# Comando padrão do Makefile, executa o alvo "run" por padrão
.DEFAULT_GOAL := link
