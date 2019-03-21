#include "pch.h"
#include "gameMaster.h"


GameMaster::GameMaster() {

}

GameMaster::~GameMaster() {
	
}

void GameMaster::readUnits() {
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;

	char path[] = "units/*.unit";
	wchar_t wpath[256];
	mbstowcs_s(NULL, wpath, path, strlen(path) + 1);
	LPWSTR ptr = wpath;

	if ((hFind = FindFirstFile(ptr, &FindFileData)) != INVALID_HANDLE_VALUE) {
		do {
			printf("%s\n", FindFileData.cFileName);
			cout << (char*)FindFileData.cFileName << endl;
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
}
