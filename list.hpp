#ifndef _LIST_H
#define _LIST_H

#include <iostream>

#include "chaveItem.hpp"
#include "symbolTable.hpp"

// DECLARAÇÃO DAS CLASSES

template <typename Chave = MyString, typename Item = int>
class no_lista {
  public:
	Par<Chave, Item> *node;      // Par do nó
	no_lista<Chave, Item> *ant;  // Nó anterior
	no_lista<Chave, Item> *prox; // Próximo nó

	no_lista<Chave, Item>();
	no_lista<Chave, Item>(Par<Chave, Item> p);
	~no_lista<Chave, Item>();
};

template <typename Chave = MyString, typename Item = int>
class lista : public SymbolTable<Chave, Item> {
  public:
	no_lista<Chave, Item> *cabeca; // Nó dummy inicial
	no_lista<Chave, Item> *calda;  // Nó dummy final

	lista<Chave, Item>();
	~lista<Chave, Item>();
	void insere(Chave chave, Item valor);
	Item devolve(Chave chave);
	void remove(Chave chave);
	int rank(Chave chave);
	Chave seleciona(int k);
	void imprime();
};

template <typename Chave = MyString, typename Item = int>
class lista_ordenada : public SymbolTable<Chave, Item> {
  public:
	no_lista<Chave, Item> *cabeca; // Nó dummy inicial
	no_lista<Chave, Item> *calda;  // Nó dummy final

	lista_ordenada<Chave, Item>();
	~lista_ordenada<Chave, Item>();
	void insere(Chave chave, Item valor);
	Item devolve(Chave chave);
	void remove(Chave chave);
	int rank(Chave chave);
	Chave seleciona(int k);
	void imprime();
};

// IMPLEMENTAÇÃO NO_LISTA

template <typename Chave, typename Item>
no_lista<Chave, Item>::no_lista() : node(new Par<Chave, Item>()), ant(nullptr), prox(nullptr) {}

template <typename Chave, typename Item>
no_lista<Chave, Item>::no_lista(Par<Chave, Item> p) : ant(nullptr), prox(nullptr) {
	node = new Par<Chave, Item>();
	*node = p;
}

template <typename Chave, typename Item>
no_lista<Chave, Item>::~no_lista() {
	delete node;          // Deletamos o ponteiro 'node'
	ant = prox = nullptr; // Isso é śo para precaver
}

// IMPLEMENTAÇÃO LISTA

template <typename Chave, typename Item>
lista<Chave, Item>::lista() {
	cabeca = new no_lista<Chave, Item>();
	calda = new no_lista<Chave, Item>();

	cabeca->ant = nullptr;
	calda->prox = nullptr;
	cabeca->prox = calda;
	calda->ant = cabeca;
}

template <typename Chave, typename Item>
lista<Chave, Item>::~lista() {
	no_lista<Chave, Item> *lixo;

	while (cabeca != nullptr) {
		lixo = cabeca;
		cabeca = cabeca->prox;
		delete lixo;
	}
}

template <typename Chave, typename Item>
void lista<Chave, Item>::insere(Chave chave, Item valor) {
	no_lista<Chave, Item> *it; // um iterador

	// Primeiro buscamos se aquela chave já está na tabela
	it = cabeca->prox;
	while (it != calda) {
		if (it->node->chave == chave) {
			it->node->chavesIguais((Par<Chave, Item>){ chave, valor });
			return;
		}
		it = it->prox;
	}

	// Depois adicionamos esse par simplesmente na última posição da lista
	it = new no_lista<Chave, Item>(); // Puxamos memória do heap para nosso novo nó
	*(it->node) = (Par<Chave, Item>){ chave, valor };

	it->ant = calda->ant; // Colocamos ele entre a calda e o último da lista
	it->prox = calda;

	calda->ant->prox = it; // Depois informamos para a lista que ele foi adicionado
	calda->ant = it;
}

template <typename Chave, typename Item>
Item lista<Chave, Item>::devolve(Chave chave) {
	no_lista<Chave, Item> *it; // um iterador

	// Buscamos o elemento na tabela
	it = cabeca->prox;
	while (it != calda) {
		// Se acharmos a chave, retornamos seu valor
		if (it->node->chave == chave) return it->node->valor;
		it = it->prox;
	}

	// Se chegamos até aqui, é porque não achamos

	return {};
}

template <typename Chave, typename Item>
void lista<Chave, Item>::remove(Chave chave) {
	no_lista<Chave, Item> *it; // um iterador

	// Buscamos o elemento na tabela
	it = cabeca->prox;
	while (it != calda) {
		// Se acharmos a chave, removemos ela
		if (it->node->chave == chave) {
			// Desvinculamos ele da lista
			it->prox->ant = it->ant;
			it->ant->prox = it->prox;

			// Deletamos ele
			delete it;

			return;
		}
		it = it->prox;
	}

	// Se chegamos até aqui, é porque não achamos
}

