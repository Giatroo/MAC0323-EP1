#include <iostream>
#include "arvoreBinaria.hpp"
#include "list.hpp"
#include "treap.hpp"
#include "vector.hpp"

using namespace std;

treap<> st;

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
	testeInsere(10000000);
	testeRank(10000000);
	testeSeleciona(10000000);
	testeDevolve(10000000);
	testeRemove(10000000);
	testeAleatorizado(50000000);
}
void testeInicial() {
	st.remove((MyString) "a");
	st.remove((MyString) "b");
	st.insere((MyString) "a", 1);
	st.remove((MyString) "a");

	st.imprime();
	cout << endl;

	st.insere((MyString) "ola", 1);
	// st.imprime();
	// cout << endl;

	st.insere((MyString) "mundo", 2);
	// st.imprime();
	// cout << endl;

	st.insere((MyString) "sei lá", 10);
	// st.imprime();
	// cout << endl;

	st.insere((MyString) "outra palavra", -23);
	st.imprime();
	cout << endl;

	cout << st.devolve((MyString) "ola") << " " << st.devolve((MyString) "mundo");
	cout << endl;

	cout << st.devolve((MyString) "a") << " " << st.devolve((MyString) "b") << endl;
	cout << endl;

	st.imprime();
	cout << endl;

	cout << "rank(ola) = " << st.rank((MyString) "ola") << endl;
	cout << "rank(sei lá) = " << st.rank((MyString) "sei lá") << endl;
	cout << "rank(outra palavra) = " << st.rank((MyString) "outra palavra") << endl;
	cout << "rank(mundo) = " << st.rank((MyString) "mundo") << endl;
	cout << endl;
	cout << "rank(a) = " << st.rank((MyString) "a") << endl;
	cout << "rank(n) = " << st.rank((MyString) "n") << endl;
	cout << "rank(zzzz) = " << st.rank((MyString) "zzzz") << endl;
	cout << endl;

	st.imprime();
	cout << endl;

	cout << "seleciona(3) = " << st.seleciona(3) << endl;
	cout << "seleciona(2) = " << st.seleciona(2) << endl;
	cout << "seleciona(1) = " << st.seleciona(1) << endl;
	cout << "seleciona(0) = " << st.seleciona(0) << endl;

	st.remove((MyString) "outra palavra");
	cout << endl;

	st.imprime();
	cout << endl;

	cout << "seleciona(7) = " << st.seleciona(7) << endl;
	cout << "seleciona(3) = " << st.seleciona(3) << endl;
	cout << "seleciona(2) = " << st.seleciona(2) << endl;
	cout << "seleciona(1) = " << st.seleciona(1) << endl;
	cout << "seleciona(0) = " << st.seleciona(0) << endl;
	cout << "seleciona(-3) = " << st.seleciona(-3) << endl;
	cout << endl;

	st.insere((MyString) "mundo", 1);
	cout << st.devolve((MyString) "mundo") << endl;

	st.imprime();
	cout << endl;

	st.insere((MyString) "aaa", 2);
	st.insere((MyString) "aba", 2);
	st.insere((MyString) "aab", 2);
	st.insere((MyString) "baa", 2);

	st.imprime();
	cout << endl;

	st.remove((MyString) "a");
	st.remove((MyString) "aba");
	st.remove((MyString) "ola");

	st.imprime();
	cout << endl;
}
void testeInsere(int num_op) {
	clock_t start, end;
	double elapsed, media;
	media = 0;

	cout << "Inserindo...";
	cout.flush();

	start = clock();
	for (int i = 0; i < num_op; i++) st.insere(randomWord(), rand() % 1000);
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
	for (int i = 0; i < num_op; i++) st.remove(randomWord());
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
	for (int i = 0; i < num_op; i++) st.devolve(randomWord());
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
	for (int i = 0; i < num_op; i++) st.seleciona(rand() % 1000);
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
	for (int i = 0; i < num_op; i++) st.rank(randomWord());
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
			case 0: st.insere(randomWord(), rand() % 1000); break;
			case 1: st.remove(randomWord()); break;
			case 2: st.seleciona(rand() % 1000); break;
			case 3: st.devolve(randomWord()); break;
			case 4: st.rank(randomWord()); break;
			default: break;
		}
	}
	end = clock();

	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	media = elapsed / num_op;
	cout << " - Média: " << media << " segundos por operação"
	     << " - Total: " << elapsed << " segundos" << endl;
}