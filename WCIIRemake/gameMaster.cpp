#include "pch.h"
#include "gameMaster.h"

extern Console* defaultConsole;

extern const char* PARSER_DQDATA;
extern const char* PARSER_QDATA;
extern const char* PARSER_DOTCOM;
extern const char* PARSER_COMA;
extern const char* PARSER_DDOTS;
extern const char* PARSER_NUMBER;
extern const char* PARSER_WORD;
extern const char* PARSER_SBORD_LIST;
extern const char* PARSER_SBORD;
extern const char* PARSER_FBORD;
extern const char* PARSER_DQUOTE;
extern const char* PARSER_QUOTE;



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



Exitcode GameMaster::readParseUnit(string filename) {
	ParserOut input;
	FileParser* parser = new FileParser();
	if (!parser) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	input = parser->parseFile(filename);
	delete parser;

	UnInSearchTargets targets("unit");
	// configurating search for unit
	targets.addTarget(SearchTarget("name", PARSER_WORD, "default"));
	targets.addTarget(SearchTarget("beautyName", PARSER_DQDATA, "Default"));
	targets.addTarget(SearchTarget("fraction", PARSER_DQDATA, "Default"));
	targets.addTarget(SearchTarget("symbol", PARSER_QDATA, "d"));
	targets.addTarget(SearchTarget("width", PARSER_NUMBER, "1"));
	targets.addTarget(SearchTarget("heigth", PARSER_NUMBER, "1"));
	targets.addTarget(SearchTarget("health", PARSER_NUMBER, "100"));
	targets.addTarget(SearchTarget("damage", PARSER_NUMBER, "40"));
	targets.addTarget(SearchTarget("cooldown", PARSER_NUMBER, "1000"));
	targets.addTarget(SearchTarget("attackRadius", PARSER_NUMBER, "5"));
	targets.addTarget(SearchTarget("speedDelay", PARSER_NUMBER, "1000"));
	targets.addTarget(SearchTarget("mana", PARSER_NUMBER, "100"));
	targets.addTarget(SearchTarget("spells", PARSER_SBORD_LIST, "empty"));
	targets.addTarget(SearchTarget("cost", PARSER_NUMBER, "100"));
	targets.addTarget(SearchTarget("eats", PARSER_NUMBER, "2"));
	targets.addTarget(SearchTarget("productionTime", PARSER_NUMBER, "10000"));

	UnitInterpretor* interpretor = new UnitInterpretor();
	if (!interpretor) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	interpretor->init(targets);
	Exitcode exitcode = interpretor->interpret(input);
	if (exitcode != GM_NO_ERROR) {
		return exitcode;
	}
	targets = interpretor->getTargets();
	delete interpretor;


	string name = targets.targets[0].temp_string;
	string beautyName = targets.targets[1].temp_string;
	string fraction = targets.targets[2].temp_string;
	char symbol = targets.targets[3].temp_char;
	int width = targets.targets[4].temp_int;
	int heigth = targets.targets[5].temp_int;
	int health = targets.targets[6].temp_int;
	int damage = targets.targets[7].temp_int;
	int cooldown = targets.targets[8].temp_int;
	int attackRadius = targets.targets[9].temp_int;
	int speedDelay = targets.targets[10].temp_int;
	int mana = targets.targets[11].temp_int;
	vector <string> spells = targets.targets[12].temp_vstring;
	int cost = targets.targets[13].temp_int;
	int eats = targets.targets[14].temp_int;
	int productionTime = targets.targets[15].temp_int;

	LiveUnitPreset tempCreaturePreset(name, beautyName, fraction, symbol, width, heigth, health, damage, cooldown, attackRadius, speedDelay, mana, spells, cost, eats, productionTime);
	this->creaturePresets.push_back(tempCreaturePreset);
	tempCreaturePreset.print();

	return GM_NO_ERROR;
}



