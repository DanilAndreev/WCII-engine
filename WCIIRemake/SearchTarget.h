#pragma once
#include <vector>
#include <string>
#include "ParserOut.h"


class SearchTarget {
public:
	string target_word;
	string target_type;
	int temp_int;
	string temp_string;
	vector <string> temp_vstring; 
	char temp_char;

public:
	SearchTarget(string target_word, string target_type, string default_value);
	~SearchTarget();
	bool addData(char tChar);
	bool addData(int tInt);
	bool addData(string tString);
	bool addData(vector <string> tVstring);
	bool addData(pair <string, string> input);
};

