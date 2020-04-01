/* Arquivo com implementação de uma tabela de símbolos via vetor comum e vetor
 * ordenado */

#ifndef _ARVORE_BINARIA_H
#define _ARVORE_BINARIA_H

#include <iostream>
#include "chaveItem.hpp"
#include "symbolTable.hpp"

// DECLARAÇÃO DAS CLASSES

template <typename Chave = MyString, typename Item = int>
class no_arvore {
  public:
	Par<Chave, Item> *node;      // O nó em si
	no_arvore<Chave, Item> *esq; // Filho direito
	no_arvore<Chave, Item> *dir; // Filho direito
	no_arvore<Chave, Item> *pai; // O pai
	int numNosEsq;               // Números de nós na subárvore esquerda
	int numNosDir;               // Número de nós na subárvore direita

	no_arvore();
	no_arvore(Par<Chave, Item>);
	~no_arvore();
};

template <typename Chave = MyString, typename Item = int>
class arvore_binaria : public SymbolTable<Chave, Item> {
  private:
	no_arvore<Chave, Item> *raiz;

	// Função auxiliar do destrutor
	void deleteArvore(no_arvore<Chave, Item> *);

	// Função auxiliar do imprime
	void imprimeRecursivo(no_arvore<Chave, Item> *);

	// Função auxiliar do remove
	no_arvore<Chave, Item> *removeRecursivo(no_arvore<Chave, Item> *, Chave, bool &);

	// Função auxiliar do removeRecursivo
	no_arvore<Chave, Item> *achaMin(no_arvore<Chave, Item> *);

  public:
	arvore_binaria();
	~arvore_binaria();
	void insere(Chave chave, Item valor);
	Item devolve(Chave chave);
	void remove(Chave chave);
	int rank(Chave chave);
	Chave seleciona(int k);
	void imprime();
};

// IMPLEMENTAÇÃO NO_ARVORE

template <typename Chave, typename Item>
no_arvore<Chave, Item>::no_arvore()
    : node(new Par<Chave, Item>),
      esq(nullptr),
      dir(nullptr),
      pai(nullptr),
      numNosEsq(0),
      numNosDir(0) {}

template <typename Chave, typename Item>
no_arvore<Chave, Item>::no_arvore(Par<Chave, Item> p)
    : esq(nullptr), dir(nullptr), pai(nullptr), numNosEsq(0), numNosDir(0) {
	node = new Par<Chave, Item>();
	*node = p;
}

template <typename Chave, typename Item>
no_arvore<Chave, Item>::~no_arvore() {
	delete node;
	esq = dir = pai = nullptr;
}

// IMPLEMENTAÇÃO ARVORE_BINARIA

template <typename Chave, typename Item>
arvore_binaria<Chave, Item>::arvore_binaria() : raiz(nullptr) {}

template <typename Chave, typename Item>
arvore_binaria<Chave, Item>::~arvore_binaria() {
	deleteArvore(raiz);
}

template <typename Chave, typename Item>
void arvore_binaria<Chave, Item>::deleteArvore(no_arvore<Chave, Item> *raiz) {
	if (raiz != nullptr) { // Base da recursão é raiz nula

		// Deletamos as subarvores e dps deletamos a raiz
		deleteArvore(raiz->esq);
		deleteArvore(raiz->dir);
		delete raiz;
	}
}

template <typename Chave, typename Item>
void arvore_binaria<Chave, Item>::insere(Chave chave, Item valor) {
	// Caso excepcional: raiz ser nula
	if (raiz == nullptr) {
		raiz = new no_arvore<Chave, Item>((Par<Chave, Item>){ chave, valor });
		return;
	}

	// Caso geral: raiz não é nula
	// Vamos até onde devemos inserir
	no_arvore<Chave, Item> *it, *ant; // iteradores
	ant = nullptr;                    // o anterior
	it = raiz;                        // o iterador atual

	while (it != nullptr) {
		ant = it; // Vamos atualizar o anterior
		if (chave == it->node->chave) {
			it->node->chavesIguais((Par<Chave, Item>){ chave, valor });
			return;
		} else if (chave < it->node->chave)
			it = it->esq;
		else
			it = it->dir;
	}

	// Se chegamos aqui, então it é null e anterior é o pai de it
	it = new no_arvore<Chave, Item>((Par<Chave, Item>){ chave, valor });
	it->pai = ant; // Atualizamos só o pai e deixamos esq e dir como null

	// E atualizamos o ponteiro do anterior
	if (chave < ant->node->chave)
		ant->esq = it;
	else
		ant->dir = it;

	// Agora precisamos voltar atualizando o número de nós de todos que estão no
	// caminho até essa raiz

	ant = it;
	it = it->pai;
	while (it != nullptr) {
		if (it->esq == ant)
			it->numNosEsq++;
		else
			it->numNosDir++;
		ant = it;
		it = it->pai;
	}
}

