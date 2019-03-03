// WCIIRemake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"

Console* defaultConsole;
Controller* gameController;

using namespace std;
int main()
{
	defaultConsole = new Console();
	MScreen* scr = new MScreen(85, 30);
	scr->setCord(cordScr(30, 2));
	Field* field = new Field(85, 30);
	scr->addElement(cordScr(2, 2), field->getWidth(), field->getHeigth(), field);
/*
	cordScr cords;
	cords.x = 2;
	cords.y = 2;
*/

	LiveUnit* unt1 = new LiveUnit('a', 1, field, 100, 1, 30);
	LiveUnit* unt2 = new LiveUnit('b', 1, field, 100, 1, 25);
	LiveUnit* unt3 = new LiveUnit('c', 1, field, 100, 1, 15);
	LiveUnit* unt4 = new LiveUnit('d', 1, field, 100, 1, 35);
	LiveUnit* obstacle1 = new LiveUnit('u', 1, field, 100, 2, 20);
	LiveUnit* obstacle2 = new LiveUnit('x', 1, field, 100, 2, 33);
	LiveUnit* obstacle3 = new LiveUnit('y', 1, field, 100, 2, 32);
	LiveUnit* obstacle4 = new LiveUnit('z', 1, field, 100, 2, 31);
	field->setCell(cordScr(1, 4), unt1);
	field->setCell(cordScr(5, 8), unt2);
	field->setCell(cordScr(4, 6), unt3);
	field->setCell(cordScr(1, 5), unt4);
	field->setCell(cordScr(5, 4), obstacle1);
	field->setCell(cordScr(6, 4), obstacle2);
	field->setCell(cordScr(6, 5), obstacle3);
	field->setCell(cordScr(7, 4), obstacle4);


	//scr->putToBuff(cordScr(1, 1), 'w');
	scr->render();

//	unt4->move(1);

	scr->render();

//	unt4->move(3);

	scr->render();
	//system("cls");
	
	/*1--> The cell is not blocked
	0--> The cell is blocked    */

/*

	AStar* astar = new AStar(20, 20);
	astar->DebugMap();
	//astar->getPathMap();
	
	astar->aStarSearch(cordScr(0, 0), cordScr(18, 18));
	astar->getPathMap();
	cout << astar->getPath();

	delete astar;
*/

	//Console* console = new Console();
	gameController = new Controller(field, scr,  defaultConsole);
	ConsoleCommandController* conComCon = new ConsoleCommandController(defaultConsole, gameController);


	
	conComCon->startThread();

	scr->startThread();

	HANDLE hThreadCTRL = gameController->startThread();

	WaitForSingleObject(hThreadCTRL, INFINITE);


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
