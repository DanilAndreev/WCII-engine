#include "pch.h"

Console* defaultConsole;
Controller* gameController;
extern ThreadDescriptor* gameThreads;
ConsoleCommandController* defaultConComCon;
GameMaster* gameMaster;


int main() {
	new ThreadDescriptor();
	gameMaster = new GameMaster();
	defaultConComCon = new ConsoleCommandController(defaultConsole, gameController);

//	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	EventHndlrTHREAD* evHdlrThread = (EventHndlrTHREAD*)(gameThreads->getThread(gameController->getEventHandlerDescriptor()));
	if (evHdlrThread) {
		HANDLE eventHandlerHandle = evHdlrThread->getThreadHandle();
		if (eventHandlerHandle) {
			WaitForSingleObject(eventHandlerHandle, INFINITE);
		}
	}
}
