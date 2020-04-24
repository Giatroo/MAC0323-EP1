/* Implementação de uma tabela de símbolos via árvores binárias de busca balanceadas usando a
 * técnica de árvore rubro-negras.
 */

#ifndef _REDBLACK_H
#define _REDBLACK_H

#include <iostream>

#include "chaveItem.hpp"
#include "symbolTable.hpp"

using namespace std;

// DECLARAÇÃO DAS CLASSES

template <typename Chave = MyString, typename Item = int>
class no_rb {
  public:
	Par<Chave, Item> *node;  // O nó em si
	no_rb<Chave, Item> *esq; // Filho esquerdo
	no_rb<Chave, Item> *dir; // Filho direito
	no_rb<Chave, Item> *pai; // O pai
	int numNosEsq;           // Números de nós na subárvore esquerda
	int numNosDir;           // Número de nós na subárvore direita
	bool red;                // Indica se é vermelha ou não

	no_rb();
	no_rb(Par<Chave, Item>);
	~no_rb();
	void debug();
};

template <typename Chave = MyString, typename Item = int>
class rb_tree : public SymbolTable<Chave, Item> {
  private:
	no_rb<Chave, Item> *raiz;

	// Função auxiliar do destrutor
	void deleteArvore(no_rb<Chave, Item> *);

	// Função auxiliar do imprime
	void imprimeRecursivo(no_rb<Chave, Item> *);

	// Função auxiliar do remove
	void removeRecursivo(no_rb<Chave, Item> *, Chave, bool &);

	// Funções de rotação (é passado o pai como parâmetro)
	no_rb<Chave, Item> *rotEsq(no_rb<Chave, Item> *);
	no_rb<Chave, Item> *rotDir(no_rb<Chave, Item> *);

	// Função que dado um nó vermelho que tem pai vermelho, faz as correções necessárias
	void corrigeInsere(no_rb<Chave, Item> *);

	// Função que acha o menor elemento da árvore dada
	no_rb<Chave, Item> *achaMin(no_rb<Chave, Item> *);
	no_rb<Chave, Item> *achaMax(no_rb<Chave, Item> *);

	// Função que dado um nó duplo preto e seu pai, faz as correções necessárias
	// (Precisamos passar o pai para caso o duplo preto seja nulo)
	void corrigeRemove(no_rb<Chave, Item> *, no_rb<Chave, Item> *);

  public:
	rb_tree();
	~rb_tree();
	void insere(Chave chave, Item valor);
	Item devolve(Chave chave);
	void remove(Chave chave);
	int rank(Chave chave);
	Chave seleciona(int k);
	void imprime();
};

// IMPLEMENTAÇÃO NO_RB

template <typename Chave, typename Item>
no_rb<Chave, Item>::no_rb()
    : node(new Par<Chave, Item>),
      esq(nullptr),
      dir(nullptr),
      pai(nullptr),
      numNosEsq(0),
      numNosDir(0),
      red(true) {}

template <typename Chave, typename Item>
no_rb<Chave, Item>::no_rb(Par<Chave, Item> p)
    : esq(nullptr), dir(nullptr), pai(nullptr), numNosEsq(0), numNosDir(0), red(true) {
	node = new Par<Chave, Item>();
	*node = p;
}

template <typename Chave, typename Item>
no_rb<Chave, Item>::~no_rb() {
	delete node;
	esq = dir = pai = nullptr;
	red = false;
	numNosEsq = numNosDir = 0;
}

template <typename Chave, typename Item>
void no_rb<Chave, Item>::debug() {
	std::cout << *this->node << " Vermelha = " << this->red << "\t com:\n";

	std::cout << "\tEsq:  ";
	if (this->esq)
		std::cout << *this->esq->node << " Vermelha = " << this->esq->red << std::endl;
	else
		std::cout << "null\n";

	std::cout << "\tDir:  ";
	if (this->dir)
		std::cout << *this->dir->node << " Vermelha = " << this->dir->red << std::endl;
	else
		std::cout << "null\n";

	std::cout << "\tPai: ";
	if (this->pai)
		std::cout << *this->pai->node << " Vermelha = " << this->pai->red << std::endl;
	else
		std::cout << "null\n";
	std::cout << "\tCom " << this->numNosEsq << " na esquerda e " << this->numNosDir
	          << " na direita" << std::endl;
}

// IMPLEMENTAÇÃO RB_TREE

template <typename Chave, typename Item>
rb_tree<Chave, Item>::rb_tree() : raiz(nullptr) {}

template <typename Chave, typename Item>
rb_tree<Chave, Item>::~rb_tree() {
	deleteArvore(raiz);
}