template <typename Chave, typename Item>
int lista<Chave, Item>::rank(Chave chave) {
	no_lista<Chave, Item> *it; // um iterador
	int menores = 0;

	it = cabeca->prox;
	while (it != calda) {
		if (it->node->chave < chave) menores++;
		it = it->prox;
	}

	return menores;
}

template <typename Chave, typename Item>
Chave lista<Chave, Item>::seleciona(int k) {
	no_lista<Chave, Item> *it; // um iterador

	it = cabeca->prox;
	while (it != calda) {
		if (rank(it->node->chave) == k) return it->node->chave;
		it = it->prox;
	}

	// Se chegamos até aqui, é porque não existe chave
	return {};
}

template <typename Chave, typename Item>
void lista<Chave, Item>::imprime() {
	no_lista<Chave, Item> *it; // um iterador

	std::cout << "Lista: [\n";
	it = cabeca->prox;
	while (it != calda) {
		std::cout << *it->node << "\n";
		it = it->prox;
	}
	std::cout << "]" << std::endl;
}

// IMPLEMENTAÇÃO LISTA_ORDENADA

template <typename Chave, typename Item>
lista_ordenada<Chave, Item>::lista_ordenada() {
	cabeca = new no_lista<Chave, Item>();
	calda = new no_lista<Chave, Item>();

	cabeca->ant = nullptr;
	calda->prox = nullptr;
	cabeca->prox = calda;
	calda->ant = cabeca;
}

template <typename Chave, typename Item>
lista_ordenada<Chave, Item>::~lista_ordenada() {
	no_lista<Chave, Item> *lixo;

	while (cabeca != nullptr) {
		lixo = cabeca;
		cabeca = cabeca->prox;
		delete lixo;
	}
}

template <typename Chave, typename Item>
void lista_ordenada<Chave, Item>::insere(Chave chave, Item valor) {
	no_lista<Chave, Item> *it; // um iterador

	it = cabeca->prox;
	// Paramos assim que a chave inserida é maior ou igual ao iterador
	while (it != calda && chave < it->node->chave) { it = it->prox; }

	if (it->node->chave == chave) {
		it->node->chavesIguais((Par<Chave, Item>){ chave, valor });
		return;
	}

	// Se chegou até aqui, devemos inserir um novo nó na lista (antes de it)
	no_lista<Chave, Item> *novo = new no_lista<Chave, Item>();
	*(novo->node) = (Par<Chave, Item>){ chave, valor };

	novo->ant = it->ant;
	novo->prox = it;

	it->ant->prox = novo;
	it->ant = novo;
}

template <typename Chave, typename Item>
Item lista_ordenada<Chave, Item>::devolve(Chave chave) {
	no_lista<Chave, Item> *it; // um iterador

	it = cabeca->prox;
	// Paramos assim que a chave é maior ou igual ao iterador
	while (it != calda && chave < it->node->chave) { it = it->prox; }

	// Se for igual, retornamos o valor, se não, não retornamos nada
	if (it != calda && it->node->chave == chave) return it->node->valor;

	return {};
}

template <typename Chave, typename Item>
void lista_ordenada<Chave, Item>::remove(Chave chave) {
	no_lista<Chave, Item> *it; // um iterador

	it = cabeca->prox;
	// Paramos assim que a chave é maior ou igual ao iterador
	while (it != calda && chave < it->node->chave) { it = it->prox; }

	// Se a chave é diferente, não precisamos remover nada
	if (it == calda || it->node->chave != chave) return;

	// Se chegou até aqui, precisamos remover it
	it->prox->ant = it->ant;
	it->ant->prox = it->prox;

	delete it;
}

template <typename Chave, typename Item>
int lista_ordenada<Chave, Item>::rank(Chave chave) {
	no_lista<Chave, Item> *it; // um iterador
	int menores = 0;

	it = cabeca->prox;
	while (it != calda && chave < it->node->chave) {
		menores++;
		it = it->prox;
	}

	return menores;
}

template <typename Chave, typename Item>
Chave lista_ordenada<Chave, Item>::seleciona(int k) {
	no_lista<Chave, Item> *it; // um iterador

	it = cabeca->prox;
	while (it != calda && k > 0) {
		k--;
		it = it->prox;
	}

	return it->node->chave;
}

template <typename Chave, typename Item>
void lista_ordenada<Chave, Item>::imprime() {
	no_lista<Chave, Item> *it; // um iterador

	std::cout << "Lista: [\n";
	it = cabeca->prox;
	while (it != calda) {
		std::cout << *it->node << "\n";
		it = it->prox;
	}
	std::cout << "]" << std::endl;
}

#endif //! LIST_H
