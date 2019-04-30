#include "pch.h"
#include "FileParser.h"


using namespace std;

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
		return "fbord";
	}
	if (character == '[' || character == ']') {
		return "sbord";
	}
	if (character == ':') {
		return "ddots";
	}
	if (character == '\"') {
		return "dquote";
	}
	if (character == '\'') {
		return "quote";
	}
	if (character == ';') {
		return "dotcom";
	}
	if (character == ',') {
		return "coma";
	}
	if (isalpha(character)) {
		return "word";
	}
	if (isdigit(character)) {
		return "number";
	}
	return "unknown";
}

bool FileParser::isServiceSymbol(char character) {
	string type = inputType(character);
	return isServiceSymbol(type);
}

bool FileParser::isServiceSymbol(string type) {
	if (type == "fbord" || type == "sbord" || type == "ddots" || type == "dquote" || type == "quote" || type == "dotcom" || type == "coma") {
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
			if (inputType(command[ParserPosition]) == "quote" || inputType(command[ParserPosition]) == "dquote") {
				if (inputType(command[ParserPosition]) == "quote") {
					dest = '\'';
					temp.second = "qdata";
				}
				if (inputType(command[ParserPosition]) == "dquote") {
					dest = '\"';
					temp.second = "dqdata";
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
					temp.first = "";
					temp.second = "error";
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
		return ParserOut("empty");
	}
	pair <string, string> temp;
	ParserOut output;
	temp = nextToken(input);
	for (int i = 0; temp.second != "end"; i++) {
		output.args.push_back(temp);
		temp = nextToken(input);
	}
	return output;
}

ParserOut FileParser::parseFile(string filename) {
	FileReader* reader = new FileReader(filename);
	if (!reader->isOpened()) {
		delete reader;
		return ParserOut("error");
	}
	string temp = reader->getData();
	delete reader;
	return parse(temp);
}



/*
int main() {
	FileReader* reader = new FileReader("demonFury.spell");

	cout << reader->getData();

	FileParser* parser = new FileParser();
	ParserOut output = parser->parse(reader->getData());
	output.print();

	delete parser;
	delete reader;
}
*/