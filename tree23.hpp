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
	int numNosEsq;                  // Números de nós na subárvore esquerda
	int numNosMeio;                 // Número de nós na subárvore do meio
	int numNosDir;                  // Número de nós na subárvore direita
	bool node2preenchido;           // Indica se o nó 2 está preenchido ou não

	no_arvore23();
	no_arvore23(Par<Chave, Item>);
	no_arvore23(Par<Chave, Item>, Par<Chave, Item>);
	~no_arvore23();

	// Funções auxiliares
	bool ehFolha();                // Retorna se todos os ponteiros são nulos
	bool cheia();                  // Retorna se node1 e node2 estão preenchidos
	void insere(Par<Chave, Item>); // Insere um novo par no nó
	void insere(no_arvore23<Chave, Item> *); // Insere uma árvore nesse nó
	                                         // essa árvore deve ser filha
	                                         // do nó e ele deve ter apenas um par
};

template <typename Chave = MyString, typename Item = int>
class arvore23 : public SymbolTable<Chave, Item> {
  public:
	no_arvore23<Chave, Item> *raiz;

	// Função auxiliar do destrutor
	void deleteArvore(no_arvore23<Chave, Item> *);

	// Função auxiliar do imprime
	void imprimeRecursivo(no_arvore23<Chave, Item> *);

	// Função auxiliar do insere
	no_arvore23<Chave, Item> *insereRecursivo(no_arvore23<Chave, Item> *, Chave,
	                                          Item, bool &, bool &);

	// Insere um novo par em um nó que já tinha dois pares.
	// Cria três nós cada um com um par cada onde o nó de chave intermediária
	// é retonado como um ponteiro, o de menor chave em sua esquerda e o de maior
	// chave em sua direita
	no_arvore23<Chave, Item> *split(no_arvore23<Chave, Item> *, Par<Chave, Item>);

	// Insere uma nova subárvore em um nó que já tinha dois pares
	// Cria três nós de forma que o de chave intermediária é retornada
	no_arvore23<Chave, Item> *split(no_arvore23<Chave, Item> *,
	                                no_arvore23<Chave, Item> *);

