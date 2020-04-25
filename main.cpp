#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

#include "arvoreBinaria.hpp"
#include "hashtable.hpp"
#include "list.hpp"
#include "redblack.hpp"
#include "treap.hpp"
#include "tree23.hpp"
#include "vector.hpp"

using namespace std;

SymbolTable<MyString, int> *st;

void teste();
void testeInicial();
void testeInsere(int num_op);
void testeRemove(int num_op);
void testeDevolve(int num_op);
void testeSeleciona(int num_op);
void testeRank(int num_op);
void testeAleatorizado(int num_op);
void mostreUso(char *nomePrograma);
void testeIterativo();

#define TESTES_INSERE 1e6
#define TESTES_REMOVE 1e4
#define TESTES_DEVOLVE 1e5
#define TESTES_RANK 1e3
#define TESTES_SELECIONA 1e3
#define TESTES_ALEATORIOS 1e3
#define TAM_STRINGS 5

// ******** MAIN E IMPLEMENTAÇÕES ********

int main(int argc, char *argv[]) {
	fstream arqTexto;

	if (argc < 3) mostreUso(argv[0]);

	if ((string)argv[1] != "--classic") {
		arqTexto.open(argv[1]);

		if (arqTexto.fail()) {
			cout << "ERRO: arquivo" << argv[1] << "nao pode ser aberto." << endl;
			exit(EXIT_FAILURE);
		}
	}

	/* crie a ST*/
	cout << "Criando Symbol Table..." << endl;

	/* usadas para medir tempo de processamento */
	clock_t start, end;
	string tipo = argv[2];

	if (tipo == "VD")
		st = new vetor<MyString, int>();
	else if (tipo == "VO")
		st = new vetor_ordenado<MyString, int>();
	else if (tipo == "LD")
		st = new lista<MyString, int>();
	else if (tipo == "LO")
		st = new lista_ordenada<MyString, int>();
	else if (tipo == "AB")
		st = new arvore_binaria<MyString, int>();
	else if (tipo == "TR")
		st = new treap<MyString, int>();
	else if (tipo == "A23")
		st = new arvore23<MyString, int>();
	else if (tipo == "RN")
		st = new rb_tree<MyString, int>();
	else if (tipo == "HS")
		st = new hashtable<MyString, int>();
	else {
		cout << "A estrutura " << tipo << " não é válida" << endl;
		exit(EXIT_FAILURE);
	}

	if ((string)argv[1] == "--classic") {
		teste();
		return 0;
	}

	string palavra;
	string especiais = ".,!?:;'\"*{}()[]-0123456789 _";
	start = clock();
	while (arqTexto >> palavra) {
		// Tratando a palavra (deixando ela minúscula e retirando caracteres especiais)
		// Infelizmente, não achei forma de tornar caracteres acentuados em minúsculos
		for (string::iterator it = palavra.begin(); it < palavra.end(); it++) {
			if ('A' <= *it && *it <= 'Z') *it = *it - 'A' + 'a';
			for (long unsigned int j = 0; j < especiais.size(); j++)
				if (*it == especiais[j]) palavra.erase(it);
		}
		if (palavra.size() == 0) continue;
		st->insere(palavra, 1);
	}
	end = clock();
	cout << "Arquivo lido e ST construida em " << (((double)(end - start)) / CLOCKS_PER_SEC)
	     << " segundos" << endl;

	testeIterativo();

	return 0;
}

MyString randomWord() {
	string a = "";
	int len = (rand() % TAM_STRINGS) + 1;
	a.resize(len);
	for (int i = 0; i < len; i++) a[i] = (rand() % ('z' - 'a' + 1)) + 'a';
	return (MyString)a;
}

void teste() {
	srand(time(NULL));

	testeInsere(1e6);

	// for (int i = 10000; i <= 1e9; i *= 10) {
	// 	cout << "\nTestando insere " << i << " vezes" << endl;
	// 	testeInsere(i);
	// 	delete st;
	// 	st = new hashtable<MyString, int>();
	// }

	// for (int i = 10000; i <= 1e9; i *= 10) {
	// 	testeInsere(1e6);
	// 	cout << "\nTestando remove " << i << " vezes" << endl;
	// 	testeRemove(i);
	// 	delete st;
	// 	st = new hashtable<MyString, int>();
	// }

	for (int i = 10000; i <= 1e9; i *= 10) {
		cout << "\nTestando devolve " << i << " vezes" << endl;
		testeDevolve(i);
	}

	// testeInicial();
	// testeRank(TESTES_RANK);
	// testeSeleciona(TESTES_SELECIONA);
	// testeDevolve(TESTES_DEVOLVE);
	// testeRemove(TESTES_REMOVE);
	// testeAleatorizado(TESTES_ALEATORIOS);
}

