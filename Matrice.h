#pragma once

typedef int TElem;

typedef struct {
    int linie;
    int coloana;
    int valoare;
}TElemMatrix;

typedef struct Nod {
    TElemMatrix elem;
    Nod* stanga;
    Nod* dreapta;
}Nod;

#define NULL_TELEMENT 0


//TAD  Matrice-reprezentare  sub  forma  unei  matrice  rare  (triplete  de  forma  <linie, coloană, valoare> (valoare!=0)),
//memorate folosind un ABC reprezentat înlănțuit cu alocare dinamică
class Matrice {

private:
    int nrL;
    int nrC;
    Nod* radacina;

    TElem adauga(TElemMatrix);
    TElem sterge(int i, int j);

    Nod* adaugaRecursiv(Nod* p, TElemMatrix e);
    Nod* stergeRecursiv(Nod* p, int i, int j);
    Nod* minim(Nod*);

    void distrugeRecursiv(Nod*);

public:

    //constructor
    //se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
    Matrice(int nrLinii, int nrColoane);

    //destructor
    ~Matrice();

    //returnare element de pe o linie si o coloana
    //se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
    //indicii se considera incepand de la 0
    TElem element(int i, int j) const;


    // returnare numar linii
    int nrLinii() const;

    // returnare numar coloane
    int nrColoane() const;


    // modificare element de pe o linie si o coloana si returnarea vechii valori
    // se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
    TElem modifica(int i, int j, TElem);

    TElem sumaSubDiagonalaPrincipala();
    TElem Suma(Nod*);
};