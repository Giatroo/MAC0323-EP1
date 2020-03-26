#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

/* Interface para uma SymbolTable.
 * TODAS NOSSAS ESTRUTURAS DE DADOS VÃO HERDAR DESSA CLASSE
 */
template <typename Chave, typename Item>
class SymbolTable {
	virtual void insere(Chave chave, Item valor) = 0;
	virtual Item devolve(Chave chave) = 0;
	virtual void remove(Chave chave) = 0;
	virtual int rank(Chave chave) = 0;
	virtual Chave seleciona(int k) = 0;
	virtual void imprime() = 0;
};

#endif // !SYMBOL_TABLE_H