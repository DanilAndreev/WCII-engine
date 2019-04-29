#include "pch.h"
#include "gameMaster.h"

extern Console* defaultConsole;


const int GM_NO_ERROR = 0;
const int GM_ERROR_ALLOCATING_MEMORY = 1;
const int GM_ERROR_ARGUMENTS_COUNT = 2;
const int GM_ERROR_NOT_VALID_TYPE = 3;
const int GM_ERROR_NOT_VALID_STRUCTURE = 4;


GameMaster::GameMaster() {

}

GameMaster::~GameMaster() {
	
}


vector<string> GameMaster::dirFilenames(string dirPath) {
	vector <string> filenames;

	std::string pattern(dirPath);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	cout << "starting to search for files" << endl;
	if ((hFind = FindFirstFile((LPCWSTR)pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			cout << "found file: " << (char*)(*(data.cFileName))  << endl;
			string temp = (char*)(*(data.cFileName));
			filenames.push_back(temp);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	else {
		printf("FindFirstFile failed (%d)\n", GetLastError());
	}
	cout << "files found:" << endl;
	for (int i = 0; i < filenames.size(); i++) {

		cout << "file" << filenames[i] << endl;
	}
	return filenames;
/*
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
				
			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
	return vector<string>();
*/
}




void GameMaster::readUnits() {

/*
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
*/


}

Exitcode GameMaster::readParseSpell(string filename) {
	ParserOut input;
	FileParser* parser = new FileParser();

	string name = "default";
	string beautyName = "Default";
	string type = "area";
	char symbol = 'd';
	int damage = 30; 
	int cooldown = 1000;
	int castCooldown = 4000;
	int attackRadius = 5;
	int cost = 100;
	int productionTime = 10000;


	//parsing file and checking errors in allocating memory
	if (!parser) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	input = parser->parseFile(filename);
	delete parser;


	if (input.args.size() < 8) {
		return GM_ERROR_ARGUMENTS_COUNT;
	}

	//interpriting parsed file data
	if (input.args[0].first != "spell") {
		return GM_ERROR_NOT_VALID_TYPE;
	}
	if (input.args[1].second == "word") {
		name = input.args[1].first;
		// --------------------------------------------------------------------ADD EVENT AND CHECK THE NAME, if exist - name.append(to_string(i)); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	if (input.args[2].second != "fbord" || input.args[input.args.size()-1].second != "fbord") {
		return GM_ERROR_NOT_VALID_STRUCTURE;
	}
	if (input.args[2].first != "{" || input.args[input.args.size() - 1].first != "}") {
		return GM_ERROR_NOT_VALID_STRUCTURE;
	}
	int lineArgs = 1;
	for (unsigned int i = 3; i < input.args.size() - 1; i += lineArgs) {
		lineArgs = 1;
		// Checking input correctness
		if (input.args[i].second != "word") {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (i + 3 > input.args.size()-1) {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		lineArgs = 4;
		if (input.args[i + 1].second != "ddots") {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (input.args[i + 3].second != "dotcom") {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		// Temporary buffer variables
		string temp_str;
		int temp_integer = 0;
		char temp_character = ' ';

		// Choosing buffer to save info
		if (input.args[i + 2].second == "qdata" && strlen(input.args[i + 2].first.data()) == 1) {
			temp_character = input.args[i + 2].first[0];
		}
		if (input.args[i + 2].second == "dqdata" || input.args[i + 2].second == "word") {
			temp_str = input.args[i + 2].first;
		}
		if (input.args[i + 2].second == "number") {
			temp_integer = stoi(input.args[i + 2].first);
		}

		// Checking the parameter
		if (input.args[i].first == "beautyName") {
			beautyName = temp_str;
		}
		if (input.args[i].first == "type") {
			type = temp_str;
		}
		if (input.args[i].first == "symbol") {
			symbol = temp_character;
		}
		if (input.args[i].first == "damage") {
			damage = temp_integer;
		}
		if (input.args[i].first == "cooldown") {
			cooldown = temp_integer;
		}
		if (input.args[i].first == "castCooldown") {
			castCooldown = temp_integer;
		}
		if (input.args[i].first == "attackRadius") {
			attackRadius = temp_integer;
		}
		if (input.args[i].first == "cost") {
			cost = temp_integer;
		}
		if (input.args[i].first == "productionTime") {
			productionTime = temp_integer;
		}
	}

	//finished filling the variables, creating spell;
	SpellPreset tempSpellPreset(name, beautyName, type, symbol, damage, cooldown, castCooldown, attackRadius, cost, productionTime);
	this->spellsPresets.push_back(tempSpellPreset);
	tempSpellPreset.print();
	return GM_NO_ERROR;
}







void GameMaster::readSpells() {
	Exitcode exitcode = readParseSpell("spells/demonFury.spell");
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
}

void GameMaster::readBuildings() {

/*
	ifstream takeData("units/*.unit");
	string line;
	while (getline(takeData, line, '}')) {
		stringstream ss(line);
		string token;
		getline(ss, token, ';');

		Building * building = new Building();

	}
*/
}



bool GameMaster::saveGame() {
	return false;
}

bool GameMaster::loadGame() {
	return false;
}





//char value, int type, Field* field, int health, int team, int attackLength