template <typename Chave, typename Item>
void rb_tree<Chave, Item>::deleteArvore(no_rb<Chave, Item> *raiz) {
	if (raiz != nullptr) { // Base da recursão é raiz nula

		// Deletamos as subarvores e dps deletamos a raiz
		deleteArvore(raiz->esq);
		deleteArvore(raiz->dir);
		delete raiz;
	}
}

template <typename Chave, typename Item>
no_rb<Chave, Item> *rb_tree<Chave, Item>::rotEsq(no_rb<Chave, Item> *raiz) {
	if (raiz == nullptr || raiz->esq == nullptr) return raiz;

	no_rb<Chave, Item> *temp = raiz->esq;
	raiz->esq = temp->dir;
	raiz->numNosEsq = temp->numNosDir;
	temp->dir = raiz;
	temp->numNosDir = raiz->numNosEsq + raiz->numNosDir + 1;
	temp->pai = raiz->pai;
	if (raiz->esq) raiz->esq->pai = raiz;
	raiz->pai = temp;
	raiz = temp;
	return raiz;
}

template <typename Chave, typename Item>
no_rb<Chave, Item> *rb_tree<Chave, Item>::rotDir(no_rb<Chave, Item> *raiz) {
	if (raiz == nullptr || raiz->dir == nullptr) return raiz;

	no_rb<Chave, Item> *temp = raiz->dir;
	raiz->dir = temp->esq;
	raiz->numNosDir = temp->numNosEsq;
	temp->esq = raiz;
	temp->numNosEsq = raiz->numNosEsq + raiz->numNosDir + 1;
	temp->pai = raiz->pai;
	if (raiz->dir) raiz->dir->pai = raiz;
	raiz->pai = temp;
	raiz = temp;
	return raiz;
}

template <typename Chave, typename Item>
void rb_tree<Chave, Item>::corrigeInsere(no_rb<Chave, Item> *filho) {
	no_rb<Chave, Item> *pai, *tio, *avo;
	pai = filho->pai;

	if (pai == nullptr) { // Se o filho é raiz
		this->raiz = filho;
		filho->red = false;
		return;
	}
	if (!pai->red) return; // Se o pai não é preto, não tem o que corrigir

	avo = pai->pai;
	if (avo == nullptr) { // Se o pai é raiz
		this->raiz = pai;
		pai->red = false; // Se era preto, continua preto
		return;
	}
	tio = avo->esq == pai ? avo->dir : avo->esq;

	// Separamos no caso em que o tio é vermelho ou preto/nulo
	if (tio == nullptr || !tio->red) {
		no_rb<Chave, Item> *aux;

		// O tio é preto ou nulo
		// Se o filho, pai e avô formam um triângulo, rotacionamos para formarem uma reta
		if (avo->dir == pai && pai->esq == filho) {
			// std::cout << "Rotacionando esq" << std::endl;
			avo->dir = rotEsq(pai);
			pai = avo->dir;
			filho = pai->dir;
		} else if (avo->esq == pai && pai->dir == filho) {
			// std::cout << "Rotacionando dir" << std::endl;
			avo->esq = rotDir(pai);
			pai = avo->esq;
			filho = pai->esq;
		}

		// std::cout << "Meio" << std::endl;

		// Agora caímos no caso que é uma reta.
		// Rotacionamos e trocamos a cor entre o antigo avô e o antigo pai
		aux = avo->pai;
		bool esq = (aux != nullptr && aux->esq == avo);
		if (avo->dir == pai && pai->dir == filho) {
			// std::cout << "Rotacionando dir" << std::endl;
			pai = rotDir(avo);
			avo = pai->esq;
		} else {
			// std::cout << "Rotacionando esq" << std::endl;
			pai = rotEsq(avo);
			avo = pai->dir;
		}
		pai->red ^= 1;
		avo->red ^= 1;
		if (aux == nullptr) {
			pai->red = false;
			this->raiz = pai;
		} else {
			if (esq)
				aux->esq = pai;
			else
				aux->dir = pai;
		}
		pai->pai = aux;

	} else {
		// O tio é vermelho (e não-nulo consequentemente)
		pai->red ^= 1;
		tio->red ^= 1;
		avo->red ^= 1;
		// Agora pai e tio são pretos e avo é vermelho
		// Então precisamos continuar verificando se houve conflitos entre o avô e o bisavô
		corrigeInsere(avo);
	}
}