void testeInicial() {
	st->remove((MyString) "a");
	st->remove((MyString) "b");
	st->insere((MyString) "a", 1);
	st->remove((MyString) "a");

	st->insere((MyString) "ola", 1);
	// st->imprime();
	// cout << endl;

	st->insere((MyString) "mundo", 2);
	// st->imprime();
	// cout << endl;

	st->insere((MyString) "sei lá", 10);
	// st->imprime();
	// cout << endl;

	st->insere((MyString) "outra palavra", -23);
	st->imprime();
	cout << endl;

	cout << "devolve(ola) = " << st->devolve((MyString) "ola") << endl;
	cout << "devolve(mundo) = " << st->devolve((MyString) "mundo") << endl;
	cout << endl;

	cout << "devolve(a) = " << st->devolve((MyString) "a") << endl;
	cout << "devolve(b) = " << st->devolve((MyString) "b") << endl;
	cout << endl;

	st->imprime();
	cout << endl;

	cout << "rank(ola) = " << st->rank((MyString) "ola") << endl;
	cout << "rank(sei lá) = " << st->rank((MyString) "sei lá") << endl;
	cout << "rank(outra palavra) = " << st->rank((MyString) "outra palavra") << endl;
	cout << "rank(mundo) = " << st->rank((MyString) "mundo") << endl;
	cout << endl;
	cout << "rank(a) = " << st->rank((MyString) "a") << endl;
	cout << "rank(n) = " << st->rank((MyString) "n") << endl;
	cout << "rank(zzzz) = " << st->rank((MyString) "zzzz") << endl;
	cout << endl;

	st->imprime();
	cout << endl;

	cout << "seleciona(4) = " << st->seleciona(4) << endl;
	cout << "seleciona(3) = " << st->seleciona(3) << endl;
	cout << "seleciona(2) = " << st->seleciona(2) << endl;
	cout << "seleciona(1) = " << st->seleciona(1) << endl;
	cout << "seleciona(0) = " << st->seleciona(0) << endl;

	st->remove((MyString) "outra palavra");
	cout << endl;

	st->imprime();
	cout << endl;

	cout << "seleciona(7) = " << st->seleciona(7) << endl;
	cout << "seleciona(3) = " << st->seleciona(3) << endl;
	cout << "seleciona(2) = " << st->seleciona(2) << endl;
	cout << "seleciona(1) = " << st->seleciona(1) << endl;
	cout << "seleciona(0) = " << st->seleciona(0) << endl;
	cout << "seleciona(-3) = " << st->seleciona(-3) << endl;
	cout << endl;

	st->insere((MyString) "mundo", 1);
	cout << "devolve(mundo) = " << st->devolve((MyString) "mundo") << endl;

	st->imprime();
	cout << endl;

	st->insere((MyString) "aaa", 2);
	// st->imprime();
	// cout << endl;

	st->insere((MyString) "aba", 2);
	// st->imprime();
	// cout << endl;

	st->insere((MyString) "aab", 2);
	// st->imprime();
	// cout << endl;

	st->insere((MyString) "baa", 2);
	// st->imprime();
	// cout << endl;

	st->insere((MyString) "mx", 3);
	// st->imprime();
	// cout << endl;

	st->insere((MyString) "casa", 110);
	st->imprime();
	cout << endl;

	st->remove((MyString) "a");
	st->imprime();
	cout << endl;

	st->remove((MyString) "aaa");
	// st->imprime();
	// cout << endl;

	st->remove((MyString) "aab");
	// st->imprime();
	// cout << endl;

	st->remove((MyString) "mundo");
	// st->imprime();
	// cout << endl;

	st->remove((MyString) "aba");
	// st->imprime();
	// cout << endl;

	st->remove((MyString) "ola");
	// st->imprime();
	// cout << endl;

	st->remove((MyString) "baa");
	// st->imprime();
	// cout << endl;

	st->remove((MyString) "aba");
	// st->imprime();
	// cout << endl;

	st->remove((MyString) "sei lá");
	// st->imprime();
	// cout << endl;

	st->remove((MyString) "mx");
	// st->imprime();
	// cout << endl;

	st->imprime();
	cout << endl;
}
void testeInsere(int num_op) {
	clock_t start, end;
	double elapsed, media;
	media = 0;

	cout << "Inserindo...";
	cout.flush();

	start = clock();
	for (int i = 0; i < num_op; i++) st->insere(randomWord(), 1);
	end = clock();

	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	media = elapsed / num_op;
	cout << " - Média: " << media << " segundos por operação"
	     << " - Total: " << elapsed << " segundos" << endl;
}
void testeRemove(int num_op) {
	clock_t start, end;
	double elapsed, media;
	media = 0;

	cout << "Removendo...";
	cout.flush();

	start = clock();
	for (int i = 0; i < num_op; i++) st->remove(randomWord());
	end = clock();

	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	media = elapsed / num_op;
	cout << " - Média: " << media << " segundos por operação"
	     << " - Total: " << elapsed << " segundos" << endl;
}
void testeDevolve(int num_op) {
	clock_t start, end;
	double elapsed, media;
	media = 0;

	cout << "Devolvendo...";
	cout.flush();

	start = clock();
	for (int i = 0; i < num_op; i++) st->devolve(randomWord());
	end = clock();

	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	media = elapsed / num_op;
	cout << " - Média: " << media << " segundos por operação"
	     << " - Total: " << elapsed << " segundos" << endl;
}
void testeSeleciona(int num_op) {
	clock_t start, end;
	double elapsed, media;
	media = 0;

	cout << "Selecionando...";
	cout.flush();

	start = clock();
	for (int i = 0; i < num_op; i++) st->seleciona(rand() % num_op);

	end = clock();

	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	media = elapsed / num_op;
	cout << " - Média: " << media << " segundos por operação"
	     << " - Total: " << elapsed << " segundos" << endl;
}
void testeRank(int num_op) {
	clock_t start, end;
	double elapsed, media;
	media = 0;

	cout << "Rankeando...";
	cout.flush();

	start = clock();
	for (int i = 0; i < num_op; i++) st->rank(randomWord());
	end = clock();

	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	media = elapsed / num_op;
	cout << " - Média: " << media << " segundos por operação"
	     << " - Total: " << elapsed << " segundos" << endl;
}
void testeAleatorizado(int num_op) {
	clock_t start, end;
	double elapsed, media;
	media = 0;

	cout << "Operações aleatórias...";
	cout.flush();
	int operacao;

	start = clock();
	for (int i = 0; i < num_op; i++) {
		operacao = rand() % 5;
		switch (operacao) {
			case 0: st->insere(randomWord(), rand() % 1000); break;
			case 1: st->remove(randomWord()); break;
			case 2: st->seleciona(rand() % 1000); break;
			case 3: st->devolve(randomWord()); break;
			case 4: st->rank(randomWord()); break;
			default: break;
		}
	}
	end = clock();

	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	media = elapsed / num_op;
	cout << " - Média: " << media << " segundos por operação"
	     << " - Total: " << elapsed << " segundos" << endl;
}

