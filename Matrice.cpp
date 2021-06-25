#include "Matrice.h"

#include <exception>

using namespace std;


//constructor
//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
Matrice::Matrice(int m, int n) {
    //Complexitate: 0(1)

    if (m <= 0 || n <= 0)
        throw exception();

    nrL = m;
    nrC = n;

    radacina = nullptr;
}


int Matrice::nrLinii() const {
    //Complexitate: 0(1)

    return nrL;
}


// returnare numar coloane
int Matrice::nrColoane() const {
    //Complexitate: 0(1)

    return nrC;
}



void Matrice::distrugeRecursiv(Nod* p) {
    //Complexitate: O(n) -unde n este nr. de noduri

    //stergem toate elementele
    if (p != nullptr) {
        distrugeRecursiv(p->stanga);
        distrugeRecursiv(p->dreapta);
        delete p;
    }

}



Nod* Matrice::adaugaRecursiv(Nod* p, TElemMatrix e) {
    //Complexitate: O(h) -unde h este inaltimea

    if (p == nullptr) {
        p = new Nod;
        p->elem = e;
        p->dreapta = nullptr;
        p->stanga = nullptr;
    }

    else {
        if (p->elem.linie < e.linie || (p->elem.linie == e.linie && p->elem.coloana < e.coloana))
            p->stanga = adaugaRecursiv(p->stanga, e);
        else
            p->dreapta = adaugaRecursiv(p->dreapta, e);
    }

    return p;
}



TElem Matrice::adauga(TElemMatrix e) {
    //Complexitate: O(h) -unde h este inaltimea

    Nod* p = radacina;
    while (p != nullptr) {
        if (p->elem.linie == e.linie && p->elem.coloana == e.coloana) {
            TElem ex = p->elem.valoare;
            p->elem.valoare = e.valoare;
            return ex;
        }
        if (p->elem.linie < e.linie || (p->elem.linie == e.linie && p->elem.coloana < e.coloana))
            p = p->stanga;
        else
            p = p->dreapta;
    }
    
    radacina = adaugaRecursiv(radacina, e);

    return NULL_TELEMENT;
}


//returnare element de pe o linie si o coloana
//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
//indicii se considera incepand de la 0
TElem Matrice::element(int i, int j) const {
    //Complexitate: O(h) -unde h este inaltimea

    if (i < 0 || i >= nrL || j < 0 || j >= nrC)
        throw exception();

    Nod* p = radacina;
    while (p != nullptr) {
        if (p->elem.linie == i && p->elem.coloana == j)
            return p->elem.valoare;
        if (p->elem.linie < i || (p->elem.linie == i && p->elem.coloana < j))
            p = p->stanga;
        else
            p = p->dreapta;
    }

    return NULL_TELEMENT;
}



TElem Matrice::sterge(int i, int j) {
    //Complexitate: O(h) -unde h este inaltimea

    Nod* p = radacina;
    TElem  ex = NULL_TELEMENT;

    //parcurgem pana gasim elementul vechi
    while (p != nullptr) {
        if (p->elem.linie == i && p->elem.coloana == j)
            ex = p->elem.valoare;
        if (p->elem.linie < i || (p->elem.linie == i && p->elem.coloana < j))
            p = p->stanga;
        else
            p = p->dreapta;
    }

    //realizam stergerea
    radacina = stergeRecursiv(radacina, i, j);
    
    return ex;
}


// modificare element de pe o linie si o coloana si returnarea vechii valori
// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
TElem Matrice::modifica(int i, int j, TElem e) {
    //Complexitate: O(h) -unde h este inaltimea

    if (i < 0 || i >= nrL || j < 0 || j >= nrC)
        throw exception();

    if (e == NULL_TELEMENT) {
        return sterge(i, j);
    }

    //cream nod nou pt. a fi adaugat
    TElemMatrix elem;

    elem.linie = i;
    elem.coloana = j;
    elem.valoare = e;

    return adauga(elem);
}


//destructor
Matrice::~Matrice() {
    //Complexitate: 0(n) -unde n este nr. de elemente

    distrugeRecursiv(radacina);
}


Nod* Matrice::stergeRecursiv(Nod* p, int i, int j) {
    //Complexitate: O(h) -unde h este inaltimea arborelui

    if (p == nullptr) {
        return p;
    }

    //stergere subarbore stang
    if (p->elem.linie < i || (p->elem.linie == i && p->elem.coloana < j)) {
        p->stanga = stergeRecursiv(p->stanga, i, j);
        return p;
    }

    //stergere subarbore drept
    else if (p->elem.linie > i || (p->elem.linie == i && p->elem.coloana > j)) {
        p->dreapta = stergeRecursiv(p->dreapta, i, j);
        return p;
    }

    else {

        //stergem nodul
        if (p->stanga != nullptr && p->dreapta != nullptr) {
            Nod* aux = minim(p->dreapta);
            p->elem = aux->elem;
            p->dreapta = stergeRecursiv(p->dreapta, p->elem.linie, p->elem.coloana);
        }

        else {
            Nod* aux = p;
            Nod* r;

            if (p->stanga == nullptr) {
                r = p->dreapta;
            }

            else {
                r = p->stanga;
            }

            delete(aux);

            return r;
        }
    }
}


Nod* Matrice::minim(Nod* p) {
    //Complexitate: O(log2n) sau O(h) -unde h este inaltimea

    while (p->stanga != nullptr) {
        p = p->stanga;
    }

    return p;
}




/*
Cerinta lab: Scriet fct. care determina suma elem. de sub diagonala principala

Subalgoritm sumaSubDiagonalaPrincipala()
    sumaSubDiagonalaPrincipala()<-Suma(radacina)
SfSubalgoritm

Subalgoritm Suma(p)
    suma<-0
    Daca p != NIL atunci
        Daca [p].elem.coloana < [p].elem.linie atunci
            suma<-suma+[p].elem.valoare
        SfDaca
        suma<-suma+Suma([p].dreapta)
        suma<-suma+Suma([p].stanga)
    SfDaca
    Suma(p)<-suma
SfSubalgoritm

Complexitate: O(n) -unde n este nr. de elem.
*/
TElem Matrice::sumaSubDiagonalaPrincipala() {

    return Suma(radacina);
}

TElem Matrice::Suma(Nod* p) {

    int suma = 0;
    if (p != nullptr) {
        if (p->elem.coloana < p->elem.linie)
            suma += p->elem.valoare;
        suma += Suma(p->dreapta);
        suma += Suma(p->stanga);
    }

    return suma;
}