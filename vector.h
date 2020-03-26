/* Arquivo com implementação de uma tabela de símbolos via vetor comum e vetor
 * ordenado */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "chaveItem.h"
#include "symbolTable.h"

// DECLARAÇÃO DAS CLASSES

template <typename Chave = MyString, typename Item = int>
class vetor : public SymbolTable<Chave, Item> {
  private:
	Par<Chave, Item> *v; // O vetor de elementos
	int capacidade;      // A capacidade máxima do vetor
	int numElem;         // O número de elementos atual
	void resize();       // Duplica a capacidade
  public:
	vetor();
	~vetor();
	void insere(Chave chave, Item valor);
	Item devolve(Chave chave);
	void remove(Chave chave);
	int rank(Chave chave);
	Chave seleciona(int k);
	void imprime();
};

template <typename Chave = MyString, typename Item = int>
class vetor_ordenado : public SymbolTable<Chave, Item> {
  private:
	Par<Chave, Item> *v; // O vetor de elementos
	int capacidade;      // A capacidade máxima do vetor
	int numElem;         // O número de elementos atual
	void resize();       // Duplica a capacidade

  public:
	vetor_ordenado();
	~vetor_ordenado();
	void insere(Chave chave, Item valor);
	Item devolve(Chave chave);
	void remove(Chave chave);
	int rank(Chave chave);
	Chave seleciona(int k);
	void imprime();
};

// IMPLEMENTAÇÃO VETOR

template <typename Chave, typename Item>
vetor<Chave, Item>::vetor()
    : v(new Par<Chave, Item>[ 10 ]), capacidade(10), numElem(0) {}

template <typename Chave, typename Item>
vetor<Chave, Item>::~vetor() {
	delete[] v;
	capacidade = numElem = 0;
}

template <typename Chave, typename Item>
void vetor<Chave, Item>::resize() {
	Par<Chave, Item> *novo = new Par<Chave, Item>[ 2 * capacidade ];
	for (int i = 0; i < capacidade; i++) novo[i] = v[i];
	delete[] v;
	v = novo;
	capacidade *= 2;
}

template <typename Chave, typename Item>
void vetor<Chave, Item>::insere(Chave chave, Item valor) {
	// Primeiro procuramos se a chave já não está no vetor
	for (int i = 0; i < numElem; i++)
		if (v[i].chave == chave) {
			v[i].chavesIguais((Par<Chave, Item>){ chave, valor });
			return;
		}
	// Usamos a função definida em Par quando temos chaves iguais

	if (numElem == capacidade) resize();
	v[numElem] = (Par<Chave, Item>){ chave, valor };
	numElem++;
}

template <typename Chave, typename Item>
Item vetor<Chave, Item>::devolve(Chave chave) {
	int i;
	for (i = numElem - 1; i >= 0 && v[i].chave != chave; i--)
		;
	// Compilador dá um warming, mas se não achamos chave é não há o que fazer
	if (i != -1) return v[i].valor;
}

template <typename Chave, typename Item>
void vetor<Chave, Item>::remove(Chave chave) {
	int i;
	for (i = numElem - 1; i >= 0 && v[i].chave != chave; i--)
		;
	if (i == -1) return; // não há o que remover

	for (; i <= numElem - 2; i++) v[i] = v[i + 1];
	numElem--;
}

template <typename Chave, typename Item>
int vetor<Chave, Item>::rank(Chave chave) {
	int menores = 0;
	for (int i = 0; i < numElem; i++)
		if (v[i].chave < chave) menores++;
	return menores;
}

template <typename Chave, typename Item>
Chave vetor<Chave, Item>::seleciona(int k) {
	for (int i = 0; i < numElem; i++)
		if (rank(v[i].chave) == k) return v[i].chave;
	// Novamente o compilador vai reclamar, mas as únicas opções para esse método não
	// retornar nada é caso k < 0 ou k >= numElem (que são casos que não queremos
	// retornar nada mesmo)
}

