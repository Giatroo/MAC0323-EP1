#include <iostream>
#include "vector.h"

using namespace std;

int main(int argc, const char **argv) {
	vetor_ordenado<int, string> v;

	v.insere(1, "ola");
	v.insere(2, "mundo");
	cout << v.devolve(1) << " " << v.devolve(2) << endl;
	v.insere(10, "sei lá");
	v.insere(-23, "outra palavra");
	cout << endl;

	cout << "rank(1) = " << v.rank(1) << endl;
	cout << "rank(10) = " << v.rank(10) << endl;
	cout << "rank(-23) = " << v.rank(-23) << endl;
	cout << "rank(2) = " << v.rank(2) << endl;
	cout << endl;

	cout << "seleciona(3) = " << v.seleciona(3) << endl;
	cout << "seleciona(2) = " << v.seleciona(2) << endl;
	cout << "seleciona(1) = " << v.seleciona(1) << endl;
	cout << "seleciona(0) = " << v.seleciona(0) << endl;

	v.remove(-23);
	cout << endl;
	cout << "seleciona(3) = " << v.seleciona(3) << endl;
	cout << "seleciona(2) = " << v.seleciona(2) << endl;
	cout << "seleciona(1) = " << v.seleciona(1) << endl;
	cout << "seleciona(0) = " << v.seleciona(0) << endl;

	return 0;
}