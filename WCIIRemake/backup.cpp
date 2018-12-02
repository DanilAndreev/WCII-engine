// WCIIRemake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"


int main()
{

	MScreen* scr = new MScreen(30,10);
	Field* field = new Field(30,10);
	scr->addElement(cordScr(2, 2), 1, 1, field);

/*
	cordScr cords;
	cords.x = 2;
	cords.y = 2;
*/
	



	Unit* unt1 = new Unit('a', 1, field);
	Unit* unt2 = new Unit('b', field);
	Unit* unt3 = new Unit('c', field);
	Unit* unt4 = new Unit('T', 1, field);
	field->setCell(cordScr(1, 4), unt1);
	field->setCell(cordScr(1, 5), unt4);
	field->setCell(cordScr(5, 8), unt2);
	field->setCell(cordScr(4, 6), unt3);



	//scr->putToBuff(cordScr(1, 1), 'w');
	scr->render();


	unt4->move(1);

	scr->render();

	unt4->move(3);

	scr->render();




	field->freeElements();
	scr->freeElements();
	delete scr;




	//system("pause");





/*
	std::cout << "Hello World!\n";

	for (int i = 0; i < arr->count(); i++) {
		std::cout << arr->get(1)->getClassName() << "\n";
	}
	delete arr;
*/

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
