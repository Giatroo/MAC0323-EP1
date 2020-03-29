/* Arquivo com implementação de uma tabela de símbolos via vetor comum e vetor
 * ordenado */

#ifndef _TREAP_H
#define _TREAP_H

#include <iostream>
#include "chaveItem.hpp"
#include "symbolTable.hpp"

// DECLARAÇÃO DAS CLASSES

template <typename Chave = MyString, typename Item = int>
class no_treap {
  public:
	Par<Chave, Item> *node;     // O nó em si
	int prioridade;             // A prioridade do nó
	no_treap<Chave, Item> *esq; // Filho direito
	no_treap<Chave, Item> *dir; // Filho direito
	// int numNosEsq;               // Números de nós na subárvore esquerda
	// int numNosDir;               // Número de nós na subárvore direita

	no_treap();
	no_treap(Par<Chave, Item>);
	~no_treap();
};

template <typename Chave = MyString, typename Item = int>
class treap : public SymbolTable<Chave, Item> {
  private:
	no_treap<Chave, Item> *raiz;

	// Função auxiliar do destrutor
	void deleteArvore(no_treap<Chave, Item> *);

	// Função auxiliar do imprime
	void imprimeRecursivo(no_treap<Chave, Item> *);

	// Função auxiliar do insere
	no_treap<Chave, Item> *insereRecursivo(no_treap<Chave, Item> *, Chave, Item,
	                                       bool &);

	// Função auxiliar do remove
	no_treap<Chave, Item> *removeRecursivo(no_treap<Chave, Item> *, Chave, bool &);

	// Função auxiliar do removeRecursivo
	no_treap<Chave, Item> *achaMin(no_treap<Chave, Item> *);

	// Funções de rotação
	no_treap<Chave, Item> *rotEsq(no_treap<Chave, Item> *);
	no_treap<Chave, Item> *rotDir(no_treap<Chave, Item> *);

  public:
	treap();
	~treap();
	void insere(Chave chave, Item valor);
	Item devolve(Chave chave);
	void remove(Chave chave);
	int rank(Chave chave);
	Chave seleciona(int k);
	void imprime();
};

// IMPLEMENTAÇÃO NO_TREAP

template <typename Chave, typename Item>
no_treap<Chave, Item>::no_treap()
    : node(new Par<Chave, Item>), prioridade(rand()), esq(nullptr), dir(nullptr) {}

template <typename Chave, typename Item>
no_treap<Chave, Item>::no_treap(Par<Chave, Item> p)
    : prioridade(rand()), esq(nullptr), dir(nullptr) {
	node = new Par<Chave, Item>();
	*node = p;
}

template <typename Chave, typename Item>
no_treap<Chave, Item>::~no_treap() {
	delete node;
	esq = dir = nullptr;
	prioridade = 0;
}

// IMPLEMENTAÇÃO TREAP

template <typename Chave, typename Item>
treap<Chave, Item>::treap() : raiz(nullptr) {}

template <typename Chave, typename Item>
treap<Chave, Item>::~treap() {
	deleteArvore(raiz);
}

template <typename Chave, typename Item>
void treap<Chave, Item>::deleteArvore(no_treap<Chave, Item> *raiz) {
	if (raiz != nullptr) { // Base da recursão é raiz nula

		// Deletamos as subarvores e dps deletamos a raiz
		deleteArvore(raiz->esq);
		deleteArvore(raiz->dir);
		delete raiz;
	}
}

template <typename Chave, typename Item>
no_treap<Chave, Item> *treap<Chave, Item>::rotEsq(no_treap<Chave, Item> *raiz) {
	if (raiz == nullptr || raiz->esq == nullptr) return nullptr;

	no_treap<Chave, Item> *temp = raiz->esq;
	raiz->esq = temp->dir;
	temp->dir = raiz;
	raiz = temp;
	return raiz;
}

template <typename Chave, typename Item>
no_treap<Chave, Item> *treap<Chave, Item>::rotDir(no_treap<Chave, Item> *raiz) {
	if (raiz == nullptr || raiz->dir == nullptr) return nullptr;

	no_treap<Chave, Item> *temp = raiz->dir;
	raiz->dir = temp->esq;
	temp->esq = raiz;
	raiz = temp;
	return raiz;
}

template <typename Chave, typename Item>
void treap<Chave, Item>::insere(Chave chave, Item valor) {
	bool achou = false;
	raiz = insereRecursivo(raiz, chave, valor, achou);
}

template <typename Chave, typename Item>
no_treap<Chave, Item> *treap<Chave, Item>::insereRecursivo(
    no_treap<Chave, Item> *raiz, Chave chave, Item valor, bool &achou) {
	if (raiz == nullptr) {
		raiz = new no_treap<Chave, Item>((Par<Chave, Item>){ chave, valor });
		achou = false;
		return raiz;
	}

	if (chave < raiz->node->chave) {
		raiz->esq = insereRecursivo(raiz->esq, chave, valor, achou);
		if (achou == false && raiz->esq->prioridade > raiz->prioridade)
			raiz = rotEsq(raiz);

	} else if (chave > raiz->node->chave) {
		raiz->dir = insereRecursivo(raiz->dir, chave, valor, achou);
		if (achou == false && raiz->dir->prioridade > raiz->prioridade)
			raiz = rotDir(raiz);

	} else {
		// Chaves iguais
		raiz->node->chavesIguais((Par<Chave, Item>){ chave, valor });
		achou = true;
	}
	return raiz;
}

template <typename Chave, typename Item>
Item treap<Chave, Item>::devolve(Chave chave) {
	// Exatamente igual à ABB
	no_treap<Chave, Item> *it; // iterador

	it = raiz;
	while (it != nullptr && it->node->chave != chave)
		it = (chave < it->node->chave) ? it->esq : it->dir;

	// Se chegamos aqui, ou it é nulo ou achamos it
	if (it != nullptr) return it->node->valor;
	// Retornamos apenas se não for nulo
}

template <typename Chave, typename Item>
void treap<Chave, Item>::remove(Chave chave) {}

template <typename Chave, typename Item>
int treap<Chave, Item>::rank(Chave chave) {}

template <typename Chave, typename Item>
Chave treap<Chave, Item>::seleciona(int k) {}

template <typename Chave, typename Item>
void treap<Chave, Item>::imprime() {
	std::cout << "Treap: [\n";

	imprimeRecursivo(raiz);

	std::cout << "]" << std::endl;
}

template <typename Chave, typename Item>
void treap<Chave, Item>::imprimeRecursivo(no_treap<Chave, Item> *raiz) {
	if (raiz != nullptr) { // Base da recursão é raiz nula

		// Imprimimos in-ordem
		imprimeRecursivo(raiz->esq);
		std::cout << *raiz->node << std::endl;
		imprimeRecursivo(raiz->dir);
	}
}

#endif // !_TREAP_H