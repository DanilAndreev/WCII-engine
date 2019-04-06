#include "pch.h"
#include "gameMaster.h"
#include <fstream>
#include <string>
#include <sstream>
#include <string_view>
#include <map>


GameMaster::GameMaster() {

}

GameMaster::~GameMaster() {
	
}

vector<string> & GameMaster::split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

vector<string> GameMaster::split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

int GameMaster::check_token(string & token) {
	if (token == "BeautyName: Berserker;" || token == "BeautyName: Warlock;") {
		// parse token
		return 1;
	}
	if (token == "fraction:") {
		//next_token(token);
		//token.pop_back();
		//fraction = token;
		return 2;
	}
	if (token == "symbol:") {
		//next_token(token);
		//stringstream ss(token);
		//string symbol;
		//getline(ss, symbol, '\'');
		//fraction = token;
		return 3;
	}
	if (token == "width:") {
		//next_token(token);
		//token.pop_back();
		//width = atoi(token.c_str());
		return 4;
	}
	if (token == "height:") {
		//next_token(token);
		//token.pop_back();
		//height = atoi(token.c_str());
		return 5;
	}
	if (token == "health:") {
		//next_token(token);
		//token.pop_back();
		//height = atoi(token.c_str());
		return 6;
	}
	if (token == "damage:") {
		//next_token(token);
		//token.pop_back();
		//damage = atoi(token.c_str());
		return 7;
	}
	if (token == "cooldown:") {
		//next_token(token);
		//token.pop_back();
		//cooldown = atoi(token.c_str());
		return 8;
	}
	if (token == "attackRadius:") {
		//next_token(token);
		//token.pop_back();
		//attackRadius = atoi(token.c_str());;
		return 9;
	}
	if (token == "speedDelay:") {
		//next_token(token);
		//token.pop_back();
		//speedDelay = atoi(token.c_str());
		return 10;
	}
	if (token == "mana:") {
		//next_token(token);
		//token.pop_back();
		//mana = atoi(token.c_str());
		return 11;
	}
	if (token == "spells:") {
		//next_token(token);
		//token.pop_back();
		//fraction = token;
		return 12;
	}
	if (token == "cost:") {
		//next_token(token);
		//token.pop_back();
		//cost = atoi(token.c_str());
		return 13;
	}
	if (token == "eats:") {
		//next_token(token);
		//token.pop_back();
		//eats = atoi(token.c_str());
		return 14;
	}
	if (token == "productionTime:") {
		//next_token(token);
		//token.pop_back();
		//productionTime = atoi(token.c_str());
		return 15;
	}
	return 0;
}

bool GameMaster::next_token(string & token){
	stringstream ss(line);
	while (getline(ss, token, ' ')) { cout << line; }
	return true;
}

void GameMaster::readUnits() {
	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;

	char path[] = "units/*.unit";
	wchar_t wpath[256];
	mbstowcs_s(NULL, wpath, path, strlen(path) + 1);
	LPWSTR ptr = wpath;
	int type, health, team, attackLength; 
	char value;
	if ((hFind = FindFirstFile(ptr, &FindFileData)) != INVALID_HANDLE_VALUE) {
		do {
			ifstream takeData(wpath);
			while (getline(takeData, line)) {
				string token;
				vector<string> elements = split(line, ' ');
			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
}

void GameMaster::readBuildings() {
	ifstream takeData("units/*.unit");
	string line;
	while (getline(takeData, line, '}')) {
		stringstream ss(line);
		string token;
		getline(ss, token, ';');

		Building * building = new Building();

	}
}

bool GameMaster::saveGame(vector<LiveUnit> & units) {
	ofstream ofs("units/*.unit", ios::binary);
	ofs.write((char *)&units, sizeof(units));
	ofs.close();
	return true;
}

bool GameMaster::loadGame(vector<LiveUnit> & units) {
	ifstream ifs("fifthgrade.ros", ios::binary);
	ifs.read((char *)&units, sizeof(units));
	ifs.close();
	return true;
}





//char value, int type, Field* field, int health, int team, int attackLength