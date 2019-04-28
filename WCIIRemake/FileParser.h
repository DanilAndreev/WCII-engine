#pragma once
#include "Obj.h"
#include "ParserOut.h"
#include "FileReader.h"
#include <string>
#include <vector>
#include <utility>

class FileParser : public Obj {
private:
	int ParserPosition;
public:
	FileParser();
	~FileParser();
	ParserOut parse(string command);
	ParserOut parseFile(string filename);
private:
	bool readCondition(char character);
	pair <string, string> nextToken(string command);
	string inputType(char character);
	void initParser();
	bool isServiceSymbol(string type);
	bool isServiceSymbol(char character);
};
