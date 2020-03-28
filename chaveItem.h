/* Um header com a estrutura Par, que possui uma chave e um item */

#ifndef _CHAVE_ITEM_H
#define _CHAVE_ITEM_H

#include "myString.h"

template <typename Chave = MyString, typename Item = int>
class Par {
  public:
	Chave chave;
	Item valor;

	void chavesIguais(const Par<Chave, Item> &p);

	void operator=(const Par<Chave, Item> &p);

	friend std::ostream &operator<<(std::ostream &out, const Par<Chave, Item> &p) {
		out << "( " << p.chave << ", " << p.valor << " )";
		return out;
	}
};

template <typename Chave, typename Item>
void Par<Chave, Item>::chavesIguais(const Par<Chave, Item> &p) {
	this->valor++;
}

template <typename Chave, typename Item>
void Par<Chave, Item>::operator=(const Par<Chave, Item> &p) {
	this->chave = p.chave;
	this->valor = p.valor;
}

#endif // !_CHAVE_ITEM_H
