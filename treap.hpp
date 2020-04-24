/* Implementação de uma tabela de símbolos via treap
 */

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
	no_treap<Chave, Item> *esq; // Filho esquerda
	no_treap<Chave, Item> *dir; // Filho direito
	int numNosEsq;              // Números de nós na subárvore esquerda
	int numNosDir;              // Número de nós na subárvore direita

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
	no_treap<Chave, Item> *insereRecursivo(no_treap<Chave, Item> *, Chave, Item, bool &);

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
    : node(new Par<Chave, Item>),
      prioridade(rand()),
      esq(nullptr),
      dir(nullptr),
      numNosEsq(0),
      numNosDir(0) {}

template <typename Chave, typename Item>
no_treap<Chave, Item>::no_treap(Par<Chave, Item> p)
    : prioridade(rand()), esq(nullptr), dir(nullptr), numNosEsq(0), numNosDir(0) {
	node = new Par<Chave, Item>();
	*node = p;
}

template <typename Chave, typename Item>
no_treap<Chave, Item>::~no_treap() {
	delete node;
	esq = dir = nullptr;
	prioridade = numNosEsq = numNosDir = 0;
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
	raiz->numNosEsq = temp->numNosDir;
	temp->dir = raiz;
	temp->numNosDir = raiz->numNosEsq + raiz->numNosDir + 1;
	raiz = temp;
	return raiz;
}

template <typename Chave, typename Item>
no_treap<Chave, Item> *treap<Chave, Item>::rotDir(no_treap<Chave, Item> *raiz) {
	if (raiz == nullptr || raiz->dir == nullptr) return nullptr;

	no_treap<Chave, Item> *temp = raiz->dir;
	raiz->dir = temp->esq;
	raiz->numNosDir = temp->numNosEsq;
	temp->esq = raiz;
	temp->numNosEsq = raiz->numNosEsq + raiz->numNosDir + 1;
	raiz = temp;
	return raiz;
}

template <typename Chave, typename Item>
void treap<Chave, Item>::insere(Chave chave, Item valor) {
	bool achou = false;
	raiz = insereRecursivo(raiz, chave, valor, achou);
}

