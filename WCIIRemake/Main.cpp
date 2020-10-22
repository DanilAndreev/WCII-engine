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
	new ThreadDescriptor();
	defaultConsole = new Console();
	defaultConComCon = new ConsoleCommandController(defaultConsole, gameController, 0);
	gameMaster = new GameMaster();

	GameAlifeTHREAD* HgameAlifeThread = (GameAlifeTHREAD*)(gameThreads->getThread(gameMaster->getGameAlifeTHREADDescriptor()));

	if (HgameAlifeThread) {
		HANDLE gameAlifeHandle = HgameAlifeThread->getThreadHandle();
		if (gameAlifeHandle) {
			WaitForSingleObject(gameAlifeHandle, INFINITE);
		}
	}
}