void testeIterativo() {
	string cmd;
	string chave;
	int indice;
	cout << "\nPossiveis operacoes do teste interativo:\n";
	cout << "INSERT <chave> \nGET <chave>\nRANK <chave>\nDELETE <chave>\nSELECT "
	        "<indice>\nPRINT\n";
	cout << "EXIT para encerrar." << endl;
	cout << ">>> ";

	while (cin >> cmd) {
		// to lower
		for (string::iterator it = cmd.begin(); it < cmd.end(); it++)
			if ('A' <= *it && *it <= 'Z') *it = *it - 'A' + 'a';
		if (cmd == "insert") {
			cin >> chave;
			st->insere(chave, 1);
			cout << "Inserido " << chave << endl;
		} else if (cmd == "get") {
			cin >> chave;
			cout << "Devolve(" << chave << ") = " << st->devolve(chave) << endl;
		} else if (cmd == "rank") {
			cin >> chave;
			cout << "Rank(" << chave << ") = " << st->rank(chave) << endl;
		} else if (cmd == "delete") {
			cin >> chave;
			st->remove(chave);
			cout << "Deletando " << chave << endl;
		} else if (cmd == "select") {
			cin >> indice;
			cout << "Seleciona(" << indice << ") = " << st->seleciona(indice) << endl;
		} else if (cmd == "print") {
			system("clear");
			st->imprime();
		} else if (cmd == "exit") {
			system("clear");
			cout << "Obrigado pela preferência" << endl;
		} else {
			cout << "Comando não é válido!" << endl;
		}
		cout << ">>> ";
	}
}

void mostreUso(char *nomePrograma) {
	cout << "Uso \n"
	     << "prompt> " << nomePrograma << " nome-arquivo tipo-tabela\n"
	     << "    nome-arquivo = nome do arquivo com o texto\n"
	     << "    tipo-tabela  = sigla de estrutura que deve ser usada" << endl;
	exit(EXIT_FAILURE);
}