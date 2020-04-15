/* Implementação de uma tabela de símbolos via árvores-2-3
 */

#ifndef _ARVORE23_H
#define _ARVORE23_H

#include <iostream>
#include "chaveItem.hpp"
#include "symbolTable.hpp"

// DECLARAÇÃO DAS CLASSES

template <typename Chave = MyString, typename Item = int>
class no_arvore23 {
  public:
	Par<Chave, Item> *node1;        // O par da esquerda
	Par<Chave, Item> *node2;        // O par da direita
	no_arvore23<Chave, Item> *esq;  // Filho esquerdo
	no_arvore23<Chave, Item> *meio; // Filho do meio
	no_arvore23<Chave, Item> *dir;  // Filho direito

	bool node2preenchido; // Indica se o nó 2 está preenchido ou não

	no_arvore23();
	no_arvore23(Par<Chave, Item>);
	no_arvore23(Par<Chave, Item>, Par<Chave, Item>);
	~no_arvore23();

	// Funções auxiliares
	bool ehFolha();                          // Retorna se todos os ponteiros são nulos
	bool cheia();                            // Retorna se node1 e node2 estão preenchidos
	void insere(Par<Chave, Item>);           // Insere um novo par no nó
	void insere(no_arvore23<Chave, Item> *); // Insere uma árvore nesse nó
	                                         // essa árvore deve ser filha
	                                         // do nó e ele deve ter apenas um par
	void debug();
};

template <typename Chave = MyString, typename Item = int>
class arvore23 : public SymbolTable<Chave, Item> {
  private:
	no_arvore23<Chave, Item> *raiz;

	// Função auxiliar do destrutor
	void deleteArvore(no_arvore23<Chave, Item> *);

	// Função auxiliar do imprime
	void imprimeRecursivo(no_arvore23<Chave, Item> *);

	// Função auxiliar do insere
	no_arvore23<Chave, Item> *insereRecursivo(no_arvore23<Chave, Item> *, Chave, Item, bool &,
	                                          bool &);

	// Função auxiliar do remove
	// Temos dois nós, pai e filho, e estaremos removendo uma chave do filho. O pai serve apenas
	// como nó auxiliar. Além disso, usamos dois booleanos achou e diminuiu
	// O primeiro indica se achamos a chave que estávamos tentando remover em alguma subárvore do
	// filho
	// O segundo indica se uma subárvore diminuiu de tamanho
	no_arvore23<Chave, Item> *removeRecursivo(no_arvore23<Chave, Item> *pai,
	                                          no_arvore23<Chave, Item> *filho, Chave, bool &achou,
	                                          bool &diminuiu);

	no_arvore23<Chave, Item> *removeFolha(no_arvore23<Chave, Item> *folha, Chave ch);

	// Insere um novo par em um nó que já tinha dois pares.
	// Cria três nós cada um com um par cada onde o nó de chave intermediária
	// é retonado como um ponteiro, o de menor chave em sua esquerda e o de maior
	// chave em sua direita
	no_arvore23<Chave, Item> *split(no_arvore23<Chave, Item> *, Par<Chave, Item>);

	// Insere uma nova subárvore em um nó que já tinha dois pares
	// Cria três nós de forma que o de chave intermediária é retornada
	no_arvore23<Chave, Item> *split(no_arvore23<Chave, Item> *, no_arvore23<Chave, Item> *);

	// Dados dois nós a e b, onde b é filho de a e b foi splitado, queremos inserir
	// a raiz de b após o split em a. Caso a não precise ser splitado, o retorno
	// será um ponteiro para a, caso contrário, o retorno era um ponteiro para a raiz
	// da nova subárvore (após o split de a)
	no_arvore23<Chave, Item> *join(no_arvore23<Chave, Item> *a, no_arvore23<Chave, Item> *b);

	// Dados dois nós, a e b, onde b é filho de a e b teve um elemento removido,
	// a função vê se algum dos irmãos adjacentes de b podem lhe emprestar um par
	// Se sim, a função o faz e retorna true. Se não é possível, a função apenas
	// retorna false
	bool borrow(no_arvore23<Chave, Item> *, no_arvore23<Chave, Item> *);

	// Dados dois nós, a e b, onde b é filho de a e b teve um elemento removido, mas
	// não foi possível emprestar do irmão, precisamos que um par do pai desça para o
	// irmão do filho removido. Se o pai era um 3-nó, então tudo certo, mas caso
	// contrário, temos que avisar que o pai ficou vazio e precisamos seguir
	// arrumando a árvore
	void merge(no_arvore23<Chave, Item> *, no_arvore23<Chave, Item> *);

	// Funções para achar o maior e menor elementos de uma árvore 2-3
	// Vale a pena perceber que este elemento sempre está numa folha
	no_arvore23<Chave, Item> *achaMaior(no_arvore23<Chave, Item> *);
	no_arvore23<Chave, Item> *achaMenor(no_arvore23<Chave, Item> *);

