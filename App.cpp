#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"

using namespace std;


int main() {

	testAll();
	testAllExtins();

	cout<<"End\n";
}


/*
-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Să se implementeze în C++ un anumit container de date (TAD) folosind o anumită
reprezentare (indicată) și un arbore binar de căutare (ABC) ca structură de date.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

P1. TAD Matrice - reprezentare sub forma unei matrice rare (triplete de forma <linie, coloană,valoare> (valoare!=0)), 
memorate folosind un ABC reprezentat înlănțuit cu alocare dinamică.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
