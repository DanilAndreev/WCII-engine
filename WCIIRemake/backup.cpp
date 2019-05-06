// WCIIRemake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
/*
Console* defaultConsole;
Controller* gameController;
extern ThreadDescriptor* gameThreads;
ConsoleCommandController* defaultConComCon;
GameMaster* gameMaster;
*/
/*

using namespace std;
int main()
{
	new ThreadDescriptor();
*/
/*
	defaultConsole = new Console();
	MScreen* scr = new MScreen(85, 30);
	scr->setCord(cordScr(30, 2));
	Field* field = new Field(85, 30);
	scr->addElement(cordScr(2, 2), field->getWidth(), field->getHeigth(), field);

	LiveUnit* unt1 = new LiveUnit('a', 1, field, 100, 1, 30, 10, 1000, 40);
	LiveUnit* unt2 = new LiveUnit('b', 1, field, 100, 1, 25, 1000, 1000, 40);
	LiveUnit* unt3 = new LiveUnit('c', 1, field, 100, 1, 15, 1000, 1000, 40);
	LiveUnit* unt4 = new LiveUnit('d', 1, field, 100, 1, 35, 1000, 1000, 40);
	LiveUnit* obstacle1 = new LiveUnit('u', 1, field, 100, 2, 20, 1000, 1000, 40);
	LiveUnit* obstacle2 = new LiveUnit('x', 1, field, 100, 2, 33, 1000, 1000, 40);
	LiveUnit* obstacle3 = new LiveUnit('y', 1, field, 100, 2, 32, 1000, 1000, 40);
	LiveUnit* obstacle4 = new LiveUnit('z', 1, field, 100, 2, 31, 1000, 1000, 40);
	field->setCell(cordScr(1, 4), unt1);
	field->setCell(cordScr(5, 8), unt2);
	field->setCell(cordScr(4, 6), unt3);
	field->setCell(cordScr(1, 5), unt4);
	field->setCell(cordScr(5, 4), obstacle1);
	field->setCell(cordScr(6, 4), obstacle2);
	field->setCell(cordScr(6, 5), obstacle3);
	field->setCell(cordScr(7, 4), obstacle4);
*/
//	gameMaster->dirFilenames(".\\spells","spell");

/*
	gameMaster = new GameMaster();

//	gameController = new Controller(field, scr,  defaultConsole);
	defaultConComCon = new ConsoleCommandController(defaultConsole, gameController);

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
*/
//--------------------------------------------------------------------------
// Testing load game

/*
	Exitcode exitcode = gameMaster->loadGame("test");
	switch (exitcode) {
	case GM_ERROR_ALLOCATING_MEMORY:
		defaultConsole->error("Error allocating memory");
		break;
	case GM_ERROR_ARGUMENTS_COUNT:
		defaultConsole->error("Wrong arguments count");
		break;
	case GM_ERROR_NOT_VALID_TYPE:
		defaultConsole->error("Not valid type");
		break;
	case GM_ERROR_NOT_VALID_STRUCTURE:
		defaultConsole->error("Not valid structure");
		break;
	default:
		break;
	}
*/
//---------------------------------------------------------------------------
//	gameMaster->readSpells();
//	gameMaster->readUnits();
//	gameMaster->readBuildings();


//TESTING FILE PARSER

	//FileParser* parser = new FileParser();
	//ParserOut output = parser->parseFile("units/berserker.unit");
	//output.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//-----------------------------------------------------------------------
	//gameMaster->dirFilenames("C:\\Users\\user\\Documents\\GitHub\\WCII\\WCIIRemake\\spells");
	//gameMaster->readSpells();

//----------------------------------------------------------------------------


/*
	EventHndlrTHREAD* evHdlrThread = (EventHndlrTHREAD*)(gameThreads->getThread(gameController->getEventHandlerDescriptor()));
	if (evHdlrThread) {
		HANDLE eventHandlerHandle = evHdlrThread->getThreadHandle();
		if (eventHandlerHandle) {
			WaitForSingleObject(eventHandlerHandle, INFINITE);
		}
	}
*/

//	field->freeElements();
//	scr->freeElements();
//	delete scr;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
