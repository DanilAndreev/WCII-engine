#include "pch.h"
#include "gameMaster.h"
#include <comdef.h>

extern Console* defaultConsole;
extern Controller* gameController;

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

using namespace std;


GameMaster::GameMaster() {
	readSpells();
	readUnits();
	readBuildings();
	this->field = new Field(40,20);
	this->scr = new MScreen(40, 20);
	scr->setCord(cordScr(50, 2));
	scr->addElement(cordScr(2, 2), this->field->getWidth(), this->field->getHeigth(), this->field);


	Controller* oldgc = gameController;
	gameController = new Controller(this->field, scr, defaultConsole);
	if (oldgc) {
		delete oldgc;
	}
	LiveUnit* tunit = new LiveUnit();


	loadGame("test");

}

GameMaster::~GameMaster() {
	
}

typedef vector<string> stringvec;

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}


vector<string> GameMaster::dirFilenames(string dirPath, string filetype) {
	stringvec v;
	string pattern(dirPath);
	pattern.append("\\*");
	pattern.append(".");
	pattern.append(filetype);

	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(s2ws(pattern).c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			_bstr_t b(data.cFileName);
			const char* str = b;
			v.push_back(str);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	return v;
}


Exitcode GameMaster::ParseUnit(ParserOut input, LiveUnitPreset *writeTo) {
	if (writeTo == NULL) {
		return GM_ERROR_NULL_POINTER;
	}
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

//	this->creaturePresets.push_back(tempCreaturePreset);
//	tempCreaturePreset.print();
//	defaultConsole->message("Succesfully loaded ");
	*writeTo = tempCreaturePreset;
	return GM_NO_ERROR;
}

Exitcode GameMaster::ParseUnit(string filename, LiveUnitPreset* writeTo) {
	ParserOut input;
	FileParser* parser = new FileParser();
	if (!parser) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	input = parser->parseFile(filename);
	delete parser;
	Exitcode exitcode = ParseUnit(input, writeTo);
	if (exitcode == GM_NO_ERROR) {
	}
	return exitcode;
}

void GameMaster::readUnits() {
	string directory = ".\\units";
	string filetype = "unit";
	vector<string> files = dirFilenames(directory, filetype);

	for (int i = 0; i < files.size(); i++) {
		string path = directory;
		path.append("\\");
		path.append(files[i]);

		LiveUnitPreset lupreset;
		Exitcode exitcode = ParseUnit(path, &lupreset);
		switch (exitcode) {
		case GM_NO_ERROR:
			this->creaturePresets.push_back(lupreset);
			break;
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
	targets.addTarget(SearchTarget("targetType", PARSER_NUMBER, "2"));
	targets.addTarget(SearchTarget("lifeTime", PARSER_NUMBER, "5000"));

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
	int targetType = targets.targets[11].temp_int;
	int lifeTime = targets.targets[12].temp_int;


	SpellPreset tempSpellPreset(name, beautyName, type, symbol, damage, cooldown, castCooldown, attackRadius, cost, productionTime, heal, targetType, lifeTime);
	this->spellsPresets.push_back(tempSpellPreset);
//	tempSpellPreset.print();
	cout << "Successfuly loaded spell: " << tempSpellPreset.name << endl;
	return GM_NO_ERROR;
}

void GameMaster::readSpells() {
	string directory = ".\\spells";
	string filetype = "spell";
	vector<string> files = dirFilenames(directory, filetype);

	for (int i = 0; i < files.size(); i++) {
		string path = directory;
		path.append("\\");
		path.append(files[i]);

		Exitcode exitcode = readParseSpell(path);
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
	//tempBuildingPreset.print();
	cout << "Successfuly loaded building: " << tempBuildingPreset.name << endl;
	return GM_NO_ERROR;
}

void GameMaster::readBuildings() {
	string directory = ".\\buildings";
	string filetype = "building";
	vector<string> files = dirFilenames(directory, filetype);

	for (int i = 0; i < files.size(); i++) {
		string path = directory;
		path.append("\\");
		path.append(files[i]);

		Exitcode exitcode = readParseBuilding(path);
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
}

bool GameMaster::saveGame() {
	return false;
}

Exitcode GameMaster::addField(ParserOut data, placeableData<FieldPreset> *writeTo) {
	FieldPreset preset;
	Exitcode exitcode;

	UnInSearchTargets targets("field");
	targets.addTarget(SearchTarget("width", PARSER_NUMBER, "20"));
	targets.addTarget(SearchTarget("heigth", PARSER_NUMBER, "45"));
	targets.addTarget(SearchTarget("x", PARSER_NUMBER, "2"));
	targets.addTarget(SearchTarget("y", PARSER_NUMBER, "2"));

	UnitInterpretor* interpretor = new UnitInterpretor();
	if (!interpretor) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	interpretor->init(targets);
	exitcode = interpretor->interpret(data);
	if (exitcode != GM_NO_ERROR) {
		return exitcode;
	}
	targets = interpretor->getTargets();
	delete interpretor;


	int width = targets.targets[0].temp_int;
	int heigth = targets.targets[1].temp_int;
	int x = targets.targets[2].temp_int;
	int y = targets.targets[3].temp_int;

	preset.width = width;
	preset.heigth = heigth;

	placeableData<FieldPreset> temp;
	temp.preset = preset;
	temp.x = x;
	temp.y = y;

	*writeTo = temp;

	return GM_NO_ERROR;
}

Exitcode GameMaster::addUnit(ParserOut data, vector<placeableData<LiveUnitPreset>>* arr) {
	LiveUnitPreset preset;
	Exitcode exitcode = ParseUnit(data, &preset);
	if (exitcode != GM_NO_ERROR) {
		return exitcode;
	}
	
	UnInSearchTargets targets("unit");
	targets.addTarget(SearchTarget("x", PARSER_NUMBER, "0"));
	targets.addTarget(SearchTarget("y", PARSER_NUMBER, "0"));
	targets.addTarget(SearchTarget("team", PARSER_NUMBER, "1"));

	UnitInterpretor* interpretor = new UnitInterpretor();
	if (!interpretor) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	interpretor->init(targets);
	exitcode = interpretor->interpret(data);
	if (exitcode != GM_NO_ERROR) {
		return exitcode;
	}
	targets = interpretor->getTargets();
	delete interpretor;


	int x = targets.targets[0].temp_int;
	int y = targets.targets[1].temp_int;
	int team = targets.targets[2].temp_int;


	placeableData<LiveUnitPreset> temp;
	temp.preset = preset;
	temp.x = x;
	temp.y = y;
	temp.team = team;
	arr->push_back(temp);
	return GM_NO_ERROR;
}

Exitcode GameMaster::loadGame(string savename) {
	//loading data from file
	string path = "saves/" + savename + ".wcsave";
	FileReader* reader = new FileReader(path);
	if (!reader) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	string file = reader->getData();
	delete reader;
	FileParser* parser = new FileParser();
	if (!parser) {
		return GM_ERROR_ALLOCATING_MEMORY;
	}
	ParserOut input = parser->parse(file);
	delete parser;


//	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
//	input.print();

	//adding temp arrays
	vector<placeableData<LiveUnitPreset>> units;
	placeableData<FieldPreset> field;

	//parsing file
	if (input.args.size() < 2) {
		return GM_ERROR_ARGUMENTS_COUNT;
	}
	if (!(input.args[0].first == "save" && input.args[0].second == PARSER_WORD)) {
		return GM_ERROR_NOT_VALID_TYPE;
	}
	if (input.args[1].second != PARSER_WORD) {
		return GM_ERROR_NOT_VALID_STRUCTURE;
	}

	int dataStart = 2;
	int dataEnd = input.args.size()-1;

	int step = 1;
	for (int i = dataStart; i <= dataEnd; i+= step) {
		step = 1;
		if (input.args[i].second != PARSER_WORD) {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		int fBordStart = i + 1;
		if (fBordStart > dataEnd) {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		if (!(input.args[fBordStart].first == "{" && input.args[fBordStart].second == PARSER_FBORD)) {
			return GM_ERROR_NOT_VALID_STRUCTURE;
		}
		//looking for } symbol
		int fBordEnd;
		for (fBordEnd = fBordStart; fBordEnd <= dataEnd && !(input.args[fBordEnd].first == "}" && input.args[fBordEnd].second == PARSER_FBORD); fBordEnd++) {}
		//calculating step size
		step = fBordEnd - fBordStart + 2;
		//constructing data for FileParser parser
		ParserOut data;
		data.args.push_back(input.args[i]);
		pair <string, string> temp;
		temp.first = "empty";
		temp.second = PARSER_WORD;
		data.args.push_back(temp);
		for (int id = fBordStart; id <= fBordEnd; id++) {
			data.args.push_back(input.args[id]);
		}
//		data.print();
		if (data.args[0].first == "unit") {
			addUnit(data, &units);
		}
		if (data.args[0].first == "field") {
			addField(data, &field);
		}

	}

	Field* oldField = this->field;
	this->field = new Field(field.preset);
	if (oldField) {
		delete oldField;
	}


	for (int i = 0; i < units.size(); i++) {
		LiveUnit* tempUnit = new LiveUnit(units[i].preset, this->field, units[i].team); //---------------------------------------------------------------------
		this->field->setCell(cordScr(units[i].x,units[i].y),tempUnit);
	}
	return GM_NO_ERROR;
}

int GameMaster::searchSpell(string name) {
	for (int i = 0; i < spellsPresets.size(); i++) {
		if (spellsPresets[i].name == name) {
			return i;
		}
	}
	return -1;
}

int GameMaster::searchUnit(string name) {
	for (int i = 0; i < creaturePresets.size(); i++) {
		if (creaturePresets[i].name == name) {
			return i;
		}
	}
	return -1;
}

int GameMaster::searchBuilding(string name) {
	for (int i = 0; i < buildingPresets.size(); i++) {
		if (buildingPresets[i].name == name) {
			return i;
		}
	}
	return -1;
}


LiveUnitPreset* GameMaster::getUnitPreset(string name){
	int id = searchUnit(name);
	if (id != -1) {
		return &(creaturePresets[id]);
	}
	return NULL;
}