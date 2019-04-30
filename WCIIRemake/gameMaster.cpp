#include "pch.h"
#include "gameMaster.h"

extern Console* defaultConsole;

// Parser exitcodes
const Exitcode GM_NO_ERROR = 0; // No errors
const Exitcode GM_ERROR_ALLOCATING_MEMORY = 1; // Error allocating memory
const Exitcode GM_ERROR_ARGUMENTS_COUNT = 2; // Error, too low arguments
const Exitcode GM_ERROR_NOT_VALID_TYPE = 3; // Error, not valid type of target input
const Exitcode GM_ERROR_NOT_VALID_STRUCTURE = 4; // Error, not valid structure of encoding


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

	string name = "default";
	string beautyName = "Default";
	string fraction = "default";
	char symbol = 'd';
	int width = 1;
	int heigth = 1;
	int health = 100;
	int damage = 20;
	int cooldown = 1000;
	int attackRadius = 5;
	int speedDelay = 1000;
	int mana = 100;
	vector <string> spells;
	int cost = 100;
	int eats = 10;
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

	//interpreting parsed file data
	if (input.args[0].first != "unit") {
		return GM_ERROR_NOT_VALID_TYPE;
	}
	if (input.args[1].second == "word") {
		name = input.args[1].first;
		// --------------------------------------------------------------------ADD EVENT AND CHECK THE NAME, if exist - name.append(to_string(i)); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	if (input.args[2].second != "fbord" || input.args[input.args.size() - 1].second != "fbord") {
		return GM_ERROR_NOT_VALID_STRUCTURE;
	}
	if (input.args[2].first != "{" || input.args[input.args.size() - 1].first != "}") {
		return GM_ERROR_NOT_VALID_STRUCTURE;
	}

	int lineArgs = 1; // count of arguments in one line, to jump over lines in each step
	for (unsigned int i = 3; i < input.args.size() - 1; i += lineArgs) {
		lineArgs = 1;
		// Checking input correctness
		if (input.args[i].second != "word") {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (i + 1 >= input.args.size()) {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (input.args[i+1].second != "ddots") {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (input.args[i].first == "spells") {  // condition for looking for multiple values
			if (input.args[i + 2].second != "sbord") {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			if (input.args[i + 2].first != "[") {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			int startbrackets_index = i + 2;
			if (startbrackets_index + 2 >= input.args.size()) {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			if (input.args[startbrackets_index + 1].first == "]" && input.args[startbrackets_index + 1].second == "sbord" && input.args[startbrackets_index + 2].second == "dotcom") { // checking if it is an empty data sequence
				lineArgs = 5;
			}
			else {
				int endbrackets_index = startbrackets_index + 1;
				if (endbrackets_index >= input.args.size()) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				while (input.args[endbrackets_index].second != "sbord" && input.args[endbrackets_index].first != "]" && endbrackets_index < input.args.size()) { // looking for ] symbol id
					endbrackets_index++;
				}
				if (endbrackets_index == input.args.size() - 1) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				if (endbrackets_index + 1 >= input.args.size()) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				if (input.args[endbrackets_index + 1].second != "dotcom") {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				lineArgs = endbrackets_index - i + 2; // setting line width to number of line arguments to skip whole line on the next step
				if ((endbrackets_index - startbrackets_index) % 2 != 0) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				vector <string> vstring_temp;
				for (int ind = startbrackets_index + 1; ind < endbrackets_index; ind += 2) {
					if (input.args[ind].second != "dqdata") {
						return GM_ERROR_NOT_VALID_STRUCTURE;
					}
					if (input.args[ind + 1].second != "coma" && ind + 1 != endbrackets_index) {
						return GM_ERROR_NOT_VALID_STRUCTURE;
					}
					vstring_temp.push_back(input.args[ind].first);
					//checking the parameter
					if (input.args[i].first == "spells") {
						spells = vstring_temp;
					}
				}
			}
		}
		else {
			if (i + 3 > input.args.size() - 1) {
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
			if (input.args[i].first == "beautyName" && input.args[i + 2].second == "dqdata") {
				beautyName = temp_str;
			}
			if (input.args[i].first == "fraction" && input.args[i + 2].second == "dqdata") {
				fraction = temp_str;
			}
			if (input.args[i].first == "symbol" && input.args[i + 2].second == "qdata") {
				symbol = temp_character;
			}
			if (input.args[i].first == "width" && input.args[i + 2].second == "number") {
				width = temp_integer;
			}
			if (input.args[i].first == "heigth" && input.args[i + 2].second == "number") {
				heigth = temp_integer;
			}
			if (input.args[i].first == "health" && input.args[i + 2].second == "number") {
				health = temp_integer;
			}
			if (input.args[i].first == "damage" && input.args[i + 2].second == "number") {
				damage = temp_integer;
			}
			if (input.args[i].first == "cooldown" && input.args[i + 2].second == "number") {
				cooldown = temp_integer;
			}
			if (input.args[i].first == "attackRadius" && input.args[i + 2].second == "number") {
				attackRadius = temp_integer;
			}
			if (input.args[i].first == "speedDelay" && input.args[i + 2].second == "number") {
				speedDelay = temp_integer;
			}
			if (input.args[i].first == "mana" && input.args[i + 2].second == "number") {
				mana = temp_integer;
			}
			if (input.args[i].first == "cost" && input.args[i + 2].second == "number") {
				cost = temp_integer;
			}
			if (input.args[i].first == "eats" && input.args[i + 2].second == "number") {
				eats = temp_integer;
			}
			if (input.args[i].first == "productionTime" && input.args[i + 2].second == "number") {
				productionTime = temp_integer;
			}
		}
	}

	//finished filling the variables, creating spell;
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

	string name = "default";
	string beautyName = "Default";
	string type = "area";
	char symbol = 'd';
	int damage = 0; 
	int heal = 0;
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

	//interpreting parsed file data
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
		if (input.args[i].first == "beautyName" && input.args[i + 2].second == "dqdata") {
			beautyName = temp_str;
		}
		if (input.args[i].first == "type" && input.args[i + 2].second == "word") {
			type = temp_str;
		}
		if (input.args[i].first == "symbol" && input.args[i + 2].second == "qdata") {
			symbol = temp_character;
		}
		if (input.args[i].first == "damage" && input.args[i + 2].second == "number") {
			damage = temp_integer;
		}
		if (input.args[i].first == "cooldown" && input.args[i + 2].second == "number") {
			cooldown = temp_integer;
		}
		if (input.args[i].first == "castCooldown" && input.args[i + 2].second == "number") {
			castCooldown = temp_integer;
		}
		if (input.args[i].first == "attackRadius" && input.args[i + 2].second == "number") {
			attackRadius = temp_integer;
		}
		if (input.args[i].first == "cost" && input.args[i+2].second == "number") {
			cost = temp_integer;
		}
		if (input.args[i].first == "productionTime" && input.args[i + 2].second == "number") {
			productionTime = temp_integer;
		}
		if (input.args[i].first == "heal" && input.args[i + 2].second == "number") {
			heal = temp_integer;
		}
	}

	//finished filling the variables, creating spell;
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

	string name = "default";
	string beautyName = "Default";
	string fraction = "default";
	char symbol = 'D';
	int width = 1;
	int heigth = 1;
	int health = 1000;
	int damage = 0;
	int cooldown = 1000;
	int attackRadius = 3;
	int mana = 100;
	vector <string> spells;
	vector <string> production;
	int cost = 1000;
	int productionTime = 10000000;

	//parsing file and checking errors in allocating memory
	if (!parser) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	input = parser->parseFile(filename);
	delete parser;


	if (input.args.size() < 8) {
		return GM_ERROR_ARGUMENTS_COUNT;
	}

	//interpreting parsed file data
	if (input.args[0].first != "building") {
		return GM_ERROR_NOT_VALID_TYPE;
	}
	if (input.args[1].second == "word") {
		name = input.args[1].first;
		// --------------------------------------------------------------------ADD EVENT AND CHECK THE NAME, if exist - name.append(to_string(i)); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	if (input.args[2].second != "fbord" || input.args[input.args.size() - 1].second != "fbord") {
		return GM_ERROR_NOT_VALID_STRUCTURE;
	}
	if (input.args[2].first != "{" || input.args[input.args.size() - 1].first != "}") {
		return GM_ERROR_NOT_VALID_STRUCTURE;
	}

	int lineArgs = 1; // count of arguments in one line, to jump over lines in each step
	for (unsigned int i = 3; i < input.args.size() - 1; i += lineArgs) {
		lineArgs = 1;
		// Checking input correctness
		if (input.args[i].second != "word") {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (i + 1 >= input.args.size()) {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (input.args[i + 1].second != "ddots") {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (input.args[i].first == "spells" || input.args[i].first == "production") {  // condition for looking for multiple values
			if (input.args[i + 2].second != "sbord") {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			if (input.args[i + 2].first != "[") {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			int startbrackets_index = i + 2;
			if (startbrackets_index + 2 >= input.args.size()) {
				return GM_ERROR_NOT_VALID_STRUCTURE;
			}
			if (input.args[startbrackets_index + 1].first == "]" && input.args[startbrackets_index + 1].second == "sbord" && input.args[startbrackets_index + 2].second == "dotcom") { // checking if it is an empty data sequence
				lineArgs = 5;
			}
			else {
				int endbrackets_index = startbrackets_index + 1;
				if (endbrackets_index >= input.args.size()) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				while (input.args[endbrackets_index].second != "sbord" && input.args[endbrackets_index].first != "]" && endbrackets_index < input.args.size()) { // looking for ] symbol id
					endbrackets_index++;
				}
				if (endbrackets_index == input.args.size() - 1) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				if (endbrackets_index + 1 >= input.args.size()) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				if (input.args[endbrackets_index + 1].second != "dotcom") {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				lineArgs = endbrackets_index - i + 2; // setting line width to number of line arguments to skip whole line on the next step
				if ((endbrackets_index - startbrackets_index) % 2 != 0) {
					return GM_ERROR_NOT_VALID_STRUCTURE;
				}
				vector <string> vstring_temp;
				for (int ind = startbrackets_index + 1; ind < endbrackets_index; ind += 2) {
					if (input.args[ind].second != "dqdata") {
						return GM_ERROR_NOT_VALID_STRUCTURE;
					}
					if (input.args[ind + 1].second != "coma" && ind + 1 != endbrackets_index) {
						return GM_ERROR_NOT_VALID_STRUCTURE;
					}
					vstring_temp.push_back(input.args[ind].first);
					//checking the parameter
					if (input.args[i].first == "spells") {
						spells = vstring_temp;
					}
					if (input.args[i].first == "production") {
						production = vstring_temp;
					}
				}
			}
		}
		else {
			if (i + 3 > input.args.size() - 1) {
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
			if (input.args[i].first == "beautyName" && input.args[i + 2].second == "dqdata") {
				beautyName = temp_str;
			}
			if (input.args[i].first == "fraction" && input.args[i + 2].second == "dqdata") {
				fraction = temp_str;
			}
			if (input.args[i].first == "symbol" && input.args[i + 2].second == "qdata") {
				symbol = temp_character;
			}
			if (input.args[i].first == "width" && input.args[i + 2].second == "number") {
				width = temp_integer;
			}
			if (input.args[i].first == "heigth" && input.args[i + 2].second == "number") {
				heigth = temp_integer;
			}
			if (input.args[i].first == "health" && input.args[i + 2].second == "number") {
				health = temp_integer;
			}
			if (input.args[i].first == "damage" && input.args[i + 2].second == "number") {
				damage = temp_integer;
			}
			if (input.args[i].first == "cooldown" && input.args[i + 2].second == "number") {
				cooldown = temp_integer;
			}
			if (input.args[i].first == "attackRadius" && input.args[i + 2].second == "number") {
				attackRadius = temp_integer;
			}
			if (input.args[i].first == "mana" && input.args[i + 2].second == "number") {
				mana = temp_integer;
			}
			if (input.args[i].first == "cost" && input.args[i + 2].second == "number") {
				cost = temp_integer;
			}
			if (input.args[i].first == "productionTime" && input.args[i + 2].second == "number") {
				productionTime = temp_integer;
			}
		}
	}

	//finished filling the variables, creating spell;
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





//char value, int type, Field* field, int health, int team, int attackLength