template <typename Chave, typename Item>
void rb_tree<Chave, Item>::insere(Chave chave, Item valor) {
	// Caso excepcional: raiz ser nula
	if (raiz == nullptr) {
		raiz = new no_rb<Chave, Item>((Par<Chave, Item>){ chave, valor });
		raiz->red = false; // Pintamos a raiz de preto
		return;
	}

	// Caso geral: raiz não é nula
	// Vamos até onde devemos inserir
	no_rb<Chave, Item> *it, *ant; // iteradores
	ant = nullptr;                // o anterior
	it = raiz;                    // o iterador atual

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
	it = new no_rb<Chave, Item>((Par<Chave, Item>){ chave, valor });
	it->pai = ant; // Atualizamos só o pai e deixamos esq e dir como null
	// E atualizamos o ponteiro do anterior
	if (chave < ant->node->chave)
		ant->esq = it;
	else
		ant->dir = it;

	// Agora precisamos ver se as propriedades da árvore foram violadas
	corrigeInsere(it);

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
Item rb_tree<Chave, Item>::devolve(Chave chave) {
	no_rb<Chave, Item> *it; // iterador

	it = raiz;
	while (it != nullptr && it->node->chave != chave)
		it = (chave < it->node->chave) ? it->esq : it->dir;

	// Se chegamos aqui, ou it é nulo ou achamos it
	if (it != nullptr) return it->node->valor;
	// Retornamos apenas se não for nulo

	return {};
}

template <typename Chave, typename Item>
void rb_tree<Chave, Item>::remove(Chave chave) {
	bool achou = false;
	removeRecursivo(raiz, chave, achou);
}

template <typename Chave, typename Item>
void rb_tree<Chave, Item>::removeRecursivo(no_rb<Chave, Item> *it, Chave chave, bool &achou) {
	// Se é nulo
	if (it == nullptr) {
		// Chegamos aqui ou se a raiz era nula ou se descemos nossa árvore e ela não
		// possuia essa chave
		achou = false;
		return;
	}

	if (chave < it->node->chave) {
		// Se queremos remover alguém que está à esquerda
		removeRecursivo(it->esq, chave, achou);
		if (it->esq != nullptr) it->esq->pai = it;
		if (achou) it->numNosEsq--;
	} else if (chave > it->node->chave) {
		// Se queremos remover alguém que está à direita
		removeRecursivo(it->dir, chave, achou);
		if (it->dir != nullptr) it->dir->pai = it;
		if (achou) it->numNosDir--;
	} else {
		// Se achamos quem estamos tentando remover
		achou = true;

		// Caso 1: é uma folha
		if (it->esq == nullptr && it->dir == nullptr) {
			no_rb<Chave, Item> *pai = it->pai;
			bool red = it->red;

			if (pai == nullptr)
				raiz = nullptr;
			else if (pai->esq == it)
				pai->esq = nullptr;
			else
				pai->dir = nullptr;

			delete it;

			if (!red) corrigeRemove(nullptr, pai);
		}
		// Caso 2: é nó interno
		else {
			// Procuramos a menor chave na subárvore direita
			// (o próximo inordem)
			no_rb<Chave, Item> *mini = achaMin(it->dir);
			no_rb<Chave, Item> *maxi = achaMax(it->esq);
			no_rb<Chave, Item> *temp = (mini == nullptr ? maxi : mini);
			bool esq = (mini == nullptr);
			// Sabemos que ele existe, pois it tem dois filhos

			// Colocamos o próximo inordem no lugar no do que queríamos remover
			*it->node = *temp->node;
			if (esq)
				it->numNosEsq--;
			else
				it->numNosDir--;

			// E agora o nosso problema é remover o nó do próximo inordem
			// Torcemos para que a remoção se reduza a ou o caso 1 ou o caso 2
			// mas se novamente cairmos no caso 3, vamos novamente ter que fazer
			// o processo de substituir um nó pelo próximo inordem e chamar
			// recursivamente a função de remover
			removeRecursivo((esq ? it->esq : it->dir), temp->node->chave, achou);
			// (nesse caso, 'achou' é indiferente, pois, como já falei, temos certeza
			// de que essa chave existe na nossa árvore)
			// (ou seja, 'achou' continua como true)
		}
	}
}

template <typename Chave, typename Item>
void rb_tree<Chave, Item>::corrigeRemove(no_rb<Chave, Item> *dp, no_rb<Chave, Item> *pai) {
	// Irmão é o outro filho do pai, x é o filho do irmão mais próximo do duplo preto e y é o outro
	// Dessa forma, tratamos casos simétricos da mesma forma
	no_rb<Chave, Item> *irmao, *x, *y, *avo;
	bool esqPai; // Diz se dp está à esquerda do pai (para sabermos qual o caso simétrico estamos)
	bool esqAvo; // Diz se o pai está à esquerda do avô
	if (dp != nullptr) pai = dp->pai;

	// 1) dp = raiz
	if (pai == nullptr || dp == this->raiz) return; // Está resolvido

	esqPai = dp == pai->esq;
	irmao = esqPai ? pai->dir : pai->esq;
	x = esqPai ? irmao->esq : irmao->dir;
	y = esqPai ? irmao->dir : irmao->esq;
	avo = pai->pai;
	esqAvo = (avo != nullptr && avo->esq == pai);

	// Agora vamos dividir em cinco casos:

	// 2) irmão vermelho, resto preto
	if (!pai->red && irmao->red && (x == nullptr || !x->red) && (y == nullptr || !y->red)) {
		pai->red ^= 1;
		irmao->red ^= 1;
		if (esqPai)
			rotDir(pai);
		else
			rotEsq(pai);
		if (avo == nullptr) {
			this->raiz = irmao;
			irmao->red = 0;
		} else {
			if (esqAvo) {
				avo->esq = irmao;
				avo->numNosEsq = irmao->numNosEsq + irmao->numNosDir + 1;
			} else {
				avo->dir = irmao;
				avo->numNosDir = irmao->numNosEsq + irmao->numNosDir + 1;
			}
		}
		corrigeRemove(dp, pai);
	}
	// 3) todos pretos
	else if (!pai->red && !irmao->red && (x == nullptr || !x->red) && (y == nullptr || !y->red)) {
		irmao->red ^= 1;
		corrigeRemove(pai, pai->pai);
	}
	// 4) pai vermelho, resto preto
	else if (pai->red && !irmao->red && (x == nullptr || !x->red) && (y == nullptr || !y->red)) {
		pai->red ^= 1;
		irmao->red ^= 1;
	}
	// 5) irmao preto, x vermelho, y preto e pai qualquer cor
	else if (!irmao->red && (x != nullptr && x->red) && (y == nullptr || !y->red)) {
		irmao->red ^= 1;
		x->red ^= 1;
		if (esqPai) {
			pai->dir = rotEsq(irmao);
			if (pai->dir == nullptr)
				pai->numNosDir = 0;
			else
				pai->numNosDir = pai->dir->numNosEsq + pai->dir->numNosEsq + 1;

		} else {
			pai->esq = rotDir(irmao);
			if (pai->esq == nullptr)
				pai->numNosEsq = 0;
			else
				pai->numNosEsq = pai->esq->numNosEsq + pai->esq->numNosEsq + 1;
		}
		corrigeRemove(dp, pai); // Vamos cair no caso 6
	}
	// 6) irmao preto, y vermelho, resto qualquer cor
	else if (!irmao->red && (y != nullptr && y->red)) {
		irmao->red = pai->red;
		y->red ^= 1;
		pai->red = 0;
		if (esqPai)
			rotDir(pai);
		else
			rotEsq(pai);

		if (avo == nullptr) {
			this->raiz = irmao;
			irmao->red = 0;
		} else {
			if (esqAvo) {
				avo->esq = irmao;
				avo->numNosEsq = irmao->numNosEsq + irmao->numNosDir + 1;
			} else {
				avo->dir = irmao;
				avo->numNosDir = irmao->numNosEsq + irmao->numNosDir + 1;
			}
		}
	}
}

template <typename Chave, typename Item>
no_rb<Chave, Item> *rb_tree<Chave, Item>::achaMin(no_rb<Chave, Item> *it) {
	// Para achar o menor elemento de uma árvore, basta ir para a esquerda o máximo
	// posível

	while (it != nullptr && it->esq != nullptr) it = it->esq;
	return it; // Ao final, temos o menor elemento da árvore
}

template <typename Chave, typename Item>
no_rb<Chave, Item> *rb_tree<Chave, Item>::achaMax(no_rb<Chave, Item> *it) {
	// Para achar o menor elemento de uma árvore, basta ir para a esquerda o máximo
	// posível

	while (it != nullptr && it->dir != nullptr) it = it->dir;
	return it; // Ao final, temos o menor elemento da árvore
}

template <typename Chave, typename Item>
int rb_tree<Chave, Item>::rank(Chave chave) {
	int menores;
	no_rb<Chave, Item> *it; // iterador
	it = raiz;              // o iterador atual
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
Chave rb_tree<Chave, Item>::seleciona(int k) {
	no_rb<Chave, Item> *it; // iterador
	it = raiz;              // o iterador atual
	int rank;               // o rank do nó atual

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
void rb_tree<Chave, Item>::imprime() {
	std::cout << "Árvore Rubro-Negra: [\n";

	imprimeRecursivo(raiz);

	std::cout << "]" << std::endl;
}

template <typename Chave, typename Item>
void rb_tree<Chave, Item>::imprimeRecursivo(no_rb<Chave, Item> *raiz) {
	if (raiz != nullptr) { // Base da recursão é raiz nula

		// Imprimimos in-ordem
		imprimeRecursivo(raiz->esq);
		// raiz->debug();
		std::cout << *raiz->node << " Vermelha = " << raiz->red << std::endl;
		imprimeRecursivo(raiz->dir);
	}
}

#endif // !_REDBLACK_H