void GameMaster::readUnits() {
	Exitcode exitcode = readParseUnit("units/berserker.unit");
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
	if (!parser) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	input = parser->parseFile(filename);
	delete parser;

	UnInSearchTargets targets("spell");
	// configurating search for unit
	targets.addTarget(SearchTarget("name", PARSER_WORD, "default"));
	targets.addTarget(SearchTarget("beautyName", PARSER_DQDATA, "Default"));
	targets.addTarget(SearchTarget("type", PARSER_WORD, "area"));
	targets.addTarget(SearchTarget("symbol", PARSER_QDATA, "d"));
	targets.addTarget(SearchTarget("damage", PARSER_NUMBER, "0"));
	targets.addTarget(SearchTarget("heal", PARSER_NUMBER, "0"));
	targets.addTarget(SearchTarget("cooldown", PARSER_NUMBER, "1000"));
	targets.addTarget(SearchTarget("castCooldown", PARSER_NUMBER, "2000"));
	targets.addTarget(SearchTarget("attackRadius", PARSER_NUMBER, "1"));
	targets.addTarget(SearchTarget("cost", PARSER_NUMBER, "100"));
	targets.addTarget(SearchTarget("productionTime", PARSER_NUMBER, "10000"));

	UnitInterpretor* interpretor = new UnitInterpretor();
	if (!interpretor) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	interpretor->init(targets);
	Exitcode exitcode = interpretor->interpret(input);
	if (exitcode != GM_NO_ERROR) {
		return exitcode;
	}
	targets = interpretor->getTargets();
	delete interpretor;


	string name = targets.targets[0].temp_string;
	string beautyName = targets.targets[1].temp_string;
	string type = targets.targets[2].temp_string;
	char symbol = targets.targets[3].temp_char;
	int damage = targets.targets[4].temp_int;
	int heal = targets.targets[5].temp_int;
	int cooldown = targets.targets[6].temp_int;
	int castCooldown = targets.targets[7].temp_int;
	int attackRadius = targets.targets[8].temp_int;
	int cost = targets.targets[9].temp_int;
	int productionTime = targets.targets[10].temp_int;


	SpellPreset tempSpellPreset(name, beautyName, type, symbol, damage, cooldown, castCooldown, attackRadius, cost, productionTime, heal);
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



Exitcode GameMaster::readParseBuilding(string filename) {
	ParserOut input;
	FileParser* parser = new FileParser();
	if (!parser) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	input = parser->parseFile(filename);
	delete parser;

	UnInSearchTargets targets("building");
	// configurating search for unit
	targets.addTarget(SearchTarget("name", PARSER_WORD, "default"));
	targets.addTarget(SearchTarget("beautyName", PARSER_DQDATA, "Default"));
	targets.addTarget(SearchTarget("fraction", PARSER_DQDATA, "Default"));
	targets.addTarget(SearchTarget("symbol", PARSER_QDATA, "d"));
	targets.addTarget(SearchTarget("width", PARSER_NUMBER, "1"));
	targets.addTarget(SearchTarget("heigth", PARSER_NUMBER, "1"));
	targets.addTarget(SearchTarget("health", PARSER_NUMBER, "100"));
	targets.addTarget(SearchTarget("damage", PARSER_NUMBER, "40"));
	targets.addTarget(SearchTarget("cooldown", PARSER_NUMBER, "1000"));
	targets.addTarget(SearchTarget("attackRadius", PARSER_NUMBER, "5"));
	targets.addTarget(SearchTarget("mana", PARSER_NUMBER, "100"));
	targets.addTarget(SearchTarget("spells", PARSER_SBORD_LIST, "empty"));
	targets.addTarget(SearchTarget("production", PARSER_SBORD_LIST, "empty"));
	targets.addTarget(SearchTarget("cost", PARSER_NUMBER, "100"));
	targets.addTarget(SearchTarget("productionTime", PARSER_NUMBER, "10000"));

	UnitInterpretor* interpretor = new UnitInterpretor();
	if (!interpretor) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	interpretor->init(targets);
	Exitcode exitcode = interpretor->interpret(input);
	if (exitcode != GM_NO_ERROR) {
		return exitcode;
	}
	targets = interpretor->getTargets();
	delete interpretor;

	string name = targets.targets[0].temp_string;
	string beautyName = targets.targets[1].temp_string;
	string fraction = targets.targets[2].temp_string;
	char symbol = targets.targets[3].temp_char;
	int width = targets.targets[4].temp_int;
	int heigth = targets.targets[5].temp_int;
	int health = targets.targets[6].temp_int;
	int damage = targets.targets[7].temp_int;
	int cooldown = targets.targets[8].temp_int;
	int attackRadius = targets.targets[9].temp_int;
	int mana = targets.targets[10].temp_int;
	vector <string> spells = targets.targets[11].temp_vstring;
	vector <string> production = targets.targets[12].temp_vstring;
	int cost = targets.targets[13].temp_int;
	int productionTime = targets.targets[14].temp_int;

	BuildingPreset tempBuildingPreset(name, beautyName, fraction, symbol, width, heigth, health, damage, cooldown, attackRadius, mana, spells, production, cost, productionTime);
	buildingPresets.push_back(tempBuildingPreset);
	tempBuildingPreset.print();
	return GM_NO_ERROR;
}



void GameMaster::readBuildings() {
	Exitcode exitcode = readParseBuilding("buildings/HordeBarracks.building");
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

