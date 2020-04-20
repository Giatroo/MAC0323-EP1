CC = g++
FLAGS = -Wall -g -O0
OBJ = ./obj

all : main
	# mv *.o ${OBJ}
	# mv *.gch ${OBJ}
	@echo "Compilado corretamente"

main : main.cpp chaveItem.hpp symbolTable.hpp arvoreBinaria.hpp list.hpp redblack.hpp treap.hpp tree23.hpp vector.hpp
	${CC} ${FLAGS} $^ -o $@