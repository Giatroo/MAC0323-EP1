#include <iostream>
#include "list.h"
#include "vector.h"

using namespace std;

lista_ordenada<> v;

MyString randomWord() {
	string a = "";
	int len = (rand() % 10) + 1;
	a.resize(len);
	for (int i = 0; i < len; i++) a[i] = (rand() % ('z' - 'a' + 1)) + 'a';
	return (MyString)a;
}

void teste() {
	srand(time(NULL));
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

	cout << "Inserindo" << endl;
	for (int i = 0; i < 1000; i++) v.insere(randomWord(), rand() % 1000);
	cout << "Removendo" << endl;
	for (int i = 0; i < 3000; i++) v.remove(randomWord());
	cout << "Selecionando" << endl;
	for (int i = 0; i < 100; i++) v.seleciona(rand() % 1000);
	cout << "Devolvendo" << endl;
	for (int i = 0; i < 3000; i++) v.devolve(randomWord());
	cout << "Rankeando" << endl;
	for (int i = 0; i < 3000; i++) v.rank(randomWord());
}

int main(int argc, const char **argv) {
	teste();

	return 0;
}