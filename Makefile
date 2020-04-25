CC = g++
FLAGS = -Wall -g -O0
OBJ = ./obj

all : main
	@echo "Compilado corretamente"

main : main.cpp myString.hpp chaveItem.hpp symbolTable.hpp treap.hpp list.hpp hashtable.hpp tree23.hpp redblack.hpp arvoreBinaria.hpp vector.hpp
	${CC} ${FLAGS} $^ -o $@