template <typename Chave, typename Item>
void vetor<Chave, Item>::imprime() {
	std::cout << "Vetor: [\n";
	for (int i = 0; i < this->numElem; i++) std::cout << v[i] << "\n";
	std::cout << "]" << std::endl;
}

// IMPLEMENTAÇÃO VETOR_ORDENADO

template <typename Chave, typename Item>
vetor_ordenado<Chave, Item>::vetor_ordenado()
    : v(new Par<Chave, Item>[ 10 ]), capacidade(10), numElem(0) {}

template <typename Chave, typename Item>
vetor_ordenado<Chave, Item>::~vetor_ordenado() {
	delete[] v;
	capacidade = numElem = 0;
}

template <typename Chave, typename Item>
void vetor_ordenado<Chave, Item>::resize() {
	Par<Chave, Item> *novo = new Par<Chave, Item>[ 2 * capacidade ];
	for (int i = 0; i < capacidade; i++) novo[i] = v[i];
	delete[] v;
	v = novo;
	capacidade *= 2;
}

template <typename Chave, typename Item>
void vetor_ordenado<Chave, Item>::insere(Chave chave, Item valor) {
	// se a chave é maior que a maior chave, simplesmente inserimos no final
	if (numElem == 0 || chave > v[numElem - 1].chave) {
		v[numElem] = (Par<Chave, Item>){ chave, valor };
		numElem++;
		return;
	}

	// busca binária para achar a posição que queremos inserir
	int l, r, m;
	l = 0;
	r = numElem - 1;
	m = 0;
	while (l <= r) {
		m = l + (r - l) / 2;
		if (v[m].chave == chave) {
			v[m].chavesIguais((Par<Chave, Item>){ chave, valor });
			return;
		} else if (v[m].chave < chave)
			l = m + 1;
		else
			r = m - 1;
	}

	// Queremos inserir em m, logo precisamos abrir esse espaço
	if (numElem == capacidade) resize();

	for (int i = numElem; i > m && i > 0; i--) v[i] = v[i - 1];
	v[m] = (Par<Chave, Item>){ chave, valor };
	numElem++;
}

template <typename Chave, typename Item>
Item vetor_ordenado<Chave, Item>::devolve(Chave chave) {
	int l, r, m;
	l = 0;
	r = numElem - 1;
	m = 0;
	while (l <= r) {
		m = l + (r - l) / 2;
		if (v[m].chave == chave) {
			return v[m].valor;
		} else if (v[m].chave < chave)
			l = m + 1;
		else
			r = m - 1;
	}
	// Se o código chega até aqui significa que a chave não está presente
}

template <typename Chave, typename Item>
void vetor_ordenado<Chave, Item>::remove(Chave chave) {
	int l, r, m;
	l = 0;
	r = numElem - 1;
	m = 0;
	while (l <= r) {
		m = l + (r - l) / 2;
		if (v[m].chave == chave) {
			break;
		} else if (v[m].chave < chave)
			l = m + 1;
		else
			r = m - 1;
	}

	// Se m não é a chave que estamos buscando, então a chave não está presente
	if (v[m].chave != chave) return;

	for (; m <= numElem - 2; m++) v[m] = v[m + 1];

	numElem--;
}

template <typename Chave, typename Item>
int vetor_ordenado<Chave, Item>::rank(Chave chave) {
	int l, r, m;
	l = 0;
	r = numElem - 1;
	m = 0;
	while (l <= r) {
		m = l + (r - l) / 2;
		if (v[m].chave == chave) {
			break;
		} else if (v[m].chave < chave)
			l = m + 1;
		else
			r = m - 1;
	}
	return m;
}

template <typename Chave, typename Item>
Chave vetor_ordenado<Chave, Item>::seleciona(int k) {
	if (k >= 0 && k < numElem) return v[k].chave;
}

template <typename Chave, typename Item>
void vetor_ordenado<Chave, Item>::imprime() {
	std::cout << "Vetor: [\n";
	for (int i = 0; i < this->numElem; i++) std::cout << v[i] << "\n";
	std::cout << "]" << std::endl;
}

#endif // !VECTOR_H