template <typename Chave, typename Item>
Item arvore_binaria<Chave, Item>::devolve(Chave chave) {
	no_arvore<Chave, Item> *it; // iterador

	it = raiz;
	while (it != nullptr && it->node->chave != chave)
		it = (chave < it->node->chave) ? it->esq : it->dir;

	// Se chegamos aqui, ou it é nulo ou achamos it
	if (it != nullptr) return it->node->valor;
	// Retornamos apenas se não for nulo
}

template <typename Chave, typename Item>
void arvore_binaria<Chave, Item>::remove(Chave chave) {
	bool achou = false;
	raiz = removeRecursivo(raiz, chave, achou);
}

template <typename Chave, typename Item>
no_arvore<Chave, Item> *arvore_binaria<Chave, Item>::removeRecursivo(
    no_arvore<Chave, Item> *it, Chave chave, bool &achou) {
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
		if (it->esq != nullptr) it->esq->pai = it;
		if (achou) it->numNosEsq--;
	} else if (chave > it->node->chave) {
		// Se queremos remover alguém que está à direita
		it->dir = removeRecursivo(it->dir, chave, achou);
		if (it->dir != nullptr) it->dir->pai = it;
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
			no_arvore<Chave, Item> *lixo = it;
			it->dir->pai = it->pai;
			it = it->dir;    // it vira a subárvore direita
			it->numNosDir--; // a sua subárvore direita agora tem um nó a menos
			// (pois a raiz dela se tornou it)
			delete lixo; // Deletamos o lixo
		} else if (it->dir == nullptr) {
			no_arvore<Chave, Item> *lixo = it;
			it->esq->pai = it->pai;
			it = it->esq;    // it vira a subárvore esquerda
			it->numNosEsq--; // a sua subárvore esquerda agora tem um nó a menos
			// (pois a raiz dela se tornou it)
			delete lixo; // Deletamos o nó
		}
		// Caso 3: tem os dois filhos
		else {
			// Procuramos a menor chave na subárvore direita
			// (o próximo inordem)
			no_arvore<Chave, Item> *temp = achaMin(it->dir);
			// Sabemos que ele existe, pois it tem dois filhos

			// Colocamos o próximo inordem no lugar no do que queríamos remover
			it->node->chave = temp->node->chave;
			it->node->valor = temp->node->valor;
			it->numNosDir--;

			// E agora o nosso problema é remover o nó do próximo inordem
			// Torcemos para que a remoção se reduza a ou o caso 1 ou o caso 2
			// mas se novamente cairmos no caso 3, vamos novamente ter que fazer
			// o processo de substituir um nó pelo próximo inordem e chamar
			// recursivamente a função de remover
			it->dir = removeRecursivo(it->dir, temp->node->chave, achou);
			if (it->dir != nullptr) it->dir->pai = it;

			// (nesse caso, 'achou' é indiferente, pois, como já falei, temos certeza
			// de que essa chave existe na nossa árvore)
			// (ou seja, 'achou' continua como true)
		}
	}

	return it; // Retornamos a nova raiz dessa subárvore
}

template <typename Chave, typename Item>
no_arvore<Chave, Item> *arvore_binaria<Chave, Item>::achaMin(
    no_arvore<Chave, Item> *it) {
	// Para achar o menor elemento de uma árvore, basta ir para a esquerda o máximo
	// posível

	while (it != nullptr && it->esq != nullptr) it = it->esq;
	return it; // Ao final, temos o menor elemento da árvore
}

template <typename Chave, typename Item>
int arvore_binaria<Chave, Item>::rank(Chave chave) {
	int menores;
	no_arvore<Chave, Item> *it; // iterador
	it = raiz;                  // o iterador atual
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
Chave arvore_binaria<Chave, Item>::seleciona(int k) {
	no_arvore<Chave, Item> *it; // iterador
	it = raiz;                  // o iterador atual
	int rank;                   // o rank do nó atual

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
}

template <typename Chave, typename Item>
void arvore_binaria<Chave, Item>::imprime() {
	std::cout << "Árvore de busca binária: [\n";

	imprimeRecursivo(raiz);

	std::cout << "]" << std::endl;
}

template <typename Chave, typename Item>
void arvore_binaria<Chave, Item>::imprimeRecursivo(no_arvore<Chave, Item> *raiz) {
	if (raiz != nullptr) { // Base da recursão é raiz nula

		// Imprimimos in-ordem
		imprimeRecursivo(raiz->esq);
		std::cout << *raiz->node << std::endl;
		imprimeRecursivo(raiz->dir);
	}
}

#endif // !_ARVORE_BINARIA_H