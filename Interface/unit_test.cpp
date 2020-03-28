
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../symbolTable.h"

using namespace std;

/*---------------------------------------------------------------*/
/*
 *  P R O T Ó T I P O S
 */
static void mostreUso(char *nomePrograma);

template <class ST>
void testeOperacoes(ST st);

/*---------------------------------------------------------------*/
/*
 *  M A I N
 */
int main(int argc, char *argv[]) {
	fstream arqTexto;

	if (argc < 3) mostreUso(argv[0]);

	/* abra arquivo com texto */
	arqTexto.open(argv[1]);

	if (arqTexto.fail()) {
		cout << "ERRO: arquivo" << argv[1] << "nao pode ser aberto.\n";
		exit(EXIT_FAILURE);
	}

	arqTexto.close();

	string nome_arquivo = argv[1];
	string tipo = argv[2];

	/* crie a ST*/
	cout << "criando ST...\n";

	/* usadas para medir tempo de processamento */
	clock_t start, end;
	double elapsed;
	start = clock();

	SymbolTable<string, int> *st;

	if (tipo == "VD")
		*st = new vetorDes(nome_arquivo);
	else if (tipo == "VO")
		*st = new vetorOrd(nome_arquivo);
	else if (tipo == "LD")
		*st = new listaDes(nome_arquivo);
	else if (tipo == "LO")
		*st = new listaOrd(nome_arquivo);
	else if (tipo == "AB")
		*st = new arvoreBin(nome_arquivo);
	else if (tipo == "TR")
		*st = new treap(nome_arquivo);
	else if (tipo == "A23")
		*st = new arvore23(nome_arquivo);
	else if (tipo == "RN")
		*st = new arvoreRN(nome_arquivo);
	else if (tipo == "HS")
		*st = new hashTable(nome_arquivo);
	else {
		cout << "A estrutura" << tipo << "não é válida" << endl;
		return EXIT_FAILURE;
	}

	end = clock();

	/* calcule o tempo */
	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

	testeOperacoes(st);

	return EXIT_SUCCESS;
}

/*-----------------------------------------------------------*/
/*
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S
 *                 A U X I L I A R E S
 */
static void mostreUso(char *nomePrograma) {
	cout << "Uso \n"
	     << "prompt> " << nomePrograma << " nome-arquivo tipo-tabela\n"
	     << "    nome-arquivo = nome do arquivo com o texto\n"
	     << "    tipo-tabela  = sigla de estrutura que deve ser usada\n";
	exit(EXIT_FAILURE);
}