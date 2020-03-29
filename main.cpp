#include <iostream>
#include "arvoreBinaria.hpp"
#include "list.hpp"
#include "treap.hpp"
#include "vector.hpp"

using namespace std;

treap<> v;

MyString randomWord() {
	string a = "";
	int len = (rand() % 10) + 1;
	a.resize(len);
	for (int i = 0; i < len; i++) a[i] = (rand() % ('z' - 'a' + 1)) + 'a';
	return (MyString)a;
}

void teste();
void testeInicial();
void testeInsere(int num_op);
void testeRemove(int num_op);
void testeDevolve(int num_op);
void testeSeleciona(int num_op);
void testeRank(int num_op);
void testeAleatorizado(int num_op);

// ******** MAIN ********

int main(int argc, const char **argv) {
	teste();

	return 0;
}

void teste() {
	srand(time(NULL));

	testeInicial();
	// testeInsere(100000);
	// testeRank(100000);
	// testeSeleciona(3000);
	// testeDevolve(100000);
	// testeRemove(100000);
	// testeAleatorizado(500000);
}
void testeInicial() {
	v.remove((MyString) "a");
	v.remove((MyString) "b");
	v.insere((MyString) "a", 1);
	v.remove((MyString) "a");

	v.imprime();
	cout << endl;

	v.insere((MyString) "ola", 1);
	v.insere((MyString) "mundo", 2);
	v.insere((MyString) "sei lá", 10);
	v.insere((MyString) "outra palavra", -23);
	v.imprime();
	cout << endl;

	cout << v.devolve((MyString) "ola") << " " << v.devolve((MyString) "mundo");
	cout << endl;

	cout << v.devolve((MyString) "a") << " " << v.devolve((MyString) "b") << endl;
	cout << endl;

	v.imprime();
	cout << endl;

	cout << "rank(ola) = " << v.rank((MyString) "ola") << endl;
	cout << "rank(sei lá) = " << v.rank((MyString) "sei lá") << endl;
	cout << "rank(outra palavra) = " << v.rank((MyString) "outra palavra") << endl;
	cout << "rank(mundo) = " << v.rank((MyString) "mundo") << endl;
	cout << endl;
	cout << "rank(a) = " << v.rank((MyString) "a") << endl;
	cout << "rank(n) = " << v.rank((MyString) "n") << endl;
	cout << "rank(zzzz) = " << v.rank((MyString) "zzzz") << endl;
	cout << endl;

	v.imprime();
	cout << endl;

	cout << "seleciona(3) = " << v.seleciona(3) << endl;
	cout << "seleciona(2) = " << v.seleciona(2) << endl;
	cout << "seleciona(1) = " << v.seleciona(1) << endl;
	cout << "seleciona(0) = " << v.seleciona(0) << endl;

	v.remove((MyString) "outra palavra");
	cout << endl;

	v.imprime();
	cout << endl;

	cout << "seleciona(7) = " << v.seleciona(7) << endl;
	cout << "seleciona(3) = " << v.seleciona(3) << endl;
	cout << "seleciona(2) = " << v.seleciona(2) << endl;
	cout << "seleciona(1) = " << v.seleciona(1) << endl;
	cout << "seleciona(0) = " << v.seleciona(0) << endl;
	cout << "seleciona(-3) = " << v.seleciona(-3) << endl;
	cout << endl;

	v.insere((MyString) "mundo", 1);
	cout << v.devolve((MyString) "mundo") << endl;

	v.imprime();
	cout << endl;

	v.insere((MyString) "aaa", 2);
	v.insere((MyString) "aba", 2);
	v.insere((MyString) "aab", 2);
	v.insere((MyString) "baa", 2);

	v.imprime();
	cout << endl;

	v.remove((MyString) "a");
	v.remove((MyString) "aba");
	v.remove((MyString) "ola");

	v.imprime();
	cout << endl;
}
void testeInsere(int num_op) {
	clock_t start, end;
	double elapsed, media;
	media = 0;

	cout << "Inserindo...";
	cout.flush();

	start = clock();
	for (int i = 0; i < num_op; i++) v.insere(randomWord(), rand() % 1000);
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
	for (int i = 0; i < num_op; i++) v.remove(randomWord());
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
	for (int i = 0; i < num_op; i++) v.devolve(randomWord());
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
	for (int i = 0; i < num_op; i++) v.seleciona(rand() % 1000);
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
	for (int i = 0; i < num_op; i++) v.rank(randomWord());
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
			case 0: v.insere(randomWord(), rand() % 1000); break;
			case 1: v.remove(randomWord()); break;
			case 2: v.seleciona(rand() % 1000); break;
			case 3: v.devolve(randomWord()); break;
			case 4: v.rank(randomWord()); break;
			default: break;
		}
	}
	end = clock();

	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	media = elapsed / num_op;
	cout << " - Média: " << media << " segundos por operação"
	     << " - Total: " << elapsed << " segundos" << endl;
}