	int numNosEsq(no_arvore23<Chave, Item> *);  // Números de nós na subárvore esquerda
	int numNosMeio(no_arvore23<Chave, Item> *); // Número de nós na subárvore do meio
	int numNosDir(no_arvore23<Chave, Item> *);  // Número de nós na subárvore direita

  public:
	arvore23();
	~arvore23();
	void insere(Chave chave, Item valor);
	Item devolve(Chave chave);
	void remove(Chave chave);
	int rank(Chave chave);
	Chave seleciona(int k);
	void imprime();
};

// IMPLEMENTAÇÃO NO_ARVORE23

template <typename Chave, typename Item>
no_arvore23<Chave, Item>::no_arvore23()
    : node1(new Par<Chave, Item>),
      node2(new Par<Chave, Item>),
      esq(nullptr),
      meio(nullptr),
      dir(nullptr),
      node2preenchido(false) {}

template <typename Chave, typename Item>
no_arvore23<Chave, Item>::no_arvore23(Par<Chave, Item> p)
    : node2(new Par<Chave, Item>),
      esq(nullptr),
      meio(nullptr),
      dir(nullptr),
      node2preenchido(false) {
	node1 = new Par<Chave, Item>;
	*node1 = p;
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item>::no_arvore23(Par<Chave, Item> p1, Par<Chave, Item> p2)
    : esq(nullptr), meio(nullptr), dir(nullptr), node2preenchido(true) {
	node1 = new Par<Chave, Item>;
	*node1 = p1;
	node2 = new Par<Chave, Item>;
	*node2 = p2;
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item>::~no_arvore23() {
	delete node1;
	delete node2;
	esq = meio = dir = nullptr;
}

template <typename Chave, typename Item>
bool no_arvore23<Chave, Item>::ehFolha() {
	return (esq == nullptr && meio == nullptr && dir == nullptr);
}

template <typename Chave, typename Item>
bool no_arvore23<Chave, Item>::cheia() {
	return node2preenchido;
}

template <typename Chave, typename Item>
void no_arvore23<Chave, Item>::insere(Par<Chave, Item> p) {
	// Se estamos inserindo nesse nó, então temos certeza que ele é uma folha
	if (this->node1->chave < p.chave) {
		*node2 = p;
	} else { // Se a chave é menor, precisamos puxar a esq pra dir e inserir na esq
		*node2 = *node1;
		*node1 = p;
	}
	this->node2preenchido = true;
}

template <typename Chave, typename Item>
void no_arvore23<Chave, Item>::insere(no_arvore23<Chave, Item> *p) {
	if (this->node1->chave < p->node1->chave) { // filhos da direita
		*this->node2 = *p->node1;
		this->meio = p->esq;
		// this->numNosMeio = p->numNosEsq;
		this->dir = p->dir;
		// this->numNosDir = p->numNosDir;
	} else { // filhos da esquerda
		*this->node2 = *this->node1;
		*this->node1 = *p->node1;
		this->esq = p->esq;
		// this->numNosEsq = p->numNosEsq;
		this->meio = p->dir;
		// this->numNosMeio = p->numNosDir;
	}
	this->node2preenchido = true;
	delete p;
}

template <typename Chave, typename Item>
void no_arvore23<Chave, Item>::debug() {
	std::cout << "[ " << *this->node1 << " | ";
	if (this->cheia())
		std::cout << *this->node2;
	else
		std::cout << " vazio ";
	std::cout << " ]\t com filhos:\n";

	std::cout << "\tEsq:  ";
	if (this->esq) {
		std::cout << "[ " << *this->esq->node1 << " | ";
		if (this->esq->cheia())
			std::cout << *this->esq->node2;
		else
			std::cout << " vazio ";
		std::cout << " ]\n";
	} else {
		std::cout << "null\n";
	}

	std::cout << "\tMeio: ";
	if (this->meio) {
		std::cout << "[ " << *this->meio->node1 << " | ";
		if (this->meio->cheia())
			std::cout << *this->meio->node2;
		else
			std::cout << " vazio ";
		std::cout << " ]\n";
	} else {
		std::cout << "null\n";
	}

	std::cout << "\tDir:  ";
	if (this->dir) {
		std::cout << "[ " << *this->dir->node1 << " | ";
		if (this->dir->cheia())
			std::cout << *this->dir->node2;
		else
			std::cout << " vazio ";
		std::cout << " ]\n";
	} else {
		std::cout << "null\n";
	}
}

// IMPLEMENTAÇÃO ARVORE23

template <typename Chave, typename Item>
arvore23<Chave, Item>::arvore23() : raiz(nullptr) {}

template <typename Chave, typename Item>
arvore23<Chave, Item>::~arvore23() {
	deleteArvore(raiz);
}

template <typename Chave, typename Item>
void arvore23<Chave, Item>::deleteArvore(no_arvore23<Chave, Item> *raiz) {
	if (raiz != nullptr) { // Base da recursão é raiz nula

		// Deletamos as subarvores e dps deletamos a raiz
		deleteArvore(raiz->esq);
		deleteArvore(raiz->meio);
		deleteArvore(raiz->dir);
		delete raiz;
	}
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::split(no_arvore23<Chave, Item> *node,
                                                       Par<Chave, Item> p) {
	// Split é uma operação feita em folhas apenas
	// A folha node está cheia e queremos inserir p

	// Vamos criar três nós que serão o resultado do split
	no_arvore23<Chave, Item> *esq, *meio, *dir;

	if (p.chave > node->node2->chave) {
		dir = new no_arvore23<Chave, Item>(p);
		meio = new no_arvore23<Chave, Item>(
		    (Par<Chave, Item>){ node->node2->chave, node->node2->valor });
		esq = new no_arvore23<Chave, Item>(
		    (Par<Chave, Item>){ node->node1->chave, node->node1->valor });
	} else if (p.chave > node->node1->chave) {
		dir = new no_arvore23<Chave, Item>(
		    (Par<Chave, Item>){ node->node2->chave, node->node2->valor });
		meio = new no_arvore23<Chave, Item>(p);
		esq = new no_arvore23<Chave, Item>(
		    (Par<Chave, Item>){ node->node1->chave, node->node1->valor });
	} else {
		dir = new no_arvore23<Chave, Item>(
		    (Par<Chave, Item>){ node->node2->chave, node->node2->valor });
		meio = new no_arvore23<Chave, Item>(
		    (Par<Chave, Item>){ node->node1->chave, node->node1->valor });
		esq = new no_arvore23<Chave, Item>(p);
	}

	meio->esq = esq;
	meio->dir = dir;
	// meio->numNosEsq = meio->numNosDir = 1;
	delete node; // Não usaremos para mais nada aquele nó antigo
	return meio;
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::split(no_arvore23<Chave, Item> *pai,
                                                       no_arvore23<Chave, Item> *filho) {
	no_arvore23<Chave, Item> *menor, *meior, *maior; // meior pq sim
	// Precisamos descobrir se o filho é da esquerda, meio ou direita

	if (pai->esq == filho) {
		// filho é a esquerda
		// logo, filho->node1->chave < pai->node1->chave < pai->node2->chave
		menor = filho;
		meior = new no_arvore23<Chave, Item>(*pai->node1);
		maior = new no_arvore23<Chave, Item>(*pai->node2);

		maior->esq = pai->meio;
		// maior->numNosEsq = pai->numNosMeio;
		maior->dir = pai->dir;
		// maior->numNosDir = pai->numNosDir;
		// o menor é o filho, manterá suas subárvores
	} else if (pai->meio == filho) {
		// filho é o meio
		// logo, pai->node1->chave < filho->node1->chave < pai->node2->chave
		menor = new no_arvore23<Chave, Item>(*pai->node1);
		meior = filho;
		maior = new no_arvore23<Chave, Item>(*pai->node2);

		menor->esq = pai->esq;
		// menor->numNosEsq = pai->numNosEsq;
		menor->dir = filho->esq;
		// menor->numNosDir = filho->numNosEsq;
		maior->esq = filho->dir;
		// maior->numNosEsq = filho->numNosDir;
		maior->dir = pai->dir;
		// maior->numNosDir = pai->numNosDir;
		// o meio é o filho, já salvamos suas subárvores
	} else {
		// filho é a direita
		// logo, pai->node1->chave < pai->node2->chave < filho->node1->chave
		menor = new no_arvore23<Chave, Item>(*pai->node1);
		meior = new no_arvore23<Chave, Item>(*pai->node2);
		maior = filho;

		menor->esq = pai->esq;
		// menor->numNosEsq = pai->numNosEsq;
		menor->dir = pai->meio;
		// menor->numNosDir = pai->numNosMeio;
		// o maior é o filho, materá suas subárvores
	}

	// o meio é a raiz, a sua esquerda e direita sempre serão menor e maior
	meior->esq = menor;
	// meior->numNosEsq = menor->numNosEsq + menor->numNosDir + 1;
	meior->dir = maior;
	// meior->numNosDir = maior->numNosEsq + maior->numNosDir + 1;

	pai->esq = pai->meio = pai->dir = nullptr;
	delete pai;   // O antigo nó do pai (que tinha dois elementos) agora não existe
	              // mais (foi splitado)
	pai = meior;  // Faremos o ponteiro apontar para o meior (nova raiz) apenas para
	              // evitar erros (de acesso a um pointeiro que sofreu delete)
	return meior; // Retornamos a nova raiz
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::join(no_arvore23<Chave, Item> *pai,
                                                      no_arvore23<Chave, Item> *filho) {
	// Temos dois tipos de join, quando pai está cheio ou quando há lugar
	// para inserirmos

	if (!pai->cheia()) {
		// O caso fácil é quando o pai não está cheio
		pai->insere(filho); // Basta utilizar a função insere
	} else {
		// O caso difícil é quando precisamos dar split novamente no pai
		pai = split(pai, filho); // Criei uma função para fazer isso
	}
	// Ao final, retornamos o pai, que continua como raiz dessa subárvore
	return pai;
}

template <typename Chave, typename Item>
void arvore23<Chave, Item>::insere(Chave chave, Item valor) {
	bool achou = false;
	bool cresceu = false;
	raiz = insereRecursivo(raiz, chave, valor, achou, cresceu);
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::insereRecursivo(no_arvore23<Chave, Item> *raiz,
                                                                 Chave chave, Item valor,
                                                                 bool &achou, bool &cresceu) {
	// 1. Raiz nula
	if (raiz == nullptr) {
		raiz = new no_arvore23<Chave, Item>((Par<Chave, Item>){ chave, valor });
		achou = false;
		cresceu = true; // De certa forma, cresceu
		return raiz;
	}

	// 2. Folha
	if (raiz->ehFolha()) {
		if (!raiz->cheia()) {
			// 2.1 Folha com espaço

			if (raiz->node1->chave == chave) {
				// 2.1.1 Achamos a chave
				raiz->node1->chavesIguais((Par<Chave, Item>){ chave, valor });
				achou = true;
			} else {
				// 2.1.2 Precisamos inserir na folha
				raiz->insere((Par<Chave, Item>){ chave, valor });
				achou = false;
			}

			cresceu = false; // não cresceu
			return raiz;     // Retornamos a raiz
		} else {
			// 2.2 Folha sem espaço
			if (raiz->node1->chave == chave) {
				// 2.2.1 Achamos a chave no par 1
				raiz->node1->chavesIguais((Par<Chave, Item>){ chave, valor });
				achou = true;
			} else if (raiz->node2->chave == chave) {
				// 2.2.2 Achamos a chave no par 2
				raiz->node2->chavesIguais((Par<Chave, Item>){ chave, valor });
				achou = true;
			} else {
				// 2.2.3 Não achamos a chave e precisamos inseri-la aqui
				raiz = split(raiz, (Par<Chave, Item>){ chave, valor });
				cresceu = true; // Splitamos, então cresceu
				achou = false;
			}
			return raiz; // Retornamos a nova raiz
		}
	}

	// 3. Não é folha
	if (!raiz->cheia()) {
		// 3.1 Não é um nó com dois pares
		if (raiz->node1->chave == chave) {
			// 3.1.1 Achamos a chave
			raiz->node1->chavesIguais((Par<Chave, Item>){ chave, valor });
			achou = true;
		} else if (raiz->node1->chave > chave) {
			// 3.1.2.1 Precisamos inserir na subárvore esquerda
			raiz->esq = insereRecursivo(raiz->esq, chave, valor, achou, cresceu);

			// 3.1.2.2 Se a chave foi inserida, aumentamos o número de caras na
			// direita
			// if (!achou) raiz->numNosEsq++;

			// 3.1.2.3 Precisamos agora verificar se a subárvore esquerda cresceu
			if (cresceu) raiz->insere(raiz->esq); // Inserimos a subárvore esquerda nesse nó
		} else {
			// 3.1.3.1 Precisamos inserir na subárvore direita
			raiz->dir = insereRecursivo(raiz->dir, chave, valor, achou, cresceu);

			// 3.1.3.2 Se a chave foi inserida, aumentamos o número de caras na
			// direita
			// if (!achou) raiz->numNosDir++;

			// 3.1.3.3 Precisamos agora verificar se a subárvore direita cresceu
			if (cresceu) raiz->insere(raiz->dir); // Inserimos a subárvore direita nesse nó
		}

		cresceu = false; // Não vai crescer, pois só tinha inicialmente um par
		return raiz;     // Retornamos a raiz
	} else {
		// 3.2 É um nó com dois pares
		if (chave < raiz->node1->chave) {
			// 3.2.1.1 Precisamos inserir na subárvore esquerda
			raiz->esq = insereRecursivo(raiz->esq, chave, valor, achou, cresceu);

			// 3.2.1.2 Se a chave foi inserida, aumentamos o número de caras na
			// esquerda
			// if (!achou) raiz->numNosEsq++;

			// 3.2.1.3 Precisamos agora verificar se a subárvore esquerda cresceu
			if (cresceu) {
				raiz = join(raiz, raiz->esq);
				// para deixa enfático que essa subárvore também cresceu:
				cresceu = true;
			}
		} else if (chave == raiz->node1->chave) {
			// 3.2.2 Achamos a chave no primeiro par
			raiz->node1->chavesIguais((Par<Chave, Item>){ chave, valor });
			achou = true;
			cresceu = false;
		} else if (chave < raiz->node2->chave) {
			// 3.2.3.1 Precisamos inserir na subárvore do meio
			raiz->meio = insereRecursivo(raiz->meio, chave, valor, achou, cresceu);

			// 3.2.3.2 Se a chave foi inserida, aumentamos o número de caras no meio
			// if (!achou) raiz->numNosMeio++;

			// 3.2.3.3 Precisamos agora verificar se a subárvore do meio cresceu
			if (cresceu) {
				raiz = join(raiz, raiz->meio);
				// para deixa enfático que essa subárvore também cresceu:
				cresceu = true;
			}
		} else if (chave == raiz->node2->chave) {
			// 3.2.4 Achamos a chave no segundo par
			raiz->node2->chavesIguais((Par<Chave, Item>){ chave, valor });
			achou = true;
			cresceu = false;
		} else {
			// 3.2.5.1 Precisamos inserir na subárvore direita
			raiz->dir = insereRecursivo(raiz->dir, chave, valor, achou, cresceu);

			// 3.2.5.2 Se a chave foi inserida, aumentamos o número de caras na
			// direita
			// if (!achou) raiz->numNosDir++;

			// 3.2.5.3 Precisamos agora verificar se a subárvore direita cresceu
			if (cresceu) {
				raiz = join(raiz, raiz->dir);
				// para deixa enfático que essa subárvore também cresceu:
				cresceu = true;
			}
		}
		return raiz;
	}
}

template <typename Chave, typename Item>
int arvore23<Chave, Item>::numNosEsq(no_arvore23<Chave, Item> *no) {
	if (no == nullptr) return 0;
	if (no->esq == nullptr) return 0;
	return (no->esq->cheia() ? 2 : 1) + numNosEsq(no->esq) + numNosMeio(no->esq) +
	       numNosDir(no->esq);
}

template <typename Chave, typename Item>
int arvore23<Chave, Item>::numNosMeio(no_arvore23<Chave, Item> *no) {
	if (no == nullptr) return 0;
	if (no->meio == nullptr || !no->cheia()) return 0;
	return (no->meio->cheia() ? 2 : 1) + numNosEsq(no->meio) + numNosMeio(no->meio) +
	       numNosDir(no->meio);
}

template <typename Chave, typename Item>
int arvore23<Chave, Item>::numNosDir(no_arvore23<Chave, Item> *no) {
	if (no == nullptr) return 0;
	if (no->dir == nullptr) return 0;
	return (no->dir->cheia() ? 2 : 1) + numNosEsq(no->dir) + numNosMeio(no->dir) +
	       numNosDir(no->dir);
}

template <typename Chave, typename Item>
Item arvore23<Chave, Item>::devolve(Chave chave) {
	// Mais ou menos o algoritmo clássico de ABB
	no_arvore23<Chave, Item> *it; // iterador

	it = raiz;

	while (it != nullptr) {
		if (chave < it->node1->chave)
			it = it->esq;
		else if (chave == it->node1->chave)
			return it->node1->valor;
		else if (it->cheia() && chave < it->node2->chave) // Só para 3-nó
			it = it->meio;
		else if (it->cheia() && chave == it->node2->chave) // Só para 3-nó
			return it->node2->valor;
		else
			it = it->dir;
	}

	// Se não encontramos a chave, não devolvemos nada
	return {};
}

template <typename Chave, typename Item>
bool arvore23<Chave, Item>::borrow(no_arvore23<Chave, Item> *pai, no_arvore23<Chave, Item> *filho) {
	// primeiro, precisamos descobrir se o filho é da esquerda, meio ou direita
	no_arvore23<Chave, Item> *irmao;

	if (filho == pai->esq) {
		// 1. O filho é filho esquerdo
		if (pai->cheia()) {
			// 1.1 Se o pai possiu três filhos, olhamos para o filho do meio
			irmao = pai->meio;
		} else {
			// 1.2 Se o pai possui dois filhos, olhamos para o filho da direita
			irmao = pai->dir;
		}

		if (!irmao->cheia()) // Se o irmão só possui um par
			return false;    // Então não conseguimos emprestar e retornamos false

		// Caso contrário, fazemos o empréstimo
		*filho->node1 = *pai->node1;
		*pai->node1 = *irmao->node1;
		*irmao->node1 = *irmao->node2;
		irmao->node2preenchido = false;
		// Se o irmao é uma folha, tudo ok, precisamos ver o caso em que não é
		if (filho->esq == nullptr) filho->esq = filho->dir;

		filho->dir = irmao->esq;
		irmao->esq = irmao->meio;
		irmao->meio = nullptr;
	} else if (pai->cheia() && filho == pai->meio) {
		// 2. O filho é filho do meio
		if (!pai->esq->cheia() && !pai->dir->cheia())
			return false; // Se não dos irmão está cheio, não dá pra emprestar

		if (pai->esq->cheia()) {
			// 2.1 Se o irmão esquerdo está cheio
			irmao = pai->esq;
			*filho->node1 = *pai->node1;
			*pai->node1 = *irmao->node2;
			irmao->node2preenchido = false;
			// Se o irmao é uma folha, tudo ok, precisamos ver o caso em que não é
			if (filho->dir == nullptr) filho->dir = filho->esq;

			filho->esq = irmao->dir;
			irmao->dir = irmao->meio;
			irmao->meio = nullptr;
		} else {
			// 2.2 Se o irmão direito está cheio
			irmao = pai->dir;
			*filho->node1 = *pai->node2;
			*pai->node2 = *irmao->node1;
			*irmao->node1 = *irmao->node2;
			irmao->node2preenchido = false;
			// Se o irmao é uma folha, tudo ok, precisamos ver o caso em que não é
			if (filho->esq == nullptr) filho->esq = filho->dir;

			filho->dir = irmao->esq;
			irmao->esq = irmao->meio;
			irmao->meio = nullptr;
		}
	} else {
		// 3. O filho é filho direito
		if (pai->cheia()) {
			// 1.1 Se o pai possiu três filhos, olhamos para o filho do meio
			irmao = pai->meio;
		} else {
			// 1.2 Se o pai possui dois filhos, olhamos para o filho da esquerda
			irmao = pai->esq;
		}

		if (!irmao->cheia()) // Se o irmão só possui um par
			return false;    // Então não conseguimos emprestar e retornamos false

		if (pai->cheia()) {
			*filho->node1 = *pai->node2;
			*pai->node2 = *irmao->node2;
		} else {
			*filho->node1 = *pai->node1;
			*pai->node1 = *irmao->node2;
		}
		irmao->node2preenchido = false;
		// Se o irmao é uma folha, tudo ok, precisamos ver o caso em que não é
		if (filho->dir == nullptr) filho->dir = filho->esq;

		filho->esq = irmao->dir;
		irmao->dir = irmao->meio;
		irmao->meio = nullptr;
	}

	return true;
}

template <typename Chave, typename Item>
void arvore23<Chave, Item>::merge(no_arvore23<Chave, Item> *pai, no_arvore23<Chave, Item> *filho) {
	no_arvore23<Chave, Item> *irmao;

	if (filho == pai->esq) {
		// 1. Se é o filho esquerdo

		if (pai->cheia()) {
			// 1.1 Se o pai é 3-nó
			irmao = pai->meio;
		} else {
			irmao = pai->dir;
		}

		*irmao->node2 = *irmao->node1;
		irmao->node2preenchido = true;
		*irmao->node1 = *pai->node1;
		// Se estamos em folha, terminado, se não, precisamos ajustar ponteiros
		irmao->meio = irmao->esq;
		irmao->esq = (filho->esq == nullptr) ? filho->dir : filho->esq;

		// E finalmente deletamos o filho
		delete filho;
		pai->esq = nullptr;

		// No caso em que o pai é 2-nó, ficamos com a esquerda nula, mas no caso dele
		// ser um 3-nó, precisamos transformá-lo agora em um 2-nó, que é o que ele se
		// tornou
		if (pai->cheia()) {
			pai->node2preenchido = false; // Deixou de ser 3-nó
			// Trazemos o par2 para a primeira posição (pois o par1 desceu)
			*pai->node1 = *pai->node2;
			pai->esq = pai->meio; // esq estava nula, precisamos puxar o meio
			pai->meio = nullptr;  // tornamos o meio nulo
		}
	} else if (pai->cheia() && filho == pai->meio) {
		// 2. Se o filho é do meio
		// Então já sabemos que os dois irmãos são 2-nó, então escolhemos qualquer um e juntamos
		// Escolherei junta com a esquerda
		irmao = pai->esq;
		*irmao->node2 = *pai->node1;
		irmao->node2preenchido = true;
		*pai->node1 = *pai->node2;
		pai->node2preenchido = false;
		// Agora acertamos os pointeiros, para caso não estejamos em uma folha
		irmao->meio = irmao->dir;
		irmao->dir = filho->esq == nullptr ? filho->dir : filho->esq;

		// Finalmente deletamos o filho
		delete filho;
		pai->meio = nullptr;
	} else {
		// 3. Se o filho é da direita
		if (pai->cheia())
			irmao = pai->meio;
		else
			irmao = pai->esq;

		*irmao->node2 = pai->cheia() ? *pai->node2 : *pai->node1;
		irmao->node2preenchido = true;
		// Agora acertamos os ponteiros, para caso não estejamos em uma folha
		irmao->meio = irmao->dir;
		irmao->dir = filho->esq == nullptr ? filho->dir : filho->esq;

		// Finalmente deletamos o filho
		delete filho;
		pai->dir = nullptr;

		// No caso em que o pai é 2-nó, ficamos com a direita nula e esquerda com dois pares, mas no
		// caso dele ser um 3-nó, precisamos transformá-lo agora em um 2-nó, que é o que ele se
		// tornou
		if (pai->cheia()) {
			pai->node2preenchido = false; // não é mais node2
			// Fizemos o merge com o irmão do meio, então colocamos ele na direita
			pai->dir = pai->meio;
			pai->meio = nullptr; // Limpamos o meio
		}
	}
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::achaMaior(no_arvore23<Chave, Item> *raiz) {
	no_arvore23<Chave, Item> *it;
	it = raiz;
	while (it->dir != nullptr) it = it->dir;
	return it;
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::achaMenor(no_arvore23<Chave, Item> *raiz) {
	no_arvore23<Chave, Item> *it;
	it = raiz;
	while (it->esq != nullptr) it = it->esq;
	return it;
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::removeFolha(no_arvore23<Chave, Item> *folha,
                                                             Chave chave) {
	if (folha->node1->chave == chave) *folha->node1 = *folha->node2;
	folha->node2preenchido = false;
	return folha;
}

template <typename Chave, typename Item>
void arvore23<Chave, Item>::remove(Chave chave) {
	bool achou, diminuiu;
	achou = diminuiu = false;
	raiz = removeRecursivo(nullptr, raiz, chave, achou, diminuiu);
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::removeRecursivo(no_arvore23<Chave, Item> *pai,
                                                                 no_arvore23<Chave, Item> *filho,
                                                                 Chave chave, bool &achou,
                                                                 bool &diminuiu) {
	if (filho == nullptr) {
		achou = diminuiu = false;
		return nullptr;
	}

	if (chave < filho->node1->chave) {
		// A chave está para a esquerda
		removeRecursivo(filho, filho->esq, chave, achou, diminuiu);
		if (achou) {
			if (diminuiu) {
				if (pai == nullptr) { // Se o nó nulo chegou na raiz, nos livramos dele
					pai = filho;      // Salvamos o filho, que é o nó nulo
					// Fazemos o filho se tornar o nó não nulo
					filho = filho->esq == nullptr ? filho->dir : filho->esq;
					delete pai;   // Deletamos o nó vazio
					return filho; // Retornamos o filho, que é a nova raiz
				}

				if (!borrow(pai, filho)) {
					diminuiu = !pai->cheia();
					merge(pai, filho);
				} else
					diminuiu = false;
			}
		}
	} else if (chave == filho->node1->chave) {
		achou = true;
		if (filho->ehFolha()) {
			// Se é folha, vemos se está cheia
			if (filho->cheia())
				removeFolha(filho, chave); // Se sim, remover é fácil
			else {
				if (pai == nullptr) {
					// Se é uma folha, mas não possui pais (ou seja, só existe esse par na árvore)
					delete filho; // Só deletamos e retornamos que a árvore ficou vazia
					return nullptr;
				}
				// Se não, precisamos ver se dá para o irmão emprestar
				if (!borrow(pai, filho)) {
					diminuiu = !pai->cheia();
					merge(pai, filho); // Se não, precisamos fazer o merge
				} else
					diminuiu = false;
			}
		} else {
			// Se não é folha, precisamos procura o próximo e anterior inordem
			no_arvore23<Chave, Item> *prox, *ant;
			prox = achaMenor(filho->cheia() ? filho->meio : filho->dir);
			ant = achaMaior(filho->esq);
			// E vemos se algum deles é 3-nó

			if (prox->cheia()) {
				*filho->node1 = *prox->node1;
				removeRecursivo(filho, filho->cheia() ? filho->meio : filho->dir,
				                prox->node1->chave, achou, diminuiu);
			} else if (ant->cheia()) {
				*filho->node1 = *ant->node2;
				removeRecursivo(filho, filho->esq, ant->node2->chave, achou, diminuiu);
			} else {
				*filho->node1 = *ant->node1;
				removeRecursivo(filho, filho->esq, ant->node1->chave, achou, diminuiu);
				if (diminuiu) {
					if (pai == nullptr) { // Se o nó nulo chegou na raiz, nos livramos dele
						pai = filho;      // Salvamos o filho, que é o nó nulo
						// Fazemos o filho se tornar o nó não nulo
						filho = filho->esq == nullptr ? filho->dir : filho->esq;
						delete pai;   // Deletamos o nó vazio
						return filho; // Retornamos o filho, que é a nova raiz
					}

					if (!borrow(pai, filho)) {
						diminuiu = !pai->cheia();
						merge(pai, filho);
					} else
						diminuiu = false;
				}
			}
		}

	} else if (filho->cheia() && chave < filho->node2->chave) {
		// A chave está para o meio
		removeRecursivo(filho, filho->meio, chave, achou, diminuiu);
		if (achou) {
			if (diminuiu) {
				if (pai == nullptr) { // Se o nó nulo chegou na raiz, nos livramos dele
					pai = filho;      // Salvamos o filho, que é o nó nulo
					// Fazemos o filho se tornar o nó não nulo
					filho = filho->esq == nullptr ? filho->dir : filho->esq;
					delete pai;   // Deletamos o nó vazio
					return filho; // Retornamos o filho, que é a nova raiz
				}

				if (!borrow(pai, filho)) {
					diminuiu = !pai->cheia();
					merge(pai, filho);
				} else
					diminuiu = false;
			}
		}
	} else if (filho->cheia() && chave == filho->node2->chave) {
		achou = true;
		if (filho->ehFolha()) {
			// Se é folha, vemos se está cheia
			if (filho->cheia())
				removeFolha(filho, chave); // Se sim, remover é fácil
			else {
				if (pai == nullptr) {
					// Se é uma folha, mas não possui pais (ou seja, só existe esse par na árvore)
					delete filho; // Só deletamos e retornamos que a árvore ficou vazia
					return nullptr;
				}
				// Se não, precisamos ver se dá para o irmão emprestar
				if (!borrow(pai, filho)) {
					diminuiu = !pai->cheia();
					merge(pai, filho); // Se não, precisamos fazer o merge
				} else
					diminuiu = false;
			}
		} else {
			// Se não é folha, precisamos procura o próximo e anterior inordem
			no_arvore23<Chave, Item> *prox, *ant;
			prox = achaMenor(filho->dir);
			ant = achaMaior(filho->cheia() ? filho->meio : filho->esq);
			// E vemos se algum deles é 3-nó

			if (prox->cheia()) {
				*filho->node2 = *prox->node1;
				removeRecursivo(filho, filho->dir, prox->node1->chave, achou, diminuiu);
			} else if (ant->cheia()) {
				*filho->node2 = *ant->node2;
				removeRecursivo(filho, filho->cheia() ? filho->meio : filho->esq, ant->node2->chave,
				                achou, diminuiu);
			} else {
				*filho->node2 = *prox->node1;
				removeRecursivo(filho, filho->dir, prox->node1->chave, achou, diminuiu);
				if (diminuiu) {
					if (pai == nullptr) { // Se o nó nulo chegou na raiz, nos livramos dele
						pai = filho;      // Salvamos o filho, que é o nó nulo
						// Fazemos o filho se tornar o nó não nulo
						filho = filho->esq == nullptr ? filho->dir : filho->esq;
						delete pai;   // Deletamos o nó vazio
						return filho; // Retornamos o filho, que é a nova raiz
					}

					if (!borrow(pai, filho)) {
						diminuiu = !pai->cheia();
						merge(pai, filho);
					} else
						diminuiu = false;
				}
			}
		}
	} else {
		// A chave está para a direita
		removeRecursivo(filho, filho->dir, chave, achou, diminuiu);
		if (achou) {
			if (diminuiu) {
				if (pai == nullptr) { // Se o nó nulo chegou na raiz, nos livramos dele
					pai = filho;      // Salvamos o filho, que é o nó nulo
					// Fazemos o filho se tornar o nó não nulo
					filho = filho->esq == nullptr ? filho->dir : filho->esq;
					delete pai;   // Deletamos o nó vazio
					return filho; // Retornamos o filho, que é a nova raiz
				}

				if (!borrow(pai, filho)) {
					diminuiu = !pai->cheia();
					merge(pai, filho);
				} else
					diminuiu = false;
			}
		}
	}

	return filho;
}

template <typename Chave, typename Item>
int arvore23<Chave, Item>::rank(Chave chave) {
	// Mais ou menos o mesmo algoritmo de uma ABB
	int menores;
	no_arvore23<Chave, Item> *it; // iterador
	it = raiz;                    // o iterador atual
	menores = 0;

	while (it != nullptr) {
		if (chave < it->node1->chave) {
			it = it->esq;
		} else if (chave == it->node1->chave) {
			return menores + numNosEsq(it);
		} else if (it->cheia() && chave < it->node2->chave) {
			menores += (numNosEsq(it) + 1);
			it = it->meio;
		} else if (it->cheia() && chave == it->node2->chave) {
			return menores + numNosEsq(it) + 1 + numNosMeio(it);
		} else {
			menores += (numNosEsq(it) + 1);
			if (it->cheia()) menores += (numNosMeio(it) + 1);
			it = it->dir;
		}
	}

	// Caso a chave não esteja na árvore
	return menores;
}

template <typename Chave, typename Item>
Chave arvore23<Chave, Item>::seleciona(int k) {
	no_arvore23<Chave, Item> *it; // iterador
	it = raiz;                    // o iterador atual

	while (it != nullptr) {
		if (k < numNosEsq(it)) {
			it = it->esq;
		} else if (k == numNosEsq(it)) {
			return it->node1->chave;
		} else if (it->cheia() && k < numNosEsq(it) + 1 + numNosMeio(it)) {
			k -= (numNosEsq(it) + 1);
			it = it->meio;
		} else if (it->cheia() && k == numNosEsq(it) + 1 + numNosMeio(it)) {
			return it->node2->chave;
		} else {
			k -= (numNosEsq(it) + 1);
			if (it->cheia()) k -= (numNosMeio(it) + 1);
			it = it->dir;
		}
	}

	return {};
}

template <typename Chave, typename Item>
void arvore23<Chave, Item>::imprime() {
	std::cout << "Árvore-2-3: [\n";

	imprimeRecursivo(raiz);

	std::cout << "]" << std::endl;
}

template <typename Chave, typename Item>
void arvore23<Chave, Item>::imprimeRecursivo(no_arvore23<Chave, Item> *raiz) {
	if (raiz != nullptr) { // Base da recursão é raiz nula
		// Imprimimos in-ordem
		imprimeRecursivo(raiz->esq);
		std::cout << *raiz->node1 << "\n";
		imprimeRecursivo(raiz->meio);
		if (raiz->cheia()) std::cout << *raiz->node2 << "\n";
		imprimeRecursivo(raiz->dir);

		// raiz->debug();
		// imprimeRecursivo(raiz->esq);
		// imprimeRecursivo(raiz->meio);
		// imprimeRecursivo(raiz->dir);
	}
}

#endif // !_ARVORE23_H