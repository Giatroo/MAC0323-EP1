/* Um header com a estrutura Par, que possui uma chave e um item */

#ifndef CHAVE_ITEM_H
#define CHAVE_ITEM_H

template <typename C, typename I>
class Par {
  public:
	C chave; // Chave do tipo C
	I valor; // Item do tipo I
};

#endif // !CHAVE_ITEM_H
