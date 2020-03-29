CC = g++
FLAGS = -Wall -g -O0
OBJ = ./obj

all : main
	# mv *.o ${OBJ}
	# mv *.gch ${OBJ}
	@echo "Compilado corretamente"

main : main.cpp chaveItem.hpp symbolTable.hpp vector.hpp list.hpp arvoreBinaria.hpp treap.hpp
	${CC} ${FLAGS} $^ -o $@