	// Dados dois nós a e b, onde b é filho de a e b foi splitado, queremos inserir
	// a raiz de b após o split em a. Caso a não precise ser splitado, o retorno
	// será um ponteiro para a, caso contrário, o retorno era um ponteiro para a raiz
	// da nova subárvore (após o split de a)
	no_arvore23<Chave, Item> *join(no_arvore23<Chave, Item> *a,
	                               no_arvore23<Chave, Item> *b);

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
      numNosEsq(0),
      numNosMeio(0),
      numNosDir(0),
      node2preenchido(false) {}

template <typename Chave, typename Item>
no_arvore23<Chave, Item>::no_arvore23(Par<Chave, Item> p)
    : node2(new Par<Chave, Item>),
      esq(nullptr),
      meio(nullptr),
      dir(nullptr),
      numNosEsq(0),
      numNosMeio(0),
      numNosDir(0),
      node2preenchido(false) {
	node1 = new Par<Chave, Item>;
	*node1 = p;
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item>::no_arvore23(Par<Chave, Item> p1, Par<Chave, Item> p2)
    : esq(nullptr),
      meio(nullptr),
      dir(nullptr),
      numNosEsq(0),
      numNosMeio(0),
      numNosDir(0),
      node2preenchido(true) {
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
	numNosEsq = numNosMeio = numNosDir = 0;
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
		this->numNosMeio = p->numNosEsq;
		this->dir = p->dir;
		this->numNosDir = p->numNosDir;
	} else { // filhos da esquerda
		*this->node2 = *this->node1;
		*this->node1 = *p->node1;
		this->esq = p->esq;
		this->numNosEsq = p->numNosEsq;
		this->meio = p->dir;
		this->numNosMeio = p->numNosDir;
	}
	this->node2preenchido = true;
	delete p;
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
no_arvore23<Chave, Item> *arvore23<Chave, Item>::split(
    no_arvore23<Chave, Item> *node, Par<Chave, Item> p) {
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
	meio->numNosEsq = meio->numNosDir = 1;
	delete node; // Não usaremos para mais nada aquele nó antigo
	return meio;
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::split(
    no_arvore23<Chave, Item> *pai, no_arvore23<Chave, Item> *filho) {
	no_arvore23<Chave, Item> *menor, *meior, *maior; // meior pq sim
	// Precisamos descobrir se o filho é da esquerda, meio ou direita

	if (pai->esq == filho) {
		// filho é a esquerda
		// logo, filho->node1->chave < pai->node1->chave < pai->node2->chave
		menor = filho;
		meior = new no_arvore23<Chave, Item>(*pai->node1);
		maior = new no_arvore23<Chave, Item>(*pai->node2);

		maior->esq = pai->meio;
		maior->numNosEsq = pai->numNosMeio;
		maior->dir = pai->dir;
		maior->numNosDir = pai->numNosDir;
		// o menor é o filho, manterá suas subárvores
	} else if (pai->meio == filho) {
		// filho é o meio
		// logo, pai->node1->chave < filho->node1->chave < pai->node2->chave
		menor = new no_arvore23<Chave, Item>(*pai->node1);
		meior = filho;
		maior = new no_arvore23<Chave, Item>(*pai->node2);

		menor->esq = pai->esq;
		menor->numNosEsq = pai->numNosEsq;
		menor->dir = filho->esq;
		menor->numNosDir = filho->numNosEsq;
		maior->esq = filho->dir;
		maior->numNosEsq = filho->numNosDir;
		maior->dir = pai->dir;
		maior->numNosDir = pai->numNosDir;
		// o meio é o filho, já salvamos suas subárvores
	} else {
		// filho é a direita
		// logo, pai->node1->chave < pai->node2->chave < filho->node1->chave
		menor = new no_arvore23<Chave, Item>(*pai->node1);
		meior = new no_arvore23<Chave, Item>(*pai->node2);
		maior = filho;

		menor->esq = pai->esq;
		menor->numNosEsq = pai->numNosEsq;
		menor->dir = pai->meio;
		menor->numNosDir = pai->numNosMeio;
		// o maior é o filho, materá suas subárvores
	}

	// o meio é a raiz, a sua esquerda e direita sempre serão menor e maior
	meior->esq = menor;
	meior->numNosEsq = menor->numNosEsq + menor->numNosDir + 1;
	meior->dir = maior;
	meior->numNosDir = maior->numNosEsq + maior->numNosDir + 1;

	pai->esq = pai->meio = pai->dir = nullptr;
	delete pai;   // O antigo nó do pai (que tinha dois elementos) agora não existe
	              // mais (foi splitado)
	pai = meior;  // Faremos o ponteiro apontar para o meior (nova raiz) apenas para
	              // evitar erros (de acesso a um pointeiro que sofreu delete)
	return meior; // Retornamos a nova raiz
}

template <typename Chave, typename Item>
no_arvore23<Chave, Item> *arvore23<Chave, Item>::join(
    no_arvore23<Chave, Item> *pai, no_arvore23<Chave, Item> *filho) {
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
no_arvore23<Chave, Item> *arvore23<Chave, Item>::insereRecursivo(
    no_arvore23<Chave, Item> *raiz, Chave chave, Item valor, bool &achou,
    bool &cresceu) {
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
			if (!achou) raiz->numNosEsq++;

			// 3.1.2.3 Precisamos agora verificar se a subárvore esquerda cresceu
			if (cresceu)
				raiz->insere(raiz->esq); // Inserimos a subárvore esquerda nesse nó
		} else {
			// 3.1.3.1 Precisamos inserir na subárvore direita
			raiz->dir = insereRecursivo(raiz->dir, chave, valor, achou, cresceu);

			// 3.1.3.2 Se a chave foi inserida, aumentamos o número de caras na
			// direita
			if (!achou) raiz->numNosDir++;

			// 3.1.3.3 Precisamos agora verificar se a subárvore direita cresceu
			if (cresceu)
				raiz->insere(raiz->dir); // Inserimos a subárvore direita nesse nó
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
			if (!achou) raiz->numNosEsq++;

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
			if (!achou) raiz->numNosMeio++;

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
			if (!achou) raiz->numNosDir++;

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
void arvore23<Chave, Item>::remove(Chave chave) {}

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
			return menores + it->numNosEsq;
		} else if (it->cheia() && chave < it->node2->chave) {
			menores += (it->numNosEsq + 1);
			it = it->meio;
		} else if (it->cheia() && chave == it->node2->chave) {
			return menores + it->numNosEsq + 1 + it->numNosMeio;
		} else {
			menores += (it->numNosEsq + 1);
			if (it->cheia()) menores += (it->numNosMeio + 1);
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
		if (k < it->numNosEsq) {
			it = it->esq;
		} else if (k == it->numNosEsq) {
			return it->node1->chave;
		} else if (it->cheia() && k < it->numNosEsq + 1 + it->numNosMeio) {
			k -= (it->numNosEsq + 1);
			it = it->meio;
		} else if (it->cheia() && k == it->numNosEsq + 1 + it->numNosMeio) {
			return it->node2->chave;
		} else {
			k -= (it->numNosEsq + 1);
			if (it->cheia()) k -= (it->numNosMeio + 1);
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

		// std::cout << "[ " << *raiz->node1 << " | ";
		// if (raiz->cheia())
		// 	std::cout << *raiz->node2;
		// else
		// 	std::cout << " vazio ";
		// std::cout << " ]\t com filhos:\n";

		// std::cout << "\tEsq:  ";
		// if (raiz->esq) {
		// 	std::cout << "[ " << *raiz->esq->node1 << " | ";
		// 	if (raiz->esq->cheia())
		// 		std::cout << *raiz->esq->node2;
		// 	else
		// 		std::cout << " vazio ";
		// 	std::cout << " ]\n";
		// } else {
		// 	std::cout << "null\n";
		// }

		// std::cout << "\tMeio: ";
		// if (raiz->meio) {
		// 	std::cout << "[ " << *raiz->meio->node1 << " | ";
		// 	if (raiz->meio->cheia())
		// 		std::cout << *raiz->meio->node2;
		// 	else
		// 		std::cout << " vazio ";
		// 	std::cout << " ]\n";
		// } else {
		// 	std::cout << "null\n";
		// }

		// std::cout << "\tDir:  ";
		// if (raiz->dir) {
		// 	std::cout << "[ " << *raiz->dir->node1 << " | ";
		// 	if (raiz->dir->cheia())
		// 		std::cout << *raiz->dir->node2;
		// 	else
		// 		std::cout << " vazio ";
		// 	std::cout << " ]\n";
		// } else {
		// 	std::cout << "null\n";
		// }
		// std::cout << "\tValores de nós em subárvores: " << raiz->numNosEsq << " "
		//           << raiz->numNosMeio << " " << raiz->numNosDir << "\n";

		// imprimeRecursivo(raiz->esq);
		// imprimeRecursivo(raiz->meio);
		// imprimeRecursivo(raiz->dir);
	}
}

#endif // !_ARVORE23_H