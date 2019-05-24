#include "pch.h"

#include <iostream>
#include "Renderable.h"
#include "Placable.h"
#include "CScreen.h"
#include <conio.h>


Console* defaultConsole;
Controller* gameController;
extern ThreadDescriptor* gameThreads;
ConsoleCommandController* defaultConComCon;
GameMaster* gameMaster;





int main() {

/*
	CScreen MScreen(cordScr(20, 2), 50, 25, CScreenPixel('_', COLOR_AQUA), 1);
	CScreen IScreen1(cordScr(-5, 5), 20, 10, CScreenPixel('.', COLOR_RED), 1);
	CScreen IScreen2(cordScr(30, 10), 20, 20, CScreenPixel('%', COLOR_YELLOW), 1);

	screenEl element(cordScr(2, 2), CScreenPixel('d', 10));

	MScreen.addMember(&IScreen1);
	MScreen.addMember(&IScreen2);

	IScreen1.addMember(&element);

	MScreen.render();
*/


//	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	Command_c command("select 10");
	Command_c pattern("select input_number");
	if (pattern ^= command) {
		cout << "Command is patterned" << endl;
	}
	else {
		cout << "Command isn\'t patterned" << endl;
	}

	new ThreadDescriptor();
	defaultConsole = new Console();
	defaultConComCon = new ConsoleCommandController(defaultConsole, gameController, 0);
	gameMaster = new GameMaster();

//	EventHndlrTHREAD* evHdlrThread = (EventHndlrTHREAD*)(gameThreads->getThread(gameController->getEventHandlerDescriptor()));
	GameAlifeTHREAD* HgameAlifeThread = (GameAlifeTHREAD*)(gameThreads->getThread(gameMaster->getGameAlifeTHREADDescriptor()));

//	gameMaster->scr->render();
	if (HgameAlifeThread) {
		HANDLE gameAlifeHandle = HgameAlifeThread->getThreadHandle();
		if (gameAlifeHandle) {
			WaitForSingleObject(gameAlifeHandle, INFINITE);
		}
	}

}
