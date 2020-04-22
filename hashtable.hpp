/* Arquivo com implementação de uma tabela de símbolos via hashtable */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include "chaveItem.hpp"
#include "symbolTable.hpp"

// DECLARAÇÃO DAS CLASSES

template <typename Chave = MyString, typename Item = int>
class hash_node {
  public:
	Par<Chave, Item> *node;       // Par do nó
	hash_node<Chave, Item> *prox; // Próximo nó

	hash_node<Chave, Item>();
	hash_node<Chave, Item>(Par<Chave, Item> p);
	~hash_node<Chave, Item>();
};

template <typename Chave = MyString, typename Item = int>
class hashtable : public SymbolTable<Chave, Item> {
  private:
	const static int M = 10000;       // O tamanho da hashtable
	hash_node<Chave, Item> *table[M]; // O vetor de listas ligadas

	// Função de hash
	int hash(Chave chave);

  public:
	hashtable();
	~hashtable();
	void insere(Chave chave, Item valor);
	Item devolve(Chave chave);
	void remove(Chave chave);
	int rank(Chave chave);
	Chave seleciona(int k);
	void imprime();
};

// IMPLEMENTAÇÃO HASH_NODE

template <typename Chave, typename Item>
hash_node<Chave, Item>::hash_node() : node(new Par<Chave, Item>()), prox(nullptr) {}

template <typename Chave, typename Item>
hash_node<Chave, Item>::hash_node(Par<Chave, Item> p) : prox(nullptr) {
	node = new Par<Chave, Item>();
	*node = p;
}

template <typename Chave, typename Item>
hash_node<Chave, Item>::~hash_node() {
	delete node;
	prox = nullptr;
}

// IMPLEMENTAÇÃO HASHTABLE

template <typename Chave, typename Item>
hashtable<Chave, Item>::hashtable() {
	for (int i = 0; i < M; i++) table[i] = new hash_node<Chave, Item>(); // A cabeça da lista ligada
}

template <typename Chave, typename Item>
hashtable<Chave, Item>::~hashtable() {
	hash_node<Chave, Item> *it, *lixo;
	for (int i = 0; i < M; i++) {
		it = table[i];
		while (it != nullptr) {
			lixo = it;
			it = it->prox;
			delete lixo;
		}
	}
}

template <typename Chave, typename Item>
int hashtable<Chave, Item>::hash(Chave chave) {
	// Infelizmente, somos obrigado a assumir que a chave é uma string
	int index = 0;
	for (unsigned int i = 0; i < chave.size(); i++) index = (index * 256 + chave.at(i)) % M;
	return index;
}

template <typename Chave, typename Item>
void hashtable<Chave, Item>::insere(Chave chave, Item valor) {
	hash_node<Chave, Item> *it;
	it = table[hash(chave)];
	while (it->prox != nullptr) {
		it = it->prox;
		if (it->node->chave == chave) break;
	}

	if (it->node->chave == chave)
		it->node->chavesIguais({ chave, valor });
	else
		it->prox = new hash_node<Chave, Item>({ chave, valor });
}

template <typename Chave, typename Item>
Item hashtable<Chave, Item>::devolve(Chave chave) {
	hash_node<Chave, Item> *it;
	it = table[hash(chave)];
	while (it->prox != nullptr) {
		it = it->prox;
		if (it->node->chave == chave) return it->node->valor;
	}

	return {};
}

template <typename Chave, typename Item>
void hashtable<Chave, Item>::remove(Chave chave) {
	hash_node<Chave, Item> *it, *ant;

	ant = nullptr;
	it = table[hash(chave)];

	while (it->prox != nullptr) {
		ant = it;
		it = it->prox;
		if (it->node->chave == chave) break;
	}

	if (it->node->chave == chave) {
		ant->prox = it->prox; // O anterior existe pois temos uma cabeça
		delete it;
	}
}

template <typename Chave, typename Item>
int hashtable<Chave, Item>::rank(Chave chave) {
	hash_node<Chave, Item> *it;
	int menores = 0;

	for (int i = 0; i < M; i++) {
		it = table[i];
		while (it->prox != nullptr) {
			it = it->prox;
			if (it->node->chave < chave) menores++;
		}
	}

	return menores;
}

template <typename Chave, typename Item>
Chave hashtable<Chave, Item>::seleciona(int k) {
	hash_node<Chave, Item> *it;

	for (int i = 0; i < M; i++) {
		it = table[i];
		while (it->prox != nullptr) {
			it = it->prox;
			if (rank(it->node->chave) == k) return it->node->chave;
		}
	}

	return {};
}

template <typename Chave, typename Item>
void hashtable<Chave, Item>::imprime() {
	std::cout << "HashTable: [\n";

	hash_node<Chave, Item> *it;

	for (int i = 0; i < M; i++) {
		it = table[i];
		if (it->prox != nullptr) std::cout << "Posição " << i << ":\n";
		while (it->prox != nullptr) {
			it = it->prox;
			std::cout << "\t" << *it->node << "\n";
		}
	}

	std::cout << "]" << std::endl;
}

#endif // !HASH_TABLE_H