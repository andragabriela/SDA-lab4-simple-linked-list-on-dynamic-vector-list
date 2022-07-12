#include "IteratorLP.h"
#include "Lista.h"
#include <exception>

//Complexitate Theta(1)
IteratorLP::IteratorLP(const Lista& l) :lista(l) {
	/* de adaugat */
	indice = l.primOcupat;
}

//Complexitate Theta(1)
void IteratorLP::prim() {
	/* de adaugat */
	indice = lista.primOcupat;
}

//Complexitate Theta(1)
void IteratorLP::urmator() {
	/* de adaugat */
	if (!valid()) throw std::exception();
	indice = lista.urm[indice];
}

//Complexitate Theta(1)
bool IteratorLP::valid() const {
	/* de adaugat */
	return indice >= 1 && indice <= lista.capacitate;
}

//Complexitate Theta(1)
TElem IteratorLP::element() const {
	/* de adaugat */
	if (!valid()) throw std::exception();
	return lista.elements[indice];
}


