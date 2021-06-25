#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
	Matrice m(4,4);
	assert(m.sumaSubDiagonalaPrincipala() == 0);

	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1,1,5);
	assert(m.element(1,1) == 5);
	m.modifica(1,1,6);
	assert(m.element(1,2) == NULL_TELEMENT);

	/*m.modifica(2, 1, 2);
	assert(m.element(2, 1) == 2);
	m.modifica(3, 2, 2);
	assert(m.element(3, 2) == 2);
	m.modifica(2, 3, 2);
	assert(m.element(2, 3) == 2);*/
	

	m.modifica(1,0,5);
	m.modifica(2,0,5);
	m.modifica(3,0,5);
	cout << m.sumaSubDiagonalaPrincipala() << endl;
	assert(m.sumaSubDiagonalaPrincipala() == 15);
}
