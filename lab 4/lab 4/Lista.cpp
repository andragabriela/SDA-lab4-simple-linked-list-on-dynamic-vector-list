
#include <exception>

#include "IteratorLP.h"
#include "Lista.h"
#include<cassert>
#include <iostream>

//Complexitate Theta(1)
//initializare de spatiu liber facem lista goala pe prima linie
void Lista::initSpatiuLiber(int capacitate) {
	for (int i = 1; i < capacitate; i++)
	{
		urm[i] = i + 1;
	}
	urm[capacitate] = 0;
	primLiber = 1;
}

//Complexitate Theta(1)
void Lista::aloca(int& i) {//aloc spatiu pt a stoca un nou element
	i = primLiber;
	primLiber = urm[primLiber];
}

//Complexitate Theta(1)
void Lista::dealoca(int i) {//dealoc spatiul ocupat de pozitia i pt a putea fi folosit la urm inserare
	urm[i] = primLiber;
	primLiber = i;
}

//Complexitate Theta(n)
int Lista::creeazaNod(TElem e) {
	if (primLiber == 0) {
		//realocare
		TElem* newelements = new TElem[capacitate * 2 + 1];
		int* newurmator = new int[capacitate * 2 + 1];
		for (int i = 1; i <= capacitate; i++) {
			newelements[i] = elements[i];
			newurmator[i] = urm[i];
		}
		delete[] urm;
		delete[] elements;

		urm = newurmator;
		elements = newelements;
		//reinitializare spatiu liber
		primLiber = capacitate + 1;
		for (int i = primLiber; i < capacitate * 2; i++)
			urm[i] = i + 1;
		urm[2 * capacitate] = 0;
		capacitate *= 2;
	}
	int i;
	aloca(i);
	elements[i] = e;
	urm[i] = 0;
	return i;
}

//complexitate Theta(n) (n-capacitatea)
Lista::Lista() {
	/* de adaugat */
	capacitate = 10;
	dimensiune = 0;
	elements = new TElem[capacitate + 1];
	urm = new TElem[capacitate + 1];
	initSpatiuLiber(capacitate);
	primOcupat = 0;
	ultimOcupat = 0;
}

//Complexitate Theta(1)
int Lista::dim() const {
	/* de adaugat */
	return dimensiune;
}

//Complexitate Theta(1)
bool Lista::vida() const {
	/* de adaugat */
	return primOcupat == 0;
}

//Complexitate Theta(1)
IteratorLP Lista::prim() const {
	/* de adaugat */
	return IteratorLP(*this);
}

//Complexitate Theta(1)
TElem Lista::element(IteratorLP poz) const {
	/* de adaugat */
	return poz.element();
}

//Complexitate Theta(1)-best case, Theta(n)-worst case.Overall: O(n)
TElem Lista::sterge(IteratorLP& poz) {// sterge element de pe o pozitie poz si returneaza elementul sters
	/* de adaugat */
	if (!poz.valid())
		throw std::exception();
	TElem elem = elements[poz.indice];
	if (poz.indice == primOcupat)// sterg primul
		primOcupat = urm[poz.indice];
	else {
		int q = primOcupat;
		while (urm[q] != poz.indice) // iau primul dinaintea celui dat
			q = urm[q];
		urm[q] = urm[poz.indice];
	}
	dimensiune--;
	dealoca(poz.indice);
	poz.urmator();
	return elem;
}

//Complexitate Theta(1)-best case cand e pe prima pozitie, Theta(n)-worst case. Overall: O(n)
IteratorLP Lista::cauta(TElem e) const {
	/* de adaugat */
	IteratorLP it(*this);
	it.prim();
	while (it.valid() && it.element() != e)
		it.urmator();
	return it;
}

//Complexitate Theta(1)
TElem Lista::modifica(IteratorLP poz, TElem e) {
	/* de adaugat */
	if (!poz.valid()) throw std::exception();
	int oldelem = poz.element();
	elements[poz.indice] = e;
	return oldelem;
}

//Complexitate Theta(n)- fac redimensionare
void Lista::adauga(IteratorLP& poz, TElem e) {
	/* de adaugat */
	if (!poz.valid()) throw std::exception();
	int nouIndice = creeazaNod(elements[poz.indice]);
	int oldurm = urm[poz.indice];//salvez ultimul indice ca sa-l pot suprascrie
	elements[poz.indice] = e;
	urm[poz.indice] = nouIndice;
	urm[nouIndice] = oldurm;
	dimensiune++;
}

//Complexitate Theta(n)- fac redimensionare
void Lista::adaugaInceput(TElem e) {
	/* de adaugat */
	int nouIndice = creeazaNod(e);
	urm[nouIndice] = primOcupat;
	primOcupat = nouIndice;
	if (ultimOcupat == 0) ultimOcupat = nouIndice;//cand avem un elem prima pozitie coresp cu ultima
	dimensiune++;
}

//Complexitate Theta(n)- fac redimensionare
void Lista::adaugaSfarsit(TElem e) {
	/* de adaugat */
	int nouIndice = creeazaNod(e);
	urm[ultimOcupat] = nouIndice;
	ultimOcupat = nouIndice;
	if (primOcupat == 0) {
		primOcupat = nouIndice;//cand avem un elem prima pozitie coresp cu ultima
	}
	dimensiune++;
}

//complexitate theta (n) -n dimensiunea
int* Lista::eliminaDinKInK(int k) {
	if (k <= 0) throw std::exception();
	int nr = 0;
	for (int i = 1; i <= dimensiune; i++)
	{
		if (nr == k) {
			for (int j = nr; j < dimensiune; j++)
			{
				elements[j] = elements[j + 1];

			}
			dimensiune--;
			nr = 0;
		}
		else nr++;
	}
	return elements;
}

//Complexitate Theta(1)
Lista::~Lista() {
	/* de adaugat */
	delete[] urm;
	delete[] elements;
}