template <typename Chave, typename Item>
no_treap<Chave, Item> *treap<Chave, Item>::insereRecursivo(no_treap<Chave, Item> *raiz, Chave chave,
                                                           Item valor, bool &achou) {
	if (raiz == nullptr) {
		raiz = new no_treap<Chave, Item>((Par<Chave, Item>){ chave, valor });
		achou = false;
		return raiz;
	}

	if (chave < raiz->node->chave) {
		raiz->esq = insereRecursivo(raiz->esq, chave, valor, achou);
		if (!achou) {
			raiz->numNosEsq++;
			if (raiz->esq->prioridade > raiz->prioridade) raiz = rotEsq(raiz);
		}

	} else if (chave > raiz->node->chave) {
		raiz->dir = insereRecursivo(raiz->dir, chave, valor, achou);
		if (!achou) {
			raiz->numNosDir++;
			if (raiz->dir->prioridade > raiz->prioridade) raiz = rotDir(raiz);
		}
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

	return {};
}

template <typename Chave, typename Item>
void treap<Chave, Item>::remove(Chave chave) {
	bool achou = false;
	raiz = removeRecursivo(raiz, chave, achou);
}

template <typename Chave, typename Item>
no_treap<Chave, Item> *treap<Chave, Item>::removeRecursivo(no_treap<Chave, Item> *it, Chave chave,
                                                           bool &achou) {
	// Se é nulo
	if (it == nullptr) {
		// Chegamos aqui ou se a raiz era nula ou se descemos nossa árvore e ela não
		// possuia essa chave
		achou = false;
		return nullptr;
	}

	if (chave < it->node->chave) {
		// Se queremos remover alguém que está à esquerda
		it->esq = removeRecursivo(it->esq, chave, achou);
		if (achou) it->numNosEsq--;
	} else if (chave > it->node->chave) {
		// Se queremos remover alguém que está à direita
		it->dir = removeRecursivo(it->dir, chave, achou);
		if (achou) it->numNosDir--;
	} else {
		// Se achamos quem estamos tentando remover
		achou = true;

		// Caso 1: é uma folha
		if (it->esq == nullptr && it->dir == nullptr) {
			delete it;
			it = nullptr;
			return nullptr;
		}
		// Caso 2: tem apenas um filho
		else if (it->esq == nullptr) {
			no_treap<Chave, Item> *lixo = it;
			it = it->dir;    // it vira a subárvore direita
			it->numNosDir--; // a sua subárvore direita agora tem um nó a menos
			// (pois a raiz dela se tornou it)
			delete lixo; // Deletamos o lixo
		} else if (it->dir == nullptr) {
			no_treap<Chave, Item> *lixo = it;
			it = it->esq;    // it vira a subárvore esquerda
			it->numNosEsq--; // a sua subárvore esquerda agora tem um nó a menos
			// (pois a raiz dela se tornou it)
			delete lixo; // Deletamos o nó
		}
		// Caso 3: tem os dois filhos
		else {
			// Procuramos a menor chave na subárvore direita
			// (o próximo inordem)
			no_treap<Chave, Item> *temp = achaMin(it->dir);
			// Sabemos que ele existe, pois it tem dois filhos

			// Colocamos o próximo inordem no lugar no do que queríamos remover
			it->node->chave = temp->node->chave;
			it->node->valor = temp->node->valor;
			// A prioridade não importa, pois ela é parte do nó, não do Par
			it->numNosDir--;

			// E agora o nosso problema é remover o nó do próximo inordem
			// Torcemos para que a remoção se reduza a ou o caso 1 ou o caso 2
			// mas se novamente cairmos no caso 3, vamos novamente ter que fazer
			// o processo de substituir um nó pelo próximo inordem e chamar
			// recursivamente a função de remover
			it->dir = removeRecursivo(it->dir, temp->node->chave, achou);

			// (nesse caso, 'achou' é indiferente, pois, como já falei, temos certeza
			// de que essa chave existe na nossa árvore)
			// (ou seja, 'achou' continua como true)
		}
	}

	return it; // Retornamos a nova raiz dessa subárvore
}

template <typename Chave, typename Item>
no_treap<Chave, Item> *treap<Chave, Item>::achaMin(no_treap<Chave, Item> *it) {
	// Para achar o menor elemento de uma árvore, basta ir para a esquerda o máximo
	// posível

	while (it != nullptr && it->esq != nullptr) it = it->esq;
	return it; // Ao final, temos o menor elemento da árvore
}

template <typename Chave, typename Item>
int treap<Chave, Item>::rank(Chave chave) {
	int menores;
	no_treap<Chave, Item> *it; // iterador
	it = raiz;                 // o iterador atual
	menores = 0;

	while (it != nullptr) {
		if (chave == it->node->chave) {
			return menores + it->numNosEsq; // O número de caras menores que ele
		} else if (chave < it->node->chave)
			it = it->esq;
		else {
			menores += (it->numNosEsq + 1);
			it = it->dir;
		}
	}

	return menores;
}

template <typename Chave, typename Item>
Chave treap<Chave, Item>::seleciona(int k) {
	no_treap<Chave, Item> *it; // iterador
	it = raiz;                 // o iterador atual
	int rank;                  // o rank do nó atual

	if (raiz != nullptr) rank = raiz->numNosEsq;

	while (it != nullptr) {
		if (rank == k)
			return it->node->chave;
		else if (rank > k) {
			it = it->esq;
			if (it != nullptr) rank += (-1 - it->numNosDir);
		} else {
			it = it->dir;
			if (it != nullptr) rank += (1 + it->numNosEsq);
		}
	}

	return {};
}

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
		std::cout << *raiz->node << "\n";
		imprimeRecursivo(raiz->dir);
	}
}

#endif // !_TREAP_H