CC = g++
FLAGS = -Wall -g -O0
OBJ = ./obj

all : main
	# mv *.o ${OBJ}
	# mv *.gch ${OBJ}
	@echo "Compilado corretamente"

main : main.cpp chaveItem.h symbolTable.h vector.h list.h
	${CC} ${FLAGS} $^ -o $@