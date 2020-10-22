#include "pch.h"
#include "FileParser.h"


using namespace std;


const char* PARSER_DQDATA = "dqdata";
const char* PARSER_QDATA = "qdata";
const char* PARSER_DOTCOM = "dotcom";
const char* PARSER_COMA = "coma";
const char* PARSER_DDOTS = "ddots";
const char* PARSER_NUMBER = "number";
const char* PARSER_WORD = "word";
const char* PARSER_SBORD_LIST = "sbord_list";
const char* PARSER_SBORD = "sbord";
const char* PARSER_FBORD = "fbord";
const char* PARSER_DQUOTE = "dquote";
const char* PARSER_QUOTE = "quote";
const char* PARSER_DOT = "dot";
const char* PARSER_UNKNOWN = "unknown";
const char* PARSER_ERROR = "error";
const char* PARSER_EMPTY = "empty";
const char* PARSER_END = "end";



FileParser::FileParser() {
	ParserPosition = 0;
}

FileParser::~FileParser() {
}

bool FileParser::readCondition(char character) {
	if ((character != ' ') && character != 0 && character != '\n') {
		return true;
	}
	return false;
}

string FileParser::inputType(char character) {
	if (character == '{' || character == '}') {
		return PARSER_FBORD;
	}
	if (character == '[' || character == ']') {
		return PARSER_SBORD;
	}
	if (character == ':') {
		return PARSER_DDOTS;
	}
	if (character == '\"') {
		return PARSER_DQUOTE;
	}
	if (character == '\'') {
		return PARSER_QUOTE;
	}
	if (character == ';') {
		return PARSER_DOTCOM;
	}
	if (character == ',') {
		return PARSER_COMA;
	}
	if (character == '.') {
		return PARSER_DOT;
	}
	if (isalpha(character)) {
		return PARSER_WORD;
	}
	if (isdigit(character)) {
		return PARSER_NUMBER;
	}
	return PARSER_UNKNOWN;
}

bool FileParser::isServiceSymbol(char character) {
	string type = inputType(character);
	return isServiceSymbol(type);
}

bool FileParser::isServiceSymbol(string type) {
	if (type == PARSER_FBORD || type == PARSER_SBORD || type == PARSER_DDOTS || type == PARSER_DQUOTE || type == PARSER_QUOTE || type == PARSER_DOTCOM || type == PARSER_COMA || type == PARSER_DOT) {
		return true;
	}
	return false;
}

pair <string, string> FileParser::nextToken(string command) {
	bool readBegin = true;
	pair <string, string> temp;
	while (!readCondition(command[ParserPosition])) {
		if (command[ParserPosition] == 0) {
			temp.first = "\0";
			temp.second = "end";
			return temp;
		}
		ParserPosition++;
	}


	while (readCondition(command[ParserPosition])) {
		char dest = '\0';
		bool readToDest = false;
		if (!readBegin && isServiceSymbol(command[ParserPosition])) {
			return temp;
		}
		temp.first += command[ParserPosition];
		if (readBegin) {
			temp.second = inputType(temp.first[0]);
			if (inputType(command[ParserPosition]) == PARSER_QUOTE || inputType(command[ParserPosition]) == PARSER_DQUOTE) {
				if (inputType(command[ParserPosition]) == PARSER_QUOTE) {
					dest = '\'';
					temp.second = PARSER_QDATA;
				}
				if (inputType(command[ParserPosition]) == PARSER_DQUOTE) {
					dest = '\"';
					temp.second = PARSER_DQDATA;
				}
				temp.first.clear();
				readToDest = true;
				ParserPosition++;
			}
			if (readToDest) {
				while (command[ParserPosition] != '\0' && command[ParserPosition] != dest) { // read to destination
					temp.first += command[ParserPosition];
					ParserPosition++;
				}
				if (command[ParserPosition] == '\0') {
					temp.first.clear();
					temp.second = PARSER_ERROR;
					return temp;
				}
				ParserPosition++;
				return temp;
			}
			if (isServiceSymbol(temp.second)) {
				ParserPosition++;
				return temp;
			}
		}
		readBegin = false;
		ParserPosition++;
	}
	return temp;
}


void FileParser::initParser() {
	ParserPosition = 0;
}

ParserOut FileParser::parse(string input) {
	initParser();
	if (input.length() == 0) {
		return ParserOut(PARSER_EMPTY);
	}
	pair <string, string> temp;
	ParserOut output;
	temp = nextToken(input);
	for (int i = 0; temp.second != PARSER_END; i++) {
		output.args.push_back(temp);
		temp = nextToken(input);
	}
	return output;
}

ParserOut FileParser::parseFile(string filename) {
	FileReader* reader = new FileReader(filename);
	if (!reader->isOpened()) {
		delete reader;
		return ParserOut(PARSER_ERROR);
	}
	string temp = reader->getData();
	delete reader;
	return parse(temp);
}


