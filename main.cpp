#include <iostream>
#include "arvoreBinaria.hpp"
#include "list.hpp"
#include "treap.hpp"
#include "tree23.hpp"
#include "vector.hpp"

using namespace std;

arvore23<> st;

MyString randomWord() {
	string a = "";
	int len = (rand() % 5) + 1;
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

void testeSplit() {
	arvore23<> a;
	no_arvore23<> *n =
	    new no_arvore23<>((Par<>){ (MyString) "Hello", 3 }, (Par<>){ (MyString) "Mundo", 1 });
	a.raiz = n;

	a.imprime();

	cout << endl;

	cout << *a.raiz->node1 << endl;
	cout << *a.raiz->node2 << endl;
	cout << a.raiz->esq << endl;
	cout << a.raiz->meio << endl;
	cout << a.raiz->dir << endl;

	cout << endl;

	a.raiz = a.split(a.raiz, ((Par<>){ (MyString) "Ola", 1 }));

	a.imprime();

	cout << endl;

	cout << *a.raiz->node1 << endl;
	// cout << *a.raiz->node2 << endl;
	cout << a.raiz->esq << endl;
	cout << a.raiz->meio << endl;
	cout << a.raiz->dir << endl;
}

void testeInsere() {
	arvore23<> a;
	no_arvore23<> *n = new no_arvore23<>((Par<>){ (MyString) "hello", 3 });

	a.raiz = n;
	a.raiz->insere((Par<>){ (MyString) "ola", 2 });
	a.imprime();

	a.raiz = a.split(a.raiz, (Par<>){ (MyString) "aac", 2 });
	a.imprime();

	a.raiz->esq->insere((Par<>){ (MyString) "aaa", 3 });
	a.imprime();

	a.raiz->esq = a.split(a.raiz->esq, (Par<>){ (MyString) "aab", 1 });
	a.imprime();

	cout << *a.raiz->esq->node1 << endl;

	a.raiz->insere(a.raiz->esq);
	a.imprime();

	// cout << endl;
	// cout << "[ " << *a.raiz->node1 << " | " << *a.raiz->node2 << " ]" << endl;
	// cout << "[ " << *a.raiz->esq->node1 << " | " << *a.raiz->esq->node2 << " ]"
	//      << endl;
	// cout << "[ " << *a.raiz->meio->node1 << " | " << *a.raiz->meio->node2 << " ]"
	//      << endl;
	// cout << "[ " << *a.raiz->dir->node1 << " | " << *a.raiz->dir->node2 << " ]"
	//      << endl;

	arvore23<> b;
	n = new no_arvore23<>((Par<>){ (MyString) "world", 3 });
	b.raiz = n;
	b.raiz->insere((Par<>){ (MyString) "hi", 1 });

	b.raiz = b.split(b.raiz, (Par<>){ (MyString) "zzz", 1 });
	b.imprime();

	b.raiz->dir->insere((Par<>){ (MyString) "zzc", 4 });
	b.raiz->dir = b.split(b.raiz->dir, (Par<>){ (MyString) "zza", -5 });
	b.raiz->insere(b.raiz->dir);
	b.imprime();

	// cout << endl;
	// cout << "[ " << *b.raiz->node1 << " | " << *b.raiz->node2 << " ]" << endl;
	// cout << "[ " << *b.raiz->esq->node1 << " | " << *b.raiz->esq->node2 << " ]"
	//      << endl;
	// cout << "[ " << *b.raiz->meio->node1 << " | " << *b.raiz->meio->node2 << " ]"
	//      << endl;
	// cout << "[ " << *b.raiz->dir->node1 << " | " << *b.raiz->dir->node2 << " ]"
	//      << endl;
}

int main(int argc, const char **argv) {
	teste();
	// testeSplit();
	// testeInsere();

	return 0;
}

void teste() {
	srand(time(NULL));

	testeInicial();
	// testeInsere(100000);
	// testeRank(100000);
	// testeSeleciona(100000);
	// testeDevolve(100000);
	// testeRemove(100000);
	// testeAleatorizado(500000);
	// st.imprime();
}
void testeInicial() {
	st.imprime();
	cout << endl;
	st.remove((MyString) "a");
	st.remove((MyString) "b");
	st.insere((MyString) "a", 1);
	st.remove((MyString) "a");

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
	// st.imprime();
	// cout << endl;

	// cout << "devolve(ola) = " << st.devolve((MyString) "ola") << endl;
	// cout << "devolve(mundo) = " << st.devolve((MyString) "mundo") << endl;
	// cout << endl;

	// cout << "devolve(a) = " << st.devolve((MyString) "a") << endl;
	// cout << "devolve(b) = " << st.devolve((MyString) "b") << endl;
	// cout << endl;

	// st.imprime();
	// cout << endl;

	// cout << "rank(ola) = " << st.rank((MyString) "ola") << endl;
	// cout << "rank(sei lá) = " << st.rank((MyString) "sei lá") << endl;
	// cout << "rank(outra palavra) = " << st.rank((MyString) "outra palavra") << endl;
	// cout << "rank(mundo) = " << st.rank((MyString) "mundo") << endl;
	// cout << endl;
	// cout << "rank(a) = " << st.rank((MyString) "a") << endl;
	// cout << "rank(n) = " << st.rank((MyString) "n") << endl;
	// cout << "rank(zzzz) = " << st.rank((MyString) "zzzz") << endl;
	// cout << endl;

	// st.imprime();
	// cout << endl;

	// cout << "seleciona(4) = " << st.seleciona(4) << endl;
	// cout << "seleciona(3) = " << st.seleciona(3) << endl;
	// cout << "seleciona(2) = " << st.seleciona(2) << endl;
	// cout << "seleciona(1) = " << st.seleciona(1) << endl;
	// cout << "seleciona(0) = " << st.seleciona(0) << endl;

	// // st.remove((MyString) "outra palavra");
	// // cout << endl;

	// // st.imprime();
	// cout << endl;

	// cout << "seleciona(7) = " << st.seleciona(7) << endl;
	// cout << "seleciona(3) = " << st.seleciona(3) << endl;
	// cout << "seleciona(2) = " << st.seleciona(2) << endl;
	// cout << "seleciona(1) = " << st.seleciona(1) << endl;
	// cout << "seleciona(0) = " << st.seleciona(0) << endl;
	// cout << "seleciona(-3) = " << st.seleciona(-3) << endl;
	// cout << endl;

	st.insere((MyString) "mundo", 1);
	// cout << st.devolve((MyString) "mundo") << endl;

	// st.imprime();
	// cout << endl;

	st.insere((MyString) "aaa", 2);
	// st.imprime();
	// cout << endl;

	st.insere((MyString) "aba", 2);
	// st.imprime();
	// cout << endl;

	st.insere((MyString) "aab", 2);
	// st.imprime();
	// cout << endl;

	st.insere((MyString) "baa", 2);
	st.imprime();
	cout << endl;

	st.remove((MyString) "a");
	st.imprime();
	cout << endl;

	st.remove((MyString) "aba");
	st.imprime();
	cout << endl;

	st.remove((MyString) "ola");
	st.imprime();
	cout << endl;

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
	for (int i = 0; i < num_op; i++) st.insere(randomWord(), 1);
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
	for (int i = 0; i < num_op; i++) st.seleciona(rand() % num_op